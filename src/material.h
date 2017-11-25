#ifndef MATERIAL_H
#define MATERIAL_H

#include "../framework/color.h"

typedef struct {
    Color specularColor;
    Color diffuseColor;
    float specularExponent; // Es -1 si no tiene reflexión especular.
    float reflectionFraction;
} Material;

Material* material_new(Color specularColor, Color diffuseColor, float specularExponent, float reflectionFraction);

void material_free(Material* material);

void material_print(Material* material);

#endif //MATERIAL_H
