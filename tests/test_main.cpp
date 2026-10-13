// Minimal test runner (no framework needed). Run: ctest --test-dir build  or  ./build/gs_tests
// Tests marked [TODO] are expected to fail until that part is implemented.
#include "gs/math.h"
#include "gs/ply_loader.h"
#include "gs/renderer.h"
#include "gs/sh.h"
#include <cmath>
#include <cstdio>
#include <functional>
#include <string>
#include <vector>

using namespace gs;

static int failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::printf("    FAILED: %s (line %d)\n", #cond, __LINE__); ++failures; return; } } while (0)
static bool near(float a, float b, float eps = 1e-4f) { return std::fabs(a - b) < eps; }

// ---- Dhruv ----
static void test_cov3d_identity_rotation() {
    glm::mat3 c = covariance3D({2.0f, 3.0f, 4.0f}, glm::quat(1, 0, 0, 0));
    // With no rotation, Sigma = diag(scale^2).
    CHECK(near(c[0][0], 4.0f) && near(c[1][1], 9.0f) && near(c[2][2], 16.0f));
    CHECK(near(c[0][1], 0.0f) && near(c[1][2], 0.0f));
}

static void test_projection_center_visible() {
    Camera cam;
    Gaussian g;               // at origin; default camera looks at origin
    g.scale = glm::vec3(0.1f);
    Splat2D s = projectGaussian(g, cam, cam.view());
    CHECK(s.visible);
    CHECK(near(s.center.x, cam.width * 0.5f, 0.5f) && near(s.center.y, cam.height * 0.5f, 0.5f));
}

// ---- Rishabh ----
static void test_sh_degree0_color() {
    Gaussian g;
    const float C0 = 0.28209479177387814f;
    g.sh[0] = (glm::vec3(0.8f, 0.4f, 0.1f) - 0.5f) / C0;
    glm::vec3 c = evalSH(g, {0, 0, 1}, 0);
    CHECK(near(c.r, 0.8f) && near(c.g, 0.4f) && near(c.b, 0.1f));
}

// ---- Integration ----
static void test_render_test_scene_not_black() {
    Camera cam; cam.width = 160; cam.height = 90;
    Image img = render(makeTestScene(), cam, RenderOptions{});
    float sum = 0.0f;
    for (auto& p : img.pixels) sum += p.r + p.g + p.b;
    CHECK(sum > 1.0f);
}

int main() {
    std::vector<std::pair<std::string, std::function<void()>>> tests = {
        {"cov3d identity rotation [TODO Dhruv]", test_cov3d_identity_rotation},
        {"projection center visible [TODO Dhruv]", test_projection_center_visible},
        {"sh degree 0 color", test_sh_degree0_color},
        {"render test scene not black [TODO all]", test_render_test_scene_not_black},
    };
    for (auto& [name, fn] : tests) {
        int before = failures;
        fn();
        std::printf("[%s] %s\n", failures == before ? "PASS" : "FAIL", name.c_str());
    }
    std::printf("%d failure(s)\n", failures);
    return failures == 0 ? 0 : 1;
}
