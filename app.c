#include "app.h"
#include "init_sdl.h"

void app_events(App *g);
void app_update(App *g);
void app_draw(App *g);

bool app_new(App **app) {
    *app = calloc(1, sizeof(App));
    if (*app == NULL) {
        fprintf(stderr, "Error Calloc of New App.\n");
        return false;
    }
    App *a = *app;


    if (!app_init_sdl(a)) {
        return false;
    }

    if(!canvas_new(&a->canvas, a->renderer)){
        return false;
    }

    a->is_running = true;

    return true;
}

void app_free(App **app) {
    if (*app) {
        App *a = *app;

        if(a->font){
            TTF_CloseFont(a->font);
            a->font = NULL;
        }

        if (a->renderer) {
            SDL_DestroyRenderer(a->renderer);
            a->renderer = NULL;
        }
        if (a->window) {
            SDL_DestroyWindow(a->window);
            a->window = NULL;
        }

        TTF_Quit();
        SDL_Quit();

        free(a);

        a = NULL;
        *app = NULL;

        printf("All Clean!\n");
    }
}

void app_events(App *a) {
    while (SDL_PollEvent(&a->event)) {
        switch (a->event.type) {
        case SDL_EVENT_QUIT:
            a->is_running = false;
            break;        
        case SDL_EVENT_MOUSE_WHEEL:
            if(SDL_GetModState() & SDL_KMOD_CTRL)
                canvas_zoom(a->canvas, a->event);
            break;
        default:
            break;
        }
    }
}

void app_update(App *a){
    canvas_update(a->canvas);
}

void app_draw(App *a) {
    SDL_RenderClear(a->renderer);
    canvas_draw(a->canvas);
    SDL_RenderPresent(a->renderer);
}

void app_run(App *a) {
    while (a->is_running){
        app_events(a);
        app_update(a);
        app_draw(a);
    }
}