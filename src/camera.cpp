#include "gs/camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

namespace gs {

glm::mat4 Camera::view() const { return glm::lookAt(position, target, up); }

glm::mat4 Camera::projection() const {
    return glm::perspective(fovY, float(width) / float(height), znear, zfar);
}

float Camera::focalY() const { return 0.5f * float(height) / std::tan(0.5f * fovY); }
float Camera::focalX() const { return focalY(); } // square pixels

std::vector<Camera> turntablePath(const Camera& base, glm::vec3 center,
                                  float radius, float height, int frames) {
    // TODO(Orvin): add smoother paths (orbit + dolly), maybe load poses from cameras.json.
    std::vector<Camera> path;
    path.reserve(frames);
    for (int i = 0; i < frames; ++i) {
        float t = 2.0f * 3.14159265f * float(i) / float(frames);
        Camera c = base;
        c.position = center + glm::vec3(radius * std::cos(t), height, radius * std::sin(t));
        c.target = center;
        path.push_back(c);
    }
    return path;
}

} // namespace gs
