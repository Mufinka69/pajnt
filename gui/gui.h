#ifdef __cplusplus
extern "C" {
#endif

#include <SDL3/SDL.h>

typedef void ImGuiHandle;

ImGuiHandle* gui_create(SDL_Window* window, SDL_Renderer* renderer);
void gui_new_frame(ImGuiHandle* gui);
void gui_render(ImGuiHandle* gui);
void gui_destroy(ImGuiHandle* gui);

#ifdef __cplusplus
}
#endif
