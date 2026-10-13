// Owner: Dhruv. Reference: Kerbl et al. 2023, Sec. 4, and Zwicker et al. 2001 (EWA splatting).
#include "gs/math.h"

namespace gs {

glm::mat3 covariance3D(const glm::vec3& scale, const glm::quat& rotation) {
    // TODO(Dhruv): Sigma = R * S * S^T * R^T
    //   R = glm::mat3_cast(rotation), S = diag(scale).
    (void)scale; (void)rotation;
    return glm::mat3(1.0f);
}

glm::mat2 covariance2D(const glm::mat3& cov3D, const glm::vec3& viewPos,
                       const glm::mat3& viewRot, float focalX, float focalY) {
    // TODO(Dhruv): Jacobian of the perspective projection at viewPos (x, y, z):
    //   J = [ fx/z   0     -fx*x/z^2 ]
    //       [ 0      fy/z  -fy*y/z^2 ]
    //       [ 0      0      0        ]
    //   T = J * W  (W = viewRot);  cov = T * cov3D * T^T; return top-left 2x2.
    //   Add 0.3 to the diagonal (low-pass filter, as in the reference code).
    //   Note: GLM matrices are column-major: m[col][row].
    (void)cov3D; (void)viewPos; (void)viewRot; (void)focalX; (void)focalY;
    return glm::mat2(1.0f);
}

Splat2D projectGaussian(const Gaussian& g, const Camera& cam, const glm::mat4& view) {
    Splat2D s;
    // TODO(Dhruv):
    //  1. viewPos = view * vec4(g.position, 1). Cull if depth < cam.znear.
    //     (Watch the sign convention: glm::lookAt looks down -z.)
    //  2. cov2D = covariance2D(covariance3D(g.scale, g.rotation), viewPos, mat3(view), fx, fy)
    //  3. conic = inverse(cov2D) stored as (a, b, c); cull if determinant <= 0.
    //  4. radius = 3 * sqrt(largest eigenvalue of cov2D).
    //  5. center = pixel coords: (fx * x / z + width/2, fy * y / z + height/2).
    //  6. Cull if the bounding square is fully off-screen.
    (void)g; (void)cam; (void)view;
    s.visible = false;
    return s;
}

} // namespace gs
