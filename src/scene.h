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
    float vw;
    float vh;
    float distance; // Distancia al plano de proyección.
} Scene;

Scene* scene_new();

void scene_free(Scene* scene);

void scene_print(Scene* scene);

#endif //SCENE_H
