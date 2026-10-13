// Shared data types. Owner: Dhruv. Everyone codes against these.
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <array>
#include <vector>

namespace gs {

// Number of SH coefficients per color channel for degree 3: (3+1)^2 = 16.
constexpr int kMaxShDegree = 3;
constexpr int kShCoeffs = (kMaxShDegree + 1) * (kMaxShDegree + 1);

// One 3D Gaussian, already decoded from the .ply file:
//  - scale is the real scale (exp already applied to the stored log-scale)
//  - opacity is in [0,1] (sigmoid already applied)
//  - rotation is a normalized quaternion
struct Gaussian {
    glm::vec3 position{0.0f};
    glm::vec3 scale{1.0f};
    glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f}; // (w, x, y, z)
    float opacity = 1.0f;
    // sh[k] = RGB coefficient k. k = 0 is the base (DC) color.
    std::array<glm::vec3, kShCoeffs> sh{};
};

struct Scene {
    std::vector<Gaussian> gaussians;
    int shDegree = 0; // highest SH degree present in the file
};

// A Gaussian after projection to the screen for one camera.
struct Splat2D {
    glm::vec2 center{0.0f};   // pixel coordinates
    glm::vec3 conic{0.0f};    // inverse 2D covariance (a, b, c) for [a b; b c]
    float radius = 0.0f;      // bounding radius in pixels (3 sigma)
    float depth = 0.0f;       // view-space depth, used for sorting
    glm::vec3 color{0.0f};    // view-dependent RGB from SH
    float opacity = 0.0f;
    int index = -1;           // index into Scene::gaussians
    bool visible = false;
};

} // namespace gs
