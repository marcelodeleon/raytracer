#ifndef VEC3_H
#define VEC3_H

typedef struct {
    float x; 
    float y; 
    float z; 
} Vec3;

Vec3* vec3_new(float x, float y, float z);

// Producto punto.
float vec3_dot(Vec3* v1, Vec3* v2); 

// Producto cruz.
Vec3* vec3_cross(Vec3* v1, Vec3* v2); 

void vec3_free(Vec3* vec3); 

void vec3_print(Vec3* vec3);

#endif //VEC3_H
