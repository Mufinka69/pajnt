#include "menu.h"


void open_file(Canvas *a);



            // selected_color = 
            //     ((Uint32)(color[3] * 255) << 24) |
            //     ((Uint32)(color[0] * 255) << 16) |
            //     ((Uint32)(color[1] * 255) << 8)  |
            //     ((Uint32)(color[2] * 255));

Uint32 get_color(const Canvas *c, int x, int y){
    Uint8* p = (Uint8*)c->surface->pixels + y * c->surface->pitch + x * 4; 
    return *(Uint32*)p;
}


void save_file(const Canvas *c){
    FILE *f = fopen("obrazek.ppm", "wb");
    int w = 128;
    int h = 128;
    fprintf(f, "P6\n");
    fprintf(f, "%d %d\n", w, h);
    fprintf(f, "255\n");
    Uint32 color32 = 0;
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            color32 = get_color(c, j, i);
            int r = (color32 >> 16) & ((1 << 8) - 1);
            int g = (color32 >> 8) & ((1 << 8) - 1);
            int b = (color32 >> 0) & ((1 << 8) - 1);
            fputc(r, f);
            fputc(g, f);
            fputc(b, f);
        }
    }
    fclose(f);
    printf("saved file as .ppm\n");
}