#include "raytracer.h"

Color follow_ray(Scene* scene, Vec3* O, Vec3* D, float minLambda, float maxLambda, int recursionLimit)
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
        /* while(currentLightBlock != NULL) */
        /* { */
        /*     currentLight = (Light *) currentLightBlock->data; */
        /*     L = vec3_diff(currentLight->position, P); */
        /*     Intersection *shadow = intersection(scene, P, L, EPSILON, 1); */
        /*     /1* if(shadow->sphere == NULL) *1/ */
        /*     /1* { *1/ */
                
        /*     /1* } *1/ */


        /*     vec3_free(L); */

        /*     currentLightBlock = currentLightBlock->next; */
        /* } */

        if(recursionLimit > 0 && intersection->sphere->material->reflectionFraction > 0)
        {
            // Calcúlo el rayo reflejado.
            float dotNV = vec3_dot_product(N, V);
            // Representa el vector N multiplicado por (2*<N,V>).
            Vec3* dotNV2N = vec3_mult_by_scalar(N, 2 * dotNV);
            Vec3* RV = vec3_diff(dotNV2N, V);

            result = follow_ray(scene, P, RV, EPSILON, INF, recursionLimit - 1);

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

