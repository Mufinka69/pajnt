#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>
#include <SDL3/SDL.h>

typedef struct{
    float x, y;
}Vector2;

float vec2_length(Vector2 v);
float vec2_distance(Vector2 a, Vector2 b);
Vector2 vec2_sub(Vector2 a, Vector2 b);


bool check_collision_point_rect(Vector2 point, SDL_FRect rect);
bool is_mouse_button_down(int button);


#endif