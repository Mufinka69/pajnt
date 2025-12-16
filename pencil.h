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
}Pencil;


bool pencil_new(Pencil **pencil, Canvas *canvas);
void pencil_free(Pencil **pencil);
void pencil_draw(Pencil *pencil);

#endif