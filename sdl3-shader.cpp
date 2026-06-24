#include <SDL3/SDL.h>
#include <stdbool.h>
#include "vec.h"

// 960x540 (16:9 ratio)
#define WIDTH  960
#define HEIGHT 540

// Alpha is 255 (upper 8 bits, the rest are RGB)
#define ALPHA 0xFF000000

int main(int argc, char *argv[]) {

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return 1;
    }

    // Create Window
    SDL_Window *window = SDL_CreateWindow("XOR Plasma",
        WIDTH, HEIGHT,
        0);
    if (!window) {
        SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Center the window (position is no longer part of CreateWindow)
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    // Create Renderer
    // SDL3 uses driver name instead of index + flags
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);  // NULL = let SDL pick best driver
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create Texture
    SDL_Texture *texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH, HEIGHT);
    if (!texture) {
        SDL_Log("SDL_CreateTexture error: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    uint32_t *pixels;
    int pitch;
    bool quit = false;

    Uint64 startTime = SDL_GetTicks();

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) quit = true;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) quit = true;
        }

        // Time in seconds, with smooth looping
        float time = (SDL_GetTicks() - startTime) * 0.001f;
        float t = fmodf(time * 0.5f, 2.0f * (float)M_PI);  // adjust speed here

        // Lock texture and generate current frame
        if (SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch)) {
            int stride = pitch / sizeof(uint32_t);
            vec2 r = {(float)WIDTH, (float)HEIGHT};

            for (int y = 0; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                    vec4 o;
                    vec2 FC = {(float)x, (float)y};

                    // Original shader from XorDev (https://x.com/XorDev/status/1894123951401378051)
                    // CPP Translation by: tsoding (https://x.com/tsoding/status/1989446257882829223)
                    vec2 p = (FC * 2.0f - r) / r.y, l, i, v = p * (l += 4.0f - 4.0f * fabsf(0.7f - dot(p, p)));
                    for (; i.y++ < 8.0f; o += (sin(v.xyyx()) + 1.0f) * fabsf(v.x - v.y))
                        v += cos(v.yx() * i.y + i + t) / i.y + 0.7f;

                    o = tanh(5.0f * exp(l.x - 4.0f - p.y * vec4(-1, 1, 2, 0)) / o);

                    uint32_t color = ALPHA |
                                     ((uint32_t)(fminf(fmaxf(o.x, 0.0f), 1.0f) * 0xFF) << 16) | // R
                                     ((uint32_t)(fminf(fmaxf(o.y, 0.0f), 1.0f) * 0xFF) << 8)  | // G
                                     ((uint32_t)(fminf(fmaxf(o.z, 0.0f), 1.0f) * 0xFF));        // B

                    pixels[y * stride + x] = color;
                }
            }
            SDL_UnlockTexture(texture);
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
