#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#ifdef __cplusplus
extern "C"{
#endif

#include "SDL3/SDL.h"
#include "../colors.h"
#include "../main.h"

typedef void ColorPickerHandle;


ColorPickerHandle* color_picker_new(SDL_Renderer* renderer);
bool color_picker_draw(ColorPickerHandle *picker);
void color_picker_free(ColorPickerHandle *picker);
Uint32 color_picker_get_color(ColorPickerHandle *picker);


#ifdef __cplusplus
}
#endif

#endif