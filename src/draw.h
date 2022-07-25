#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>

int draw(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);

int drawhex(SDL_Renderer *renderer, int xc, int yc, int s, double angle);

int drawgame(SDL_Renderer *renderer, int gameField[7][7][6]);