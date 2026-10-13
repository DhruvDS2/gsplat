# Tasks and milestones

Find open work in code: `grep -rn "TODO(" src apps scripts`

## Milestones
- **Nov 3:** first rendered image of the test scene and a real scene; tile binning working
- **Nov 14:** multithreaded rendering; video export working
- **Nov 21:** scene trimming done
- **Nov 25:** feature freeze
- **Dec 1:** report, demo video, final presentation

## Dhruv — math + core renderer
- [ ] `covariance3D` (test: `cov3d identity rotation`)
- [ ] `covariance2D` with the projection Jacobian
- [ ] `projectGaussian`: depth cull, conic, radius, pixel center (test: `projection center visible`)
- [ ] Per-pixel blending in `blendTile`
- [ ] Integration, fixing artifacts, CPU image vs. paper reference

## Prateek — tiles + performance
- [ ] `binSplats`: tile ranges, per-tile depth sort
- [ ] OpenMP across tiles; try schedule(dynamic) vs static
- [ ] Profile (perf / `RenderStats`), optimize hot loops
- [ ] Target: < 2 s for 1280x720 with ~200k Gaussians

## Rishabh — data + color
- [ ] Download scenes (see `scenes/README.md`)
- [ ] `loadPly` with decoding (exp scale, sigmoid opacity, normalized quaternion)
- [ ] `evalSH` degrees 1–3
- [ ] `trimScene` top-N by importance; measure PSNR loss

## Orvin — app + evaluation
- [ ] `gs_preview` controls (WASD, mouse look, SH keys, screenshot)
- [ ] Camera paths + turntable video
- [ ] PSNR on 3 scenes; render time vs 1/2/4/8 threads
- [ ] Demo video
