// Command-line renderer: still images and turntable frames.
//   gs_render --test-scene -o out/test.png
//   gs_render --ply scenes/garden/point_cloud.ply -o out/garden.png --sh 3 --threads 8
//   gs_render --ply ... --turntable 120 -o out/frames      (writes frame_0000.png ...)
#include "gs/camera.h"
#include "gs/ply_loader.h"
#include "gs/renderer.h"
#include "gs/trim.h"
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>

using namespace gs;

int main(int argc, char** argv) {
    std::string plyPath, outPath = "out/render.png";
    bool testScene = false;
    int turntable = 0;
    RenderOptions opt;
    Camera cam;
    float minOpacity = 0.0f;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        auto next = [&]() { return (i + 1 < argc) ? std::string(argv[++i]) : std::string(); };
        if (a == "--ply") plyPath = next();
        else if (a == "--test-scene") testScene = true;
        else if (a == "-o") outPath = next();
        else if (a == "--sh") opt.shDegree = std::atoi(next().c_str());
        else if (a == "--threads") opt.numThreads = std::atoi(next().c_str());
        else if (a == "--width") cam.width = std::atoi(next().c_str());
        else if (a == "--height") cam.height = std::atoi(next().c_str());
        else if (a == "--turntable") turntable = std::atoi(next().c_str());
        else if (a == "--trim") minOpacity = std::atof(next().c_str());
        else { std::fprintf(stderr, "Unknown argument: %s\n", a.c_str()); return 1; }
    }

    Scene scene;
    try {
        scene = testScene || plyPath.empty() ? makeTestScene() : loadPly(plyPath);
    } catch (const std::exception& e) {
        std::fprintf(stderr, "Error: %s\n", e.what());
        return 1;
    }
    if (minOpacity > 0.0f) scene = trimScene(scene, TrimOptions{minOpacity, 0});
    std::printf("Loaded %zu Gaussians (SH degree %d)\n", scene.gaussians.size(), scene.shDegree);

    if (turntable > 0) {
        std::filesystem::create_directories(outPath);
        auto path = turntablePath(cam, cam.target, 5.0f, 0.0f, turntable);
        for (int f = 0; f < turntable; ++f) {
            Image img = render(scene, path[f], opt);
            char name[64];
            std::snprintf(name, sizeof(name), "/frame_%04d.png", f);
            writePng(outPath + name, img);
        }
        std::printf("Wrote %d frames to %s (make a video with scripts/make_video.sh)\n", turntable, outPath.c_str());
        return 0;
    }

    RenderStats stats;
    Image img = render(scene, cam, opt, &stats);
    auto parent = std::filesystem::path(outPath).parent_path();
    if (!parent.empty()) std::filesystem::create_directories(parent);
    if (!writePng(outPath, img)) { std::fprintf(stderr, "Failed to write %s\n", outPath.c_str()); return 1; }

    std::printf("Wrote %s (%dx%d)\n", outPath.c_str(), img.width, img.height);
    std::printf("visible=%d  project=%.1fms  bin=%.1fms  blend=%.1fms  total=%.1fms\n",
                stats.visibleSplats, stats.msProject, stats.msBin, stats.msBlend, stats.msTotal);
    return 0;
}
