#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "../framework/color.h"
#include "list.h"
#include "light.h"
#include "sphere.h"
#include "scene.h"
#include "intersection.h"
#include "utils.h"

Color trace_ray(Scene* scene, Vec3* O, Vec3* D, float minLambda, float maxLambda, int recursionLimit);

/*
 * Implementación del modelo de iluminación de Lambert extendido.
 */
Color lambert(Vec3* P, Vec3* N, Vec3* V, Vec3* L, Light* light, Material* material, float ambienceLight);

#endif //RAYTRACER_H
