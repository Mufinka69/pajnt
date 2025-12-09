#ifndef APP_H
#define APP_H

#include "main.h"
#include "canvas.h"

typedef struct{
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        TTF_Font *font; 
        bool is_running;
        //tools
        Canvas *canvas;
}App;

bool app_new(App **app);
void app_free(App **app);
void app_run(App *g);

#endif