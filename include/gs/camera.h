// Pinhole camera. Owner: Dhruv (math), Orvin (controls / paths).
#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace gs {

struct Camera {
    int width = 1280;
    int height = 720;
    float fovY = glm::radians(50.0f); // vertical field of view, radians
    float znear = 0.01f;
    float zfar = 100.0f;

    glm::vec3 position{0.0f, 0.0f, 5.0f};
    glm::vec3 target{0.0f, 0.0f, 0.0f};
    glm::vec3 up{0.0f, -1.0f, 0.0f}; // 3DGS/COLMAP scenes are usually y-down

    glm::mat4 view() const;        // world -> camera
    glm::mat4 projection() const;  // camera -> clip
    float focalX() const;          // focal length in pixels
    float focalY() const;
};

// Orvin: camera paths for video export.
// Returns `frames` cameras circling `center` at `radius`.
std::vector<Camera> turntablePath(const Camera& base, glm::vec3 center,
                                  float radius, float height, int frames);

} // namespace gs
