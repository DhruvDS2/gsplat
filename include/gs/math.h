// Projection math. Owner: Dhruv.
#pragma once
#include "gs/camera.h"
#include "gs/gaussian.h"
#include <glm/glm.hpp>

namespace gs {

// 3D covariance: Sigma = R S S^T R^T  (R from quaternion, S = diag(scale)).
glm::mat3 covariance3D(const glm::vec3& scale, const glm::quat& rotation);

// 2D screen-space covariance: Sigma' = J W Sigma W^T J^T, keeping the top-left 2x2.
// `viewPos` is the Gaussian center in camera space, `viewRot` the 3x3 part of the view matrix.
glm::mat2 covariance2D(const glm::mat3& cov3D, const glm::vec3& viewPos,
                       const glm::mat3& viewRot, float focalX, float focalY);

// Full per-Gaussian projection: fills center, conic, radius, depth, visible.
// Color is filled separately by SH evaluation.
Splat2D projectGaussian(const Gaussian& g, const Camera& cam,
                        const glm::mat4& view);

} // namespace gs
