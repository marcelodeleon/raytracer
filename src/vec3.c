#include <stdio.h>
#include <math.h>
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

float vec3_dot_product(Vec3* v1, Vec3* v2)
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

Vec3* vec3_cross_product(Vec3* v1, Vec3* v2)
{
    float x = v1->y * v2->z - v1->z * v2->y;
    float y = v1->x * v2->z - v1->z * v2->x;
    float z = v1->x * v2->y - v1->y * v2->x;
    Vec3 *result = vec3_new(x, y, z);
    
    return result;
}

Vec3* vec3_mult_by_scalar(Vec3* v, float scalar)
{
    float x = v->x * scalar;
    float y = v->y * scalar;
    float z = v->z * scalar;
    Vec3* result = vec3_new(x, y, z);

    return result;
}

float vec3_norm(Vec3* v)
{
    return sqrt(vec3_dot_product(v, v));
}

Vec3* vec3_normalize(Vec3* v)
{
    float norm = vec3_norm(v);
    Vec3* normalized = vec3_mult_by_scalar(v, 1/norm);

    return normalized;
}

Vec3* vec3_add(Vec3* v1, Vec3* v2)
{
    float x = v1->x + v2->x;
    float y = v1->y + v2->y;
    float z = v1->z + v2->z;
    Vec3* result = vec3_new(x, y, z);

    return result;
}

float vec3_normalized_dot_product(Vec3* v1, Vec3* v2)
{
    float normV1 = vec3_norm(v1);
    float normV2 = vec3_norm(v2);

    return vec3_dot_product(v1, v2) / ( normV1 * normV2 );
}

Vec3* vec3_diff(Vec3* v1, Vec3* v2)
{
    float x = v1->x - v2->x;
    float y = v1->y - v2->y;
    float z = v1->z - v2->z;
    Vec3* result = vec3_new(x, y, z);

    return result;
}

void vec3_free(Vec3* vec3)
{
    cg_free(vec3);
}

void vec3_print(Vec3* vec3)
{
    printf("Vec3 -> { x: %f, y: %f, z %f }\n", vec3->x, vec3->y, vec3->z);
}
