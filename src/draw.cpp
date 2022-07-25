#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <iostream>
#include "defs.h"
#include "draw.h"

using namespace std;

int draw(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    boxRGBA(renderer, x1, y1, x2, y2, 255, 255, 255, 255);
    return 0;
}

int drawhex(SDL_Renderer *renderer, int xc, int yc, int s, double angle = 0.0) {
    short int xv[6] = {0};
    short int yv[6] = {0};
    float xs, xp;
    float ys, yp;

    double cos60 = 0.5e0;
    double sin60 = 0.5e0 * sqrt(3e0);

    xp = s*cos(angle);
    yp = s*sin(angle);

    xv[0] = round(xc + xp);
    yv[0] = round(yc + yp);

    // Rotate each vertex 60 degrees
    for (int i = 1; i < 6; i++) {
        xs = cos60 * xp + sin60 * yp;
        ys = cos60 * yp - sin60 * xp;
        xv[i] = round(xc + xs);
        yv[i] = round(yc + ys);
        xp = xs;
        yp = ys;
    }

    filledPolygonRGBA(renderer, xv, yv, 6, 255, 255, 255, 255);
    polygonRGBA(renderer, xv, yv, 6, 0, 0, 0, 255);
    return 0;
}

int drawgame(SDL_Renderer* renderer, int gameField[7][7][6]){
    int s = 30;
    float vx[2] = {s * 1.5, sqrt(3)/2*s};
    float vy[2] = {0.0, sqrt(3) * s};

    int xc = s, yc = s;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            xc = s + vx[0] * i + vy[0] * j;
            yc = s + vx[1] * i + vy[1] * j;
            if (gameField[i][j][0] > -1)
                drawhex(renderer, xc, yc, s, 0.0);
        }
    }
    return drawhex(renderer, WINDOW_WIDTH - s, WINDOW_HEIGHT - s, s, 6.28e-4 * (SDL_GetTicks() % 10000));
}