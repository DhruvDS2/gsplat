// Spherical harmonics color. Owner: Rishabh.
#pragma once
#include "gs/gaussian.h"
#include <glm/glm.hpp>

namespace gs {

// Evaluates view-dependent RGB for one Gaussian.
// `dir` = normalized direction from camera position to the Gaussian center.
// `degree` = 0..3 (clamped to the scene's available degree by the caller).
// Result follows the reference code: color = SH(dir) + 0.5, clamped at 0.
glm::vec3 evalSH(const Gaussian& g, const glm::vec3& dir, int degree);

} // namespace gs
