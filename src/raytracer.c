#include "raytracer.h"

Color lambert(Vec3* P, Vec3* N, Vec3* V, Vec3* L, Light* light, Material* material, float ambienceLight)
{

    // Factor que multiplica al color difuso en la ecuación de lambert extendida.
    float diffuseFactor = 0.0f;
    // Factor que multiplica al color especular en la ecuación de lambert extendida.
    float specularFactor = 0.0f;

    // N debe estar normalizado para hacer el cálculo de lambert.
    Vec3* normalizedN = vec3_normalize(N);

    // Calcúlo el vector reflejado.
    float dotNL = vec3_dot_product(normalizedN, L);
    Vec3* dotNL2N = vec3_mult_by_scalar(normalizedN, 2 * dotNL);
    Vec3* R = vec3_diff(dotNL2N, L);

    float normalizedDotNL = vec3_normalized_dot_product(normalizedN, L); 
    if(normalizedDotNL > 0)
    {
        diffuseFactor += light->intensity * normalizedDotNL;
    }

    float normalizedDotVR = vec3_normalized_dot_product(V, R);
    if(normalizedDotVR > 0 && material->specularExponent >= 1)
    {
        specularFactor += light->intensity * pow(normalizedDotVR, material->specularExponent);
    }

    Color diffuseColor = cg_color_mult_by_factor(material->diffuseColor, diffuseFactor);
    Color specularColor = cg_color_mult_by_factor(material->specularColor, specularFactor);
    Color result = cg_color_add(diffuseColor, specularColor);

    // Liberar recursos.
    vec3_free(R);
    vec3_free(dotNL2N);
    vec3_free(normalizedN);

    return result;
}

Color trace_ray(Scene* scene, Vec3* O, Vec3* D, float minLambda, float maxLambda, int recursionLimit)
{
    Color result = cg_color_new(0, 0, 0);
    Intersection *intersection = intersect(scene, O, D, minLambda, maxLambda);
    if(intersection->sphere != NULL)
    {
        result = cg_color_mult_by_factor(intersection->sphere->material->diffuseColor, scene->ambienceLight);

        Vec3* lambdaD = vec3_mult_by_scalar(D, intersection->closestLambda);
        Vec3* P = vec3_add(O, lambdaD);
        Vec3* N = vec3_diff(P, intersection->sphere->center);
        Vec3* V = vec3_mult_by_scalar(D, -1.0f);

        vec3_free(lambdaD);

        // Calcula las sombras de las esferas.
        Block *currentLightBlock = scene->lights->head;
        Light *currentLight;
        Vec3 *L;
        Vec3 *oppositeL;
        Intersection *shadow;
        while(currentLightBlock != NULL)
        {
            currentLight = (Light *) currentLightBlock->data;
            L = vec3_diff(currentLight->position, P);
            oppositeL = vec3_diff(P, currentLight->position);
            shadow = intersect(scene, P, oppositeL, EPSILON, 1-EPSILON);
            if(shadow->sphere == NULL)
            {
               Color lambertColor = lambert(P, N, V, L, currentLight, intersection->sphere->material, scene->ambienceLight);
               result = cg_color_add(result, lambertColor); 
            }

            // Liberar recursos.
            vec3_free(L);
            vec3_free(oppositeL);
            intersection_free(shadow);

            currentLightBlock = currentLightBlock->next;
        }

        Color reflected = cg_color_new(0, 0, 0);

        if(recursionLimit > 0 && intersection->sphere->material->reflectionFraction > 0)
        {
            Vec3* normalizedN = vec3_normalize(N);

            // Calcúlo el rayo reflejado.
            float dotNV = vec3_dot_product(normalizedN, V);
            // Representa el vector N multiplicado por (2*<N,V>).
            Vec3* dotNV2N = vec3_mult_by_scalar(normalizedN, 2 * dotNV);
            Vec3* RV = vec3_diff(dotNV2N, V);

            reflected = trace_ray(scene, P, RV, EPSILON, INF, recursionLimit - 1);
            Color a = cg_color_mult_by_factor(result, 1 - intersection->sphere->material->reflectionFraction);
            Color b = cg_color_mult_by_factor(reflected, intersection->sphere->material->reflectionFraction);
            result = cg_color_add(a, b);

            // Liberar recursos.
            vec3_free(RV);
            vec3_free(dotNV2N);
        }

        // Liberar recursos.
        vec3_free(P);
        vec3_free(N);
        vec3_free(V);
    }

    // Liberar recursos.
    intersection_free(intersection);

    return result;
}
