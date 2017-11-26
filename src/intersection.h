#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <math.h>
#include "utils.h"
#include "scene.h"
#include "sphere.h"

typedef struct
{
    Sphere* sphere;
    float closestLambda; // Lambda más cercano a la cámara, siempre es el lambda más chico.
} Intersection;

Intersection* intersection_new();

void intersection_free(Intersection* intersection);

float intersectWithSphere(Vec3* O, Vec3* D, Sphere* sphere);

Intersection* intersect(Scene* scene, Vec3* O, Vec3* D, float minLambda, float maxLambda);

#endif //INTERSECTION_H
