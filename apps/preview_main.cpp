// Low-resolution interactive preview. Owner: Orvin.
//   gs_preview --ply scenes/garden/point_cloud.ply
// Controls (to implement): WASD move, mouse drag look, 1-4 SH degree, P save screenshot.
#include "gs/camera.h"
#include "gs/ply_loader.h"
#include "gs/renderer.h"
#include <SDL.h>
#include <cstdio>
#include <string>

using namespace gs;

int main(int argc, char** argv) {
    std::string plyPath;
    for (int i = 1; i < argc; ++i)
        if (std::string(argv[i]) == "--ply" && i + 1 < argc) plyPath = argv[++i];

    Scene scene = plyPath.empty() ? makeTestScene() : loadPly(plyPath);

    Camera cam;
    cam.width = 320; // render small, display scaled up
    cam.height = 180;
    const int scale = 4;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("gs_preview", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       cam.width * scale, cam.height * scale, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING,
                                         cam.width, cam.height);

    RenderOptions opt;
    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            // TODO(Orvin): camera controls, SH degree keys, screenshot key.
        }
        RenderStats stats;
        Image img = render(scene, cam, opt, &stats);
        auto bytes = img.toRGB8();
        SDL_UpdateTexture(tex, nullptr, bytes.data(), cam.width * 3);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, nullptr, nullptr);
        SDL_RenderPresent(ren);

        char title[96];
        std::snprintf(title, sizeof(title), "gs_preview  %.1f ms  (%.1f FPS)",
                      stats.msTotal, 1000.0 / (stats.msTotal + 1e-6));
        SDL_SetWindowTitle(win, title);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
