// Image buffer + PNG output.
#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace gs {

struct Image {
    int width = 0;
    int height = 0;
    std::vector<glm::vec3> pixels; // linear RGB in [0,1], row-major

    Image() = default;
    Image(int w, int h, glm::vec3 fill = glm::vec3(0.0f))
        : width(w), height(h), pixels(static_cast<size_t>(w) * h, fill) {}

    glm::vec3& at(int x, int y) { return pixels[static_cast<size_t>(y) * width + x]; }
    const glm::vec3& at(int x, int y) const { return pixels[static_cast<size_t>(y) * width + x]; }

    std::vector<unsigned char> toRGB8() const;
};

bool writePng(const std::string& path, const Image& img);

} // namespace gs
