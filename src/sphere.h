#ifndef SPHERE_H
#define SPHERE_H

#include "material.h"
#include "vec3.h"

typedef struct {
	Material* material; // Contiene todas las propiedades del material de la esfera.
    Vec3 *center;
	float radius;
} Sphere;

Sphere* sphere_new(Material* material, Vec3* center, float radius);

void sphere_free(Sphere* sphere);

void sphere_print(Sphere* sphere);

#endif //SPHERE_H
