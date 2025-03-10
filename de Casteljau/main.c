#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define POINT_RADIUS 5
#define STEP 0.01

typedef struct {
    float x, y;
} Point;

Point controlPoints[] = {
    {100, 300}, {300, 100}, {500, 500}, {700, 300}
};

const int numPoints = sizeof(controlPoints) / sizeof(Point);
bool running = true;
int selectedPoint = -1;
double t = 0.5;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool isNear(Point p, int x, int y) {
    return fabs(p.x - x) < 10 && fabs(p.y - y) < 10;
}

Point calculateBezierPoint(double t) {
    Point temp[numPoints];
    for (int i = 0; i < numPoints; i++) {
        temp[i] = controlPoints[i];
    }

    for (int k = 1; k < numPoints; k++) {
        for (int i = 0; i < numPoints - k; i++) {
            temp[i].x = (1 - t) * temp[i].x + t * temp[i + 1].x;
            temp[i].y = (1 - t) * temp[i].y + t * temp[i + 1].y;
        }
    }
    return temp[0];
}

void drawLine(Point p1, Point p2, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

void drawPoint(Point p, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    for (int dx = -POINT_RADIUS; dx <= POINT_RADIUS; dx++) {
        for (int dy = -POINT_RADIUS; dy <= POINT_RADIUS; dy++) {
            if (dx * dx + dy * dy <= POINT_RADIUS * POINT_RADIUS) {
                SDL_RenderDrawPoint(renderer, p.x + dx, p.y + dy);
            }
        }
    }
}

void drawBezierCurve() {
    SDL_Color curveColor = {0, 0, 0, 255};
    Point prev = controlPoints[0];
    
    for (double t = 0; t <= 1; t += STEP) {
        Point p = calculateBezierPoint(t);
        drawLine(prev, p, curveColor);
        prev = p;
    }
}

void drawControlPolygon() {
    SDL_Color lineColor = {150, 150, 150, 255};
    for (int i = 0; i < numPoints - 1; i++) {
        drawLine(controlPoints[i], controlPoints[i + 1], lineColor);
    }

    SDL_Color pointColor = {0, 0, 255, 255};
    for (int i = 0; i < numPoints; i++) {
        drawPoint(controlPoints[i], pointColor);
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    drawControlPolygon();
    drawBezierCurve();
    drawPoint(calculateBezierPoint(t), (SDL_Color){0, 255, 0, 255});

    SDL_RenderPresent(renderer);
}

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Bezier Curve - SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer != NULL;
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    for (int i = 0; i < numPoints; i++) {
                        if (isNear(controlPoints[i], event.button.x, event.button.y)) {
                            selectedPoint = i;
                            break;
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                selectedPoint = -1;
                break;
            case SDL_MOUSEMOTION:
                if (selectedPoint != -1) {
                    controlPoints[selectedPoint].x = event.motion.x;
                    controlPoints[selectedPoint].y = event.motion.y;
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_UP && t < 1) t += 0.05;
                if (event.key.keysym.sym == SDLK_DOWN && t > 0) t -= 0.05;
                break;
        }
    }
}

int main(int argc, char* argv[])
 {
    if (!initSDL()) return 1;

    while (running) {
        handleEvents();
        render();
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
