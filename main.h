#ifndef MAIN_H
#define MAIN_H

#define SDL_MAIN_HANDLED

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "vector2.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#define SDL_FLAGS SDL_INIT_VIDEO

#define WINDOW_TITLE "asdas"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#endif