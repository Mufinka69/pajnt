#ifndef CANVAS_H
#define CANVAS_H

#include "main.h"
#include "colors.h"

typedef struct{
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    size_t x;
    size_t y;
    float zoom;
    SDL_FRect rect;
}Canvas;

bool canvas_new(Canvas **canvas, SDL_Renderer *renderer);
bool canvas_free(Canvas **canvas);
void put_pixel(Canvas *c, int x, int y, Uint32 color);
void canvas_draw(Canvas *c);
void canvas_zoom(Canvas *c, SDL_Event event);
void canvas_move(Canvas *c);
void canvas_update(Canvas *c);

#endif
