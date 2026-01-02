#ifndef MENUBAR_H
#define MENUBAR_H

#ifdef __cplusplus
extern "C"{
#endif

#include "SDL3/SDL.h"

typedef void MenuBarHandle;


MenuBarHandle* menubar_new(SDL_Renderer* renderer);
void menubar_draw(MenuBarHandle *menu);
void menubar_free(MenuBarHandle *menu);

typedef enum{
    MENU_NONE,
    MENU_NEW,
    MENU_OPEN,
    MENU_SAVE,
    MENU_EXIT
}MenuCommand ;

MenuCommand menubar_poll_command(MenuBarHandle *menu);

#ifdef __cplusplus
}
#endif

#endif