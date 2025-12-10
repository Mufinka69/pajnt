#include "canvas.h"
#include "vector2.h"


void put_pixel(Canvas *c, int x, int y, Uint32 color);


bool canvas_new(Canvas **canvas, SDL_Renderer *renderer){
    *canvas = calloc(1, sizeof(Canvas));
    Canvas *c = *canvas;

    c->ctrl_was_pressed = false;
    c->dst =(Vector2){0, 0};

    c->zoom = 1.0;
    c->rect = (SDL_FRect){200, 200, 200, 200};
    c->renderer = renderer;
    c->surface = SDL_CreateSurface(32, 32, SDL_PIXELFORMAT_RGBA8888);
    
    if (c->surface == NULL) {
        SDL_Log("CreateRGBSurface failed: %s", SDL_GetError());
        // exit(1);
        return false;
    }
    SDL_FillSurfaceRect(c->surface, NULL, WHITE);
    c->texture = SDL_CreateTextureFromSurface(c->renderer, c->surface);
    SDL_SetTextureScaleMode(c->texture, SDL_SCALEMODE_NEAREST);
    if (c->texture == NULL) {
        SDL_Log("CreateTextureFromSurface failed: %s", SDL_GetError());
        // exit(1);
        return false;
    }

    int w = c->surface->w;
    int h = c->surface->h;
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            if((i + j)%2 == 0){
                put_pixel(c, i, j, WHITE);
            }else{
                put_pixel(c, i, j, GREY);
            }
        }
    }

    SDL_UpdateTexture(c->texture, NULL, c->surface->pixels, c->surface->pitch);

    return true;
}
bool canvas_free(Canvas **canvas){
    if(*canvas){
        Canvas *c = *canvas;
        free(c);
        c = NULL;
        *canvas = NULL;
        printf("Canvas Free!\n");
    }
}

void put_pixel(Canvas *c, int x, int y, Uint32 color){
    Uint8* p = (Uint8*)c->surface->pixels + y * c->surface->pitch + x * 4; 
    *(Uint32*)p = color;
}

void canvas_zoom(Canvas *c, SDL_Event event){
    switch (event.type)
    {
    case SDL_EVENT_MOUSE_WHEEL:
        if(SDL_GetModState() & SDL_KMOD_CTRL){
            if(event.wheel.y > 0){
                c->zoom *= 1.1;
                printf("plus\n");
            }else if(event.wheel.y < 0){
                c->zoom *= 0.9;
                printf("minus\n");
            }
        }
        break;
    default:
        break;
    }
}

void canvas_move(Canvas *c, SDL_Event event){
    const bool* key_state = SDL_GetKeyboardState(NULL);
    float x, y;
    SDL_MouseButtonFlags mouse_flags =  SDL_GetMouseState(&x, &y);
    Vector2 mouse_pos = {x, y};
    Vector2 rect_pos = {c->rect.x, c->rect.y};
    switch (event.type)
    {
    case SDL_EVENT_KEY_DOWN:
        if (key_state[SDL_SCANCODE_LCTRL] && key_state[SDL_SCANCODE_LEFT]){
            c->rect.x -= 1;
            printf("left\n");
        }
        if (key_state[SDL_SCANCODE_LCTRL] && key_state[SDL_SCANCODE_DOWN]){
            c->rect.y += 1;
            printf("down\n");
        }
        if (key_state[SDL_SCANCODE_LCTRL] && key_state[SDL_SCANCODE_RIGHT]){
            c->rect.x += 1;
            printf("right\n");
        }
        if (key_state[SDL_SCANCODE_LCTRL] && key_state[SDL_SCANCODE_UP]){
            c->rect.y -= 1;
            printf("up\n");
        }
        break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if(mouse_flags & SDL_BUTTON_LMASK){
                if(!c->ctrl_was_pressed){
                    c->ctrl_was_pressed = true;
                    printf("klik\n");
                    c->dst = vec2_sub(mouse_pos, rect_pos);                
                }
            }
            break;
        case SDL_EVENT_MOUSE_MOTION:
            // if(czy mysz na płótnie)

            if(c->ctrl_was_pressed ){
                if((mouse_flags & SDL_BUTTON_LMASK) && key_state[SDL_SCANCODE_LCTRL]){
                    c->rect.y = mouse_pos.y - c->dst.y;
                    c->rect.x = mouse_pos.x - c->dst.x;                    
                }
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            if(event.button.button == SDL_BUTTON_LEFT){
                c->ctrl_was_pressed = false;
                printf("up\n");
            }
        break;
    default:
        break;
    }
}

// void canvas_update(Canvas *c){
//     // canvas_move(c);
// }

void canvas_draw(Canvas *c){
    SDL_FRect n_rect = (SDL_FRect){c->rect.x, c->rect.y, c->rect.h * c->zoom, c->rect.w * c->zoom};
    SDL_RenderTexture(c->renderer, c->texture, NULL, &n_rect);
}