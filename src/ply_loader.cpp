// Owner: Rishabh.
#include "gs/ply_loader.h"
#include <happly.h>
#include <stdexcept>

namespace gs {

Scene loadPly(const std::string& path) {
    Scene scene;
    // TODO(Rishabh):
    //  happly::PLYData ply(path);
    //  auto& v = ply.getElement("vertex");
    //  Read x,y,z  f_dc_0..2  f_rest_0..44  opacity  scale_0..2  rot_0..3 as std::vector<float>.
    //  Decode: scale = exp(s), opacity = 1/(1+exp(-o)), rotation = normalize(quat(rot_0, rot_1, rot_2, rot_3)).
    //  SH layout: f_rest is channel-major -> for channel c and coeff k (1..15): f_rest[c*15 + (k-1)].
    //  Set scene.shDegree from how many f_rest properties exist (0, 9, 24 or 45 -> degree 0..3).
    (void)path;
    throw std::runtime_error("loadPly not implemented yet (TODO Rishabh). Use --test-scene for now.");
    return scene;
}

Scene makeTestScene() {
    // Three colored Gaussians in front of the default camera. Good for debugging math.
    Scene scene;
    const float kC0 = 0.28209479177387814f; // SH degree-0 constant
    auto add = [&](glm::vec3 p, glm::vec3 scale, glm::vec3 rgb) {
        Gaussian g;
        g.position = p;
        g.scale = scale;
        g.opacity = 0.9f;
        g.sh[0] = (rgb - 0.5f) / kC0; // inverse of color = C0 * sh0 + 0.5
        scene.gaussians.push_back(g);
    };
    add({-1.0f, 0.0f, 0.0f}, {0.4f, 0.2f, 0.2f}, {1.0f, 0.2f, 0.2f});
    add({ 0.0f, 0.0f, 0.5f}, {0.3f, 0.3f, 0.3f}, {0.2f, 1.0f, 0.2f});
    add({ 1.0f, 0.0f, 0.0f}, {0.2f, 0.5f, 0.2f}, {0.2f, 0.4f, 1.0f});
    return scene;
}

} // namespace gs
