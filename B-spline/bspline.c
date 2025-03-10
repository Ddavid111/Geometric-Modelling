#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_POINTS 8

// Kontrollpontok
SDL_Point controlPoints[MAX_POINTS] = {
    {50, 100}, {150, 50}, {250, 150}, {350, 100},
    {450, 200}, {550, 100}, {650, 50}, {750, 150}
};

int degree = 3; // Alapértelmezett fokszám

// B-Spline görbepontok számítása
void GenerateBSpline(SDL_Point *curvePoints, int *curveSize) {
    *curveSize = 0;
    for (int i = 0; i < MAX_POINTS - degree; i++) {
        double x = 0, y = 0;
        for (int j = 0; j < degree; j++) {
            x += controlPoints[i + j].x;
            y += controlPoints[i + j].y;
        }
        curvePoints[*curveSize].x = (int)(x / degree);
        curvePoints[*curveSize].y = (int)(y / degree);
        (*curveSize)++;
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("B-Spline Curve", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Point curvePoints[100];
    int curveSize = 0;
    GenerateBSpline(curvePoints, &curveSize);

    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawLines(renderer, curvePoints, curveSize);
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
