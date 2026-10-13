// Owner: Rishabh. Constants and formula from the reference 3DGS code (forward.cu, computeColorFromSH).
#include "gs/sh.h"
#include <algorithm>

namespace gs {

namespace {
constexpr float C0 = 0.28209479177387814f;
// TODO(Rishabh): C1 = 0.4886025119029199, plus the C2[5] and C3[7] tables from the reference code.
} // namespace

glm::vec3 evalSH(const Gaussian& g, const glm::vec3& dir, int degree) {
    glm::vec3 result = C0 * g.sh[0];
    // TODO(Rishabh): if degree > 0, add the degree-1, 2, 3 terms using dir (x, y, z).
    (void)dir; (void)degree;
    result += 0.5f;
    return glm::max(result, glm::vec3(0.0f));
}

} // namespace gs
