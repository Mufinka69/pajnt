#include "vector2.h"


float vec2_length(Vector2 v){
    return sqrtf(v.x * v.x + v.y * v.y);
}

float vec2_distance(Vector2 a, Vector2 b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx*dx + dy*dy);
}

Vector2 vec2_sub(Vector2 a, Vector2 b){
    return (Vector2){a.x - b.x, a.y - b.y};
}

bool check_collision_point_rect(Vector2 point, SDL_FRect rect){
    return (point.x >= rect.x &&
            point.x <= rect.x + rect.w &&
            point.y >= rect.y &&
            point.y <= rect.y + rect.h);
}
