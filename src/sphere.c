#include <stdio.h>
#include <stdlib.h>
#include "../framework/mm.h"
#include "sphere.h"

Sphere* sphere_new(Material* material, Vec3* center, float radius)
{
    Sphere *sphere = (Sphere *) cg_malloc(sizeof(Sphere));
    sphere->material = material;
    sphere->center = center;
    sphere->radius = radius;

    return sphere;
}

void sphere_free(Sphere* sphere)
{
    vec3_free(sphere->center);
    cg_free(sphere);
}

void sphere_print(Sphere* sphere)
{
    material_print(sphere->material);
    vec3_print(sphere->center);
    printf("Radius: %f\n", sphere->radius);
}
