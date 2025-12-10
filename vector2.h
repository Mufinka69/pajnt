#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

typedef struct{
    float x, y;
}Vector2;

float vec2_length(Vector2 v);
float vec2_distance(Vector2 a, Vector2 b);
Vector2 vec2_sub(Vector2 a, Vector2 b);

#endif