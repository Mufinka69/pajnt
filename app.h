#ifndef APP_H
#define APP_H

#include "main.h"
#include "canvas.h"
#include "pencil.h"

#include "gui/gui.h"
#include "gui/menubar.h"

typedef struct{
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        TTF_Font *font; 
        bool is_running;
        //inne hujstwa
        Canvas *canvas;
        Pencil *pencil;
        //gui
        ImGuiHandle* gui;  
        MenuBarHandle* menu;
}App;

bool app_new(App **app);
void app_free(App **app);
void app_run(App *g);

#endif