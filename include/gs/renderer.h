// Renderer entry point. Owners: Dhruv (core blend), Prateek (tiles + threads).
#pragma once
#include "gs/camera.h"
#include "gs/gaussian.h"
#include "gs/image_io.h"

namespace gs {

struct RenderOptions {
    int shDegree = 3;              // 0..3
    int numThreads = 0;            // 0 = OpenMP default
    glm::vec3 background{0.0f};
    float minAlpha = 1.0f / 255.0f; // skip contributions below this
    float transmittanceStop = 1e-4f; // stop a pixel once it is this opaque
};

struct RenderStats {
    int visibleSplats = 0;
    double msProject = 0.0;
    double msBin = 0.0;
    double msBlend = 0.0;
    double msTotal = 0.0;
};

// project -> SH color -> bin into tiles -> front-to-back blend per tile.
Image render(const Scene& scene, const Camera& cam, const RenderOptions& opt,
             RenderStats* stats = nullptr);

} // namespace gs
