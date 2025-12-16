#include "pencil.h"

bool pencil_new(Pencil **pencil, Canvas *canvas){
    *pencil = calloc(1, sizeof(Pencil));
    if (*pencil == NULL) {
        fprintf(stderr, "Error Calloc of Pencil.\n");
        return false;
    }
    Pencil *p = *pencil;

    p->canvas = canvas;
    p->color = RED;
    p->size = 10;
    p->tooltype = PEN;
    return true;
}

void pencil_free(Pencil **pencil){
    if(*pencil){
        Pencil *p = *pencil;
        free(p);
        p = NULL;
        *pencil = NULL;
        printf("Pen free\n");
    }
}

void pencil_draw(Pencil *p){
    Vector2 mouse_pos;
    SDL_MouseButtonFlags mouse_flags =  SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    if(check_collision_point_rect(mouse_pos, p->canvas->rect)){
        put_pixel(p->canvas, mouse_pos.x - p->canvas->rect.x, mouse_pos.y - p->canvas->rect.y, RED);
        printf("%f, %f \n", mouse_pos.x - p->canvas->rect.x, mouse_pos.y - p->canvas->rect.y);
    }
    SDL_UpdateTexture(p->canvas->texture, NULL, p->canvas->surface->pixels, p->canvas->surface->pitch);
}
