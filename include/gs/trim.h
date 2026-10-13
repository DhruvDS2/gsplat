// Scene trimming / culling. Owner: Rishabh.
#pragma once
#include "gs/gaussian.h"

namespace gs {

struct TrimOptions {
    float minOpacity = 0.005f; // drop nearly transparent Gaussians
    int maxGaussians = 0;      // 0 = no cap; otherwise keep the most "important"
};

// Returns a reduced copy of the scene.
Scene trimScene(const Scene& scene, const TrimOptions& opt);

} // namespace gs
