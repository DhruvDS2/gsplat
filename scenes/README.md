# Scenes

Scene files are large (hundreds of MB), so they are **not** committed to Git. Each teammate downloads them locally into this folder.

## Where to get them

The pretrained models from the original paper are linked from the official repo's README:
https://github.com/graphdeco-inria/gaussian-splatting (look for "Pre-trained Models").

Unzip so the layout looks like:

```
scenes/
  garden/point_cloud/iteration_30000/point_cloud.ply
  bicycle/point_cloud/iteration_30000/point_cloud.ply
  ...
```

Good scenes to start with: `garden`, `bicycle`, `truck`. For fast iteration, trim first:

```
./build/gs_render --ply scenes/garden/point_cloud/iteration_30000/point_cloud.ply --trim 0.05 -o out/garden.png
```

Reference images for PSNR come from the matching dataset (Mip-NeRF 360 / Tanks and Temples).
Credit the dataset in slides and the report.
