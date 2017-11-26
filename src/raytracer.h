#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "../framework/color.h"
#include "list.h"
#include "light.h"
#include "sphere.h"
#include "scene.h"
#include "intersection.h"

Color follow_ray(Scene* scene, Vec3* O, Vec3* D, float minLambda, float maxLambda, int recursionLimit);

Color lambert(Vec3* P, Vec3* N, Light* L, Material material);

#endif //RAYTRACER_H
