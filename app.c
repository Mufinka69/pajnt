#include "app.h"
#include "init_sdl.h"

void app_events(App *g);
void app_update(App *g);
void app_draw(App *g);

bool app_new(App **app) {
    *app = (App*)calloc(1, sizeof(App));
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

    if(!pencil_new(&a->pencil, a->canvas)){
        return false;
    }

    a->gui = gui_create(a->window, a->renderer);  // <-- Tworzymy GUI
    a->menu = menubar_new(a->renderer);

    a->is_running = true;

    return true;
}

void app_free(App **app) {
    if (*app) {
        App *a = *app;


        if(a->menu){
            menubar_free(a->menu);
            a->menu = NULL;
        }

        if (a->gui) {
            gui_destroy(a->gui);
            a->gui = NULL;
        }

        if(a->pencil){
            pencil_free(&a->pencil);
        }

        if (a->canvas){
            canvas_free(&a->canvas);
        }
        
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
        ImGui_ImplSDL3_ProcessEvent(&a->event);

        canvas_move(a->canvas, a->event);
        canvas_zoom(a->canvas, a->event);        
        switch (a->event.type) {
        case SDL_EVENT_QUIT:
            a->is_running = false;
            break;        
        default:
            break;
        }
    }
}


void app_handle_menu_cmd(App *a){
    MenuCommand cmd = menubar_poll_command(a->menu);
    switch(cmd) {
        case MENU_NEW:
            canvas_free(&a->canvas);
            canvas_new(&a->canvas, a->renderer);

            pencil_free(&a->pencil);
            pencil_new(&a->pencil, a->canvas);
            break;
        case MENU_OPEN:
            /* wczytaj obraz */
            break;
        case MENU_SAVE:
            /* zapisz obraz */
            break;
        case MENU_EXIT:
            a->is_running = false;
            break;
        default:
            break;
    }
}

void app_update(App *a){
    // pencil_draw(a->pencil);
    draw_lineH((Vector2){3, 3}, (Vector2){10, 5}, a->canvas);
    draw_lineV((Vector2){3, 3}, (Vector2){3, 10}, a->canvas);
    draw_line(a->pencil);
    // pencil_draw_line(a->pencil);
    if(is_mouse_button_down(SDL_BUTTON_LEFT)){
        printf("SDL_BUTTON_LEFT\n");
    }

    if(is_mouse_button_down(SDL_BUTTON_RIGHT)){
        printf("SDL_BUTTON_RIGHT\n");
    }
    app_handle_menu_cmd(a);

    SDL_UpdateTexture(a->pencil->canvas->texture, NULL, a->pencil->canvas->surface->pixels, a->pencil->canvas->surface->pitch);
}

void app_draw(App *a) {
    SDL_RenderClear(a->renderer);
    canvas_draw(a->canvas); 
    gui_new_frame(a->gui); 

    menubar_draw(a->menu);
    gui_render(a->gui);    

    SDL_RenderPresent(a->renderer);
}

void app_run(App *a) {
    while (a->is_running){
        app_events(a);
        app_update(a);

        app_draw(a);
    }
}