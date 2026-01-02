#include "gui.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

struct Gui {
    SDL_Renderer* renderer;
};

extern "C" {

ImGuiHandle* gui_create(SDL_Window* window, SDL_Renderer* renderer) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    Gui* g = new Gui;
    g->renderer = renderer;
    return (ImGuiHandle*)g;
}

void gui_new_frame(ImGuiHandle*) {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void gui_render(ImGuiHandle* gui) {
    Gui* g = reinterpret_cast<Gui*>(gui);
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), g->renderer);
}

void gui_destroy(ImGuiHandle* gui) {
    Gui* g = reinterpret_cast<Gui*>(gui);
    delete g;

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
} 
