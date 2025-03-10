#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

void hermite(double t, double p0x, double p0y, double t0x, double t0y, double p1x, double p1y, double t1x, double t1y, double *x, double *y) {
    double h0 = 2 * pow(t, 3) - 3 * pow(t, 2) + 1;
    double h1 = -2 * pow(t, 3) + 3 * pow(t, 2);
    double h2 = pow(t, 3) - 2 * pow(t, 2) + t;
    double h3 = pow(t, 3) - pow(t, 2);

    *x = h0 * p0x + h1 * p1x + h2 * t0x + h3 * t1x;
    *y = h0 * p0y + h1 * p1y + h2 * t0y + h3 * t1y;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init hiba: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Hermite Curve", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Ablak létrehozása hiba: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer létrehozása hiba: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    double p0x = 100, p0y = 500;
    double t0x = 200, t0y = 400;
    double p1x = 700, p1y = 100;
    double t1x = 600, t1y = 200;

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    for (double t = 0; t <= 1; t += 0.01) {
        double x, y;
        hermite(t, p0x, p0y, t0x, t0y, p1x, p1y, t1x, t1y, &x, &y);

        SDL_RenderDrawPoint(renderer, (int)x, (int)y);
    }

    SDL_RenderPresent(renderer);

    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
