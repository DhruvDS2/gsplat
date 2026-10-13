// Owner: Prateek.
#include "gs/tiles.h"
#include <algorithm>

namespace gs {

TileGrid binSplats(const std::vector<Splat2D>& splats, int width, int height) {
    TileGrid grid;
    grid.tilesX = (width + kTileSize - 1) / kTileSize;
    grid.tilesY = (height + kTileSize - 1) / kTileSize;
    grid.bins.resize(static_cast<size_t>(grid.tilesX) * grid.tilesY);

    // TODO(Prateek): for each visible splat, compute the tile range covered by
    //   [center - radius, center + radius], clamp to the grid, push its index into each bin.
    //   Then sort each bin by splats[i].depth (nearest first).
    //   Later: parallelize the sort over bins with OpenMP; compare against one global sort.
    (void)splats;
    return grid;
}

} // namespace gs
