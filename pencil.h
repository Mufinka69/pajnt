#ifndef PENCIL_H
#define PENCIL_H

#include "main.h"
#include "canvas.h"

typedef enum {
    PEN
}ToolType;

typedef struct{
    Canvas *canvas;
    ToolType tooltype;
    int size;
    Uint32 color;
    bool is_drawing;
    Vector2 previous_pos;
}Pencil;


bool pencil_new(Pencil **pencil, Canvas *canvas);
void pencil_free(Pencil **pencil);
void pencil_draw(Pencil *pencil);
void draw_lineH(Vector2 a, Vector2 b, Canvas *c);
void draw_lineV(Vector2 a, Vector2 b, Canvas *c);
void pencil_draw_line(Pencil *pencil);
void draw_line(Pencil *p);


#endif