#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <math.h>
#include <float.h>
#include "../framework/color.h"
#include "../framework/mm.h"
#include "vec3.h"
#include "list.h"
#include "light.h"
#include "sphere.h"
#include "scene.h"

/* Como calculamos las intersecciones con esferas matemáticamente perfectas, puede ser posible que el punto
 * interceptado esté dentro de la esfera (por cálculos computacionales). Por eso, definimos la siguiente
 * constante EPSILON que nos asegura que el punto de intersección se mueva un poquito hacia afuera de la
 * esfera.
 * */
#define EPSILON 0.001f

// Defino el infiníto como el float más grande que C puede representar.
#define INF FLT_MAX

typedef struct
{
    Sphere* sphere;
    float closestLambda; // Lambda más cercano a la cámara, siempre es el lambda más chico.
} Intersection;

Intersection* intersection_new();

void intersection_free(Intersection* intersection);

float min(float a, float b);

float solveCuadraticEquation(float a, float b, float c);

float intersectWithSphere(Vec3* O, Vec3* D, Sphere* sphere);

Intersection* intersect(Scene* scene, Vec3* O, Vec3* D, float minLambda, float maxLambda);

Color follow_ray(Scene* scene, Vec3* O, Vec3* D, float minLambda, float maxLambda, int recursionLimit);

Color lambert(Vec3* P, Vec3* N, Light* L, Material material);

#endif //RAYTRACER_H
