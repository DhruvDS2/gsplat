#include "gs/image_io.h"
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace gs {

std::vector<unsigned char> Image::toRGB8() const {
    std::vector<unsigned char> bytes(pixels.size() * 3);
    for (size_t i = 0; i < pixels.size(); ++i) {
        for (int c = 0; c < 3; ++c) {
            float v = std::clamp(pixels[i][c], 0.0f, 1.0f);
            bytes[i * 3 + c] = static_cast<unsigned char>(v * 255.0f + 0.5f);
        }
    }
    return bytes;
}

bool writePng(const std::string& path, const Image& img) {
    auto bytes = img.toRGB8();
    return stbi_write_png(path.c_str(), img.width, img.height, 3, bytes.data(), img.width * 3) != 0;
}

} // namespace gs
