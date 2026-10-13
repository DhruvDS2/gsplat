// Owner: Rishabh.
#include "gs/trim.h"

namespace gs {

Scene trimScene(const Scene& scene, const TrimOptions& opt) {
    Scene out;
    out.shDegree = scene.shDegree;
    for (const auto& g : scene.gaussians) {
        if (g.opacity < opt.minOpacity) continue;
        out.gaussians.push_back(g);
    }
    // TODO(Rishabh): if opt.maxGaussians > 0, keep the top-N by an importance score
    //   (e.g. opacity * scale.x * scale.y * scale.z) and measure the PSNR cost.
    return out;
}

} // namespace gs
