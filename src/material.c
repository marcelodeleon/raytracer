#include <stdio.h>
#include <stdlib.h>
#include "../framework/mm.h"
#include "material.h"

Material* material_new(Color specularColor, Color diffuseColor, float specularExponent, float reflectionFraction)
{
    Material* material = (Material *) cg_malloc(sizeof(Material));
    material->specularColor = specularColor;
    material->diffuseColor = diffuseColor;
    material->specularExponent = specularExponent;
    material->reflectionFraction = reflectionFraction;

    return material;
}

void material_free(Material* material)
{
    cg_free(material);
}

void material_print(Material* material)
{
    printf("%s\n", "Color especular: ");
    cg_color_print(material->specularColor);
    printf("%s\n", "Color difuso: ");
    cg_color_print(material->diffuseColor);
    printf("Exponente especular: %f\n", material->specularExponent);
    printf("Fracción de reflexión: %f\n", material->reflectionFraction);
}
