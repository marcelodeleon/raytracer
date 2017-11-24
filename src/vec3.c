#include <stdio.h>
#include <stdlib.h>
#include "../framework/mm.h"
#include "vec3.h"

Vec3* vec3_new(float x, float y, float z)
{
    Vec3 *vec3 = (Vec3 *) cg_malloc(sizeof(Vec3));
    vec3->x = x;
    vec3->y = y;
    vec3->z = z;

    return vec3;
}

void vec3_free(Vec3* vec3)
{
    cg_free(vec3);
}

void vec3_print(Vec3* vec3)
{
    printf("Vec3 -> { x: %f, y: %f, z %f }\n", vec3->x, vec3->y, vec3->z);
}
