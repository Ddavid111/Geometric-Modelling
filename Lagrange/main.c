#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define POINT_RADIUS 5
#define NUM_POINTS 4

typedef struct {
    double x, y;
} Point;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Point controlPoints[NUM_POINTS] = {
    {100, 200}, {200, 200}, {300, 200}, {400, 200}
};
int selectedPoint = -1;

int initSDL();
void closeSDL();
void drawPoints();
void drawLagrangeCurve();
double lagrangeInterpolation(double x);

int main(int argc, char *argv[]) {
    if (!initSDL()) return 1;
    
    SDL_Event e;
    int quit = 0;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mx = e.button.x, my = e.button.y;
                for (int i = 0; i < NUM_POINTS; i++) {
                    if (fabs(mx - controlPoints[i].x) < 10 && fabs(my - controlPoints[i].y) < 10) {
                        selectedPoint = i;
                        break;
                    }
                }
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                selectedPoint = -1;
            } else if (e.type == SDL_MOUSEMOTION && selectedPoint != -1) {
                controlPoints[selectedPoint].x = e.motion.x;
                controlPoints[selectedPoint].y = e.motion.y;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        drawLagrangeCurve();
        drawPoints();
        
        SDL_RenderPresent(renderer);
    }
    
    closeSDL();
    return 0;
}

int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    window = SDL_CreateWindow("Lagrange Interpolation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    return 1;
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void drawPoints() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < NUM_POINTS; i++) {
        SDL_Rect rect = {controlPoints[i].x - POINT_RADIUS, controlPoints[i].y - POINT_RADIUS, 2 * POINT_RADIUS, 2 * POINT_RADIUS};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void drawLagrangeCurve() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (double x = 0; x < SCREEN_WIDTH - 1; x += 1) {
        double y1 = lagrangeInterpolation(x);
        double y2 = lagrangeInterpolation(x + 1);
        SDL_RenderDrawLine(renderer, x, y1, x + 1, y2);
    }
}

double lagrangeInterpolation(double x) {
    double result = 0;
    for (int i = 0; i < NUM_POINTS; i++) {
        double term = controlPoints[i].y;
        for (int j = 0; j < NUM_POINTS; j++) {
            if (i != j) {
                term *= (x - controlPoints[j].x) / (controlPoints[i].x - controlPoints[j].x);
            }
        }
        result += term;
    }
    return result;
}
