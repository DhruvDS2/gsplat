// .ply scene loading. Owner: Rishabh.
#pragma once
#include "gs/gaussian.h"
#include <string>

namespace gs {

// Loads a 3DGS .ply file (x, y, z, f_dc_*, f_rest_*, opacity, scale_*, rot_*).
// Decodes stored values: exp(scale), sigmoid(opacity), normalized quaternion.
// Throws std::runtime_error on failure.
Scene loadPly(const std::string& path);

// Small hand-made scene for testing before real scenes are downloaded.
Scene makeTestScene();

} // namespace gs
