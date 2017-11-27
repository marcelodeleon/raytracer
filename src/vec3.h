#ifndef VEC3_H
#define VEC3_H

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

Vec3* vec3_new(float x, float y, float z);

// Producto punto.
float vec3_dot_product(Vec3* v1, Vec3* v2);

// Producto cruz.
Vec3* vec3_cross_product(Vec3* v1, Vec3* v2);

Vec3* vec3_mult_by_scalar(Vec3* v, float scalar);

/*
 * Retorna la norma de un vector.
 */
float vec3_norm(Vec3* v);

/*
 * Retorna el vector normalizado.
 */
Vec3* vec3_normalize(Vec3* v);

/*
 * Retorna el producto punto entre los vectores, dividido entre la multiplicación de sus normas.
 */
float vec3_normalized_dot_product(Vec3* v1, Vec3* v2);

Vec3* vec3_add(Vec3* v1, Vec3* v2);

Vec3* vec3_diff(Vec3* v1, Vec3* v2);

void vec3_free(Vec3* vec3);

void vec3_print(Vec3* vec3);

#endif //VEC3_H
