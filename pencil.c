#include "pencil.h"


void pencil_draw_line(Pencil *p);

bool pencil_new(Pencil **pencil, Canvas *canvas){
    *pencil = (Pencil*)calloc(1, sizeof(Pencil));
    if (*pencil == NULL) {
        fprintf(stderr, "Error Calloc of Pencil.\n");
        return false;
    }
    Pencil *p = *pencil;

    p->canvas = canvas;
    p->color = RED;
    p->size = 10;
    p->tooltype = PEN;
    p->is_drawing = false;
    p->previous_pos = (Vector2){-1, -1};
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
    const bool* key_state = SDL_GetKeyboardState(NULL);
    SDL_MouseButtonFlags mouse_flags =  SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    SDL_FRect rect;
    rect.h = p->canvas->rect.h * p->canvas->zoom;
    rect.w = p->canvas->rect.w * p->canvas->zoom;
    rect.x = p->canvas->rect.x;
    rect.y = p->canvas->rect.y;
    
    // 0 ... 32
    float x = ((mouse_pos.x) - (p->canvas->rect.x))/p->canvas->zoom;
    float y = ((mouse_pos.y) - (p->canvas->rect.y))/p->canvas->zoom;

    if (mouse_flags & SDL_BUTTON_LEFT && !key_state[SDL_SCANCODE_LCTRL]) {
        if(check_collision_point_rect(mouse_pos, rect)){
            put_pixel(p->canvas, x, y, RED);
            printf("rysuje\n");
        }
    }
}

// a^b^b = a

void draw_lineH(Vector2 a, Vector2 b, Canvas *c)
{
    if (a.x > b.x) {
        Vector2 tmp = a;
        a = b;
        b = tmp;
    }

    int dx = b.x - a.x;
    int dy = b.y - a.y;
    if (dx == 0){
        return;
    }


    int dir = (dy < 0) ? -1 : 1;
    dy = abs(dy);

    int y = a.y;
    int p = 2 * dy - dx;

    for (int x = a.x; x <= b.x; x++) {
        put_pixel(c, x, y, BLUE);
        if (p >= 0) {
            y += dir;
            p -= 2 * dx;
        }
        p += 2 * dy;
    }
}


void draw_lineV(Vector2 a, Vector2 b, Canvas *c)
{
    if (a.y > b.y) {
        Vector2 tmp = a;
        a = b;
        b = tmp;
    }

    int dx = b.x - a.x;
    int dy = b.y - a.y;
    if (dy == 0){
        return;
    }

    int dir = (dx < 0) ? -1 : 1;
    dx = abs(dx);

    int x = a.x;
    int p = 2 * dx - dy;
    for (int y = a.y; y <= b.y; y++) {
        put_pixel(c, x, y, RED);
        if (p >= 0) {
            x += dir;
            p -= 2 * dy;
        }
        p += 2 * dx;
    }
}


void draw_line_general(Vector2 a, Vector2 b, Canvas *c) {
    int dx = abs(b.x - a.x);
    int sx = (a.x < b.x) ? 1 : -1;

    int dy = -abs(b.y - a.y);
    int sy = (a.y < b.y) ? 1 : -1;

    int err = dx + dy;
    int e2;

    while (true) {
        put_pixel(c, a.x, a.y, RED);
        if (a.x == b.x && a.y == b.y) break;
        e2 = 2 * err;
        if (e2 >= dy){ err += dy; a.x += sx;}
        if (e2 <= dx){ err += dx; a.y += sy;}
    }
}



void draw_line(Pencil *p){
    Vector2 mouse_pos;
    const bool* key_state = SDL_GetKeyboardState(NULL);
    SDL_MouseButtonFlags mouse_flags =  SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    SDL_FRect rect;
    rect.h = p->canvas->rect.h * p->canvas->zoom;
    rect.w = p->canvas->rect.w * p->canvas->zoom;
    rect.x = p->canvas->rect.x;
    rect.y = p->canvas->rect.y;
    
    // 0 ... 32
    int x = ((mouse_pos.x) - (p->canvas->rect.x))/p->canvas->zoom;
    int y = ((mouse_pos.y) - (p->canvas->rect.y))/p->canvas->zoom;

    int prev_x = ((p->previous_pos.x) - (p->canvas->rect.x))/p->canvas->zoom;
    int prev_y = ((p->previous_pos.y) - (p->canvas->rect.y))/p->canvas->zoom;
    

    if (is_mouse_button_down(SDL_BUTTON_LEFT) && !key_state[SDL_SCANCODE_LCTRL]) {
        if(check_collision_point_rect(mouse_pos, rect)){
            printf("H :%d, %d -> %d, %d\n", prev_x , prev_y, x, y);
            // printf("linia\n");
            if(p->previous_pos.x == -1){
                p->previous_pos = mouse_pos;
                return;
            }
            draw_line_general((Vector2){(float)prev_x, (float)prev_y}, (Vector2){(float)x, (float)y}, p->canvas);
            p->previous_pos = mouse_pos;
        }
    }else{
        p->previous_pos.x = -1;
        p->previous_pos.y = -1;
    }
}