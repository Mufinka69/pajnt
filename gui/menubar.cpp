#include "menubar.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"


struct MenuBar{
    SDL_Renderer *renderer;
    MenuCommand last_command = MENU_NONE;

    void draw(){
        if(!ImGui::BeginMainMenuBar()){ return; }

        if(ImGui::BeginMenu("File")){
            if (ImGui::MenuItem("New", "Ctrl+N")) last_command = MENU_NEW;
            if (ImGui::MenuItem("Open", "Ctrl+O")) last_command = MENU_OPEN;
            if (ImGui::MenuItem("Save", "Ctrl+S")) last_command = MENU_SAVE;
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) last_command = MENU_EXIT;
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    MenuCommand poll_command(){
        MenuCommand command = last_command;
        last_command = MENU_NONE;
        return command;
    }
};


extern "C"{
    MenuBarHandle* menubar_new(SDL_Renderer *renderer){
        return reinterpret_cast<MenuBarHandle*>(new MenuBar{renderer});
    }

    void menubar_draw(MenuBarHandle* menu){
        reinterpret_cast<MenuBar*>(menu)->draw();
    }

    void menubar_free(MenuBarHandle *menu){
        delete reinterpret_cast<MenuBar*>(menu);
    }

    MenuCommand menubar_poll_command(MenuBarHandle *menu){
        return reinterpret_cast<MenuBar*>(menu)->poll_command();
    }
}