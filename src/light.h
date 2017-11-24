#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

typedef struct {
    Vec3* position;
    float intensity; 
} Light;

Light* light_new(float x, float y, float z, float intensity);

void light_free(Light* light);

void light_print(Light* light);

#endif //LIGHT_H
