#ifndef SCENE_H
#define SCENE_H

#include "list.h"
#include "vec3.h"
#include "light.h"
#include "sphere.h"

typedef struct
{
    List* lights; // Luces puntuales.
    List* spheres;
    Vec3* camera; // Posición de la cámara.
    float ambienceLight;
    // viewport[0] es viewportWidth.
    // viewport[1] es viewportHeight.
    float viewport[2];
    float distance; // Distancia al plano de proyección.
} Scene;

Scene* scene_new(Vec3* camera, float viewportWidth, float viewportHeight, float distance);

void scene_free(Scene* scene);

void scene_print(Scene* scene);

#endif //SCENE_H
