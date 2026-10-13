// Tile binning. Owner: Prateek.
#pragma once
#include "gs/gaussian.h"
#include <vector>

namespace gs {

constexpr int kTileSize = 16; // pixels per tile side

struct TileGrid {
    int tilesX = 0;
    int tilesY = 0;
    // bins[ty * tilesX + tx] = indices into the splat array, sorted front-to-back.
    std::vector<std::vector<int>> bins;
};

// Assigns each visible splat to every tile its bounding square overlaps,
// then sorts each tile's list by depth (nearest first).
TileGrid binSplats(const std::vector<Splat2D>& splats, int width, int height);

} // namespace gs
