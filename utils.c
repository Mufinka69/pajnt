#include "main.h"
#include "vector2.h"

bool check_collision_point_rect(Vector2 point, SDL_FRect rect){
    return (point.x >= rect.x &&
            point.x <= rect.x + rect.w &&
            point.y >= rect.y &&
            point.y <= rect.y + rect.h);
}