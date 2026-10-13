// Owners: Dhruv (blend math), Prateek (threading).
#include "gs/renderer.h"
#include "gs/math.h"
#include "gs/sh.h"
#include "gs/tiles.h"
#include <chrono>
#include <cmath>

#ifdef GS_HAS_OPENMP
#include <omp.h>
#endif

namespace gs {

namespace {
using Clock = std::chrono::steady_clock;
double msSince(Clock::time_point t) {
    return std::chrono::duration<double, std::milli>(Clock::now() - t).count();
}

// Front-to-back alpha compositing for one tile.
void blendTile(const std::vector<Splat2D>& splats, const std::vector<int>& bin,
               int tx, int ty, const RenderOptions& opt, Image& out) {
    const int x0 = tx * kTileSize, y0 = ty * kTileSize;
    const int x1 = std::min(x0 + kTileSize, out.width);
    const int y1 = std::min(y0 + kTileSize, out.height);
    for (int y = y0; y < y1; ++y) {
        for (int x = x0; x < x1; ++x) {
            glm::vec3 color(0.0f);
            float T = 1.0f; // transmittance
            // TODO(Dhruv): for each splat index in `bin` (front to back):
            //   d = pixel center (x+0.5, y+0.5) - splat.center
            //   power = -0.5 * (a*dx*dx + c*dy*dy) - b*dx*dy   using conic (a, b, c)
            //   alpha = min(0.99, opacity * exp(power)); skip if alpha < opt.minAlpha
            //   color += splat.color * alpha * T;  T *= (1 - alpha)
            //   stop if T < opt.transmittanceStop
            (void)splats; (void)bin;
            out.at(x, y) = color + T * opt.background;
        }
    }
}
} // namespace

Image render(const Scene& scene, const Camera& cam, const RenderOptions& opt,
             RenderStats* stats) {
    auto tStart = Clock::now();
    Image out(cam.width, cam.height, opt.background);
    const glm::mat4 view = cam.view();

#ifdef GS_HAS_OPENMP
    if (opt.numThreads > 0) omp_set_num_threads(opt.numThreads);
#endif

    // 1. Project + color every Gaussian.
    auto t = Clock::now();
    std::vector<Splat2D> splats(scene.gaussians.size());
    const int degree = std::min(opt.shDegree, scene.shDegree);
    #pragma omp parallel for schedule(static)
    for (long i = 0; i < static_cast<long>(scene.gaussians.size()); ++i) {
        const Gaussian& g = scene.gaussians[i];
        Splat2D s = projectGaussian(g, cam, view);
        if (s.visible) {
            s.color = evalSH(g, glm::normalize(g.position - cam.position), degree);
            s.opacity = g.opacity;
        }
        s.index = static_cast<int>(i);
        splats[i] = s;
    }
    double msProject = msSince(t);

    // 2. Bin into tiles.
    t = Clock::now();
    TileGrid grid = binSplats(splats, cam.width, cam.height);
    double msBin = msSince(t);

    // 3. Blend each tile (tiles are independent -> parallel).
    t = Clock::now();
    #pragma omp parallel for schedule(dynamic, 4)
    for (int tileId = 0; tileId < grid.tilesX * grid.tilesY; ++tileId) {
        blendTile(splats, grid.bins[tileId], tileId % grid.tilesX, tileId / grid.tilesX, opt, out);
    }
    double msBlend = msSince(t);

    if (stats) {
        int visible = 0;
        for (const auto& s : splats) visible += s.visible ? 1 : 0;
        stats->visibleSplats = visible;
        stats->msProject = msProject;
        stats->msBin = msBin;
        stats->msBlend = msBlend;
        stats->msTotal = msSince(tStart);
    }
    return out;
}

} // namespace gs
