#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600

float rotateX = 0.0f;
float rotateY = 0.0f;


void parametric_surface(float u, float v, float *x, float *y, float *z) {
    float R = 2.0f, r = 0.8f;
    *x = (R + r * cosf(v)) * cosf(u);
    *y = (R + r * cosf(v)) * sinf(u);
    *z = r * sinf(v);
}

void compute_normal(float u, float v, float *nx, float *ny, float *nz) {
    float x1, y1, z1, x2, y2, z2, x3, y3, z3;
    
    parametric_surface(u, v, &x1, &y1, &z1);
    parametric_surface(u + 0.01, v, &x2, &y2, &z2);
    parametric_surface(u, v + 0.01, &x3, &y3, &z3);
    
    float ux = x2 - x1, uy = y2 - y1, uz = z2 - z1;
    float vx = x3 - x1, vy = y3 - y1, vz = z3 - z1;

    *nx = uy * vz - uz * vy;
    *ny = uz * vx - ux * vz;
    *nz = ux * vy - uy * vx;

    float length = sqrtf((*nx) * (*nx) + (*ny) * (*ny) + (*nz) * (*nz));
    if (length > 0.0f) {
        *nx /= length;
        *ny /= length;
        *nz /= length;
    }
}


void draw_surface() {
    int u_res = 50, v_res = 50;
    float u, v, x, y, z, nx, ny, nz;
    
    for (int i = 0; i < u_res; i++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= v_res; j++) {
            u = (float)i / u_res * 2 * M_PI;
            v = (float)j / v_res * 2 * M_PI;
            
            parametric_surface(u, v, &x, &y, &z);
            compute_normal(u, v, &nx, &ny, &nz);
            glNormal3f(nx, ny, nz);  
            glVertex3f(x, y, z);
            
            u = (float)(i + 1) / u_res * 2 * M_PI;
            parametric_surface(u, v, &x, &y, &z);
            compute_normal(u, v, &nx, &ny, &nz);
            glNormal3f(nx, ny, nz);
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);

    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = {1.0f, 1.0f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glEnable(GL_DEPTH_TEST);
    
    draw_surface();
    
    glDisable(GL_LIGHTING);
}


int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Parametric Surface", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)WIDTH / (double)HEIGHT, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_NORMALIZE);


    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        rotateY -= 5.0f;
                        break;
                    case SDLK_RIGHT:
                        rotateY += 5.0f;
                        break;
                    case SDLK_UP:
                        rotateX -= 5.0f;
                        break;
                    case SDLK_DOWN:
                        rotateX += 5.0f;
                        break;
                }
            }
        }
        
        render();
        SDL_GL_SwapWindow(window);
    }
    
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
