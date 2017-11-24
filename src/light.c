#include <stdio.h>
#include <stdlib.h>
#include "../framework/mm.h"
#include "light.h"


Light* light_new(float x, float y, float z, float intensity)
{
    Light *light = (Light *) cg_malloc(sizeof(Light));
    light->position = vec3_new(x, y, z);
    light->intensity = intensity;

    return light;
}

void light_free(Light* light)
{
    vec3_free(light->position);
    cg_free(light);
}

void light_print(Light* light)
{
    printf("%s\n", "Position:");
    vec3_print(light->position);
    printf("Intensity: %f\n", light->intensity);
}
