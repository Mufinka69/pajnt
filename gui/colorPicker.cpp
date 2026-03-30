#include "colorPicker.h"

struct ColorPicker{
    SDL_Renderer *renderer;
    Uint32 selected_color = BLACK;
    float color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
    ImVec4 palette[6] = {{0, 0, 0, 1}, {0, 0, 1, 1},{0, 1, 1, 1},{1, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 0, 1}};
    int palette_index = 0;

    void draw(){
        int w = 100, h = 200;
        float topOffset = ImGui::GetFrameHeight();
        ImGui::SetNextWindowPos(ImVec2(WINDOW_WIDTH - w, topOffset), ImGuiCond_Once);

        for (int i = 0; i < 6; i++){
            char string[3];
            sprintf(string, "%d", i);
            if(ImGui::ColorButton(string, palette[i])){
                color[0] = palette[i].x;
                color[1] = palette[i].y;
                color[2] = palette[i].z;
                color[3] = palette[i].w;
                ImGui::OpenPopup("Picker");
                palette_index = i;
                ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
            }
            if(i%2 == 0){
                ImGui::SameLine();
            }
        }
        if(ImGui::BeginPopup("Picker")){
            ImGui::ColorPicker4("##picker", color);
            ImGui::EndPopup();
            palette[palette_index].x = color[0];
            palette[palette_index].y = color[1];
            palette[palette_index].z = color[2];
            palette[palette_index].w = color[3];
        }
    }

    Uint32 get_color(){
        return selected_color;
    }

};


extern "C"{
    ColorPickerHandle* color_picker_new(SDL_Renderer *renderer){
        return reinterpret_cast<ColorPickerHandle*>(new ColorPicker{renderer});
    }

    void color_picker_draw(ColorPickerHandle* picker){
        reinterpret_cast<ColorPicker*>(picker)->draw();
    }

    Uint32 color_picker_get_color(ColorPickerHandle *picker){
        return reinterpret_cast<ColorPicker*>(picker)->get_color();
    }

    void color_picker_free(ColorPickerHandle *picker){
        delete reinterpret_cast<ColorPicker*>(picker);
    }
}