#include "../framework/mm.h"
#include "intersection.h"

Intersection* intersection_new()
{
    Intersection *intersection = (Intersection *) cg_malloc(sizeof(Intersection));
    intersection->sphere = NULL;
    intersection->closestLambda = FLT_MAX;

    return intersection;
}

void intersection_free(Intersection* intersection)
{
    cg_free(intersection);
}

float intersectWithSphere(Vec3* O, Vec3* D, Sphere* sphere)
{
    // Calcúlo los coeficientes de la ecuación de segundo grado que resulve la intersección entre el rayo y
    // la esfera.
    float a = vec3_dot_product(D, D);

    // Vector resultante de la diferencia entre O y C (El centro de la esfera).
    Vec3* OC = vec3_diff(O, sphere->center);
    float dotDOC = vec3_dot_product(D, OC);
    float b = 2 * dotDOC;

    float radiusSquare = pow(sphere->radius, 2);
    float c = vec3_dot_product(OC, OC) - radiusSquare;

    float solution;
    // Solamente retornamos la solución más cercana a la cámara (de haber intersección).
    // En caso de que no exista solución, se retorna infinito.
    solution = solveCuadraticEquation(a, b, c);

    // Liberar recursos.
    vec3_free(OC);

    return solution;
}

Intersection* intersect(Scene* scene, Vec3* O, Vec3* D, float minLambda, float maxLambda)
{
    Intersection *intersection = intersection_new();

    Sphere *currentSphere;
    float lambda;
    Block *currentSphereBlock = scene->spheres->head;
    while(currentSphereBlock != NULL)
    {
        currentSphere = (Sphere *) currentSphereBlock->data;
        lambda = intersectWithSphere(O, D, currentSphere);
        if(lambda > minLambda && lambda < maxLambda && lambda < intersection->closestLambda)
        {
            // Tengo una intersección válida, actualizo la estructura.
            intersection->sphere = currentSphere;
            intersection->closestLambda = lambda;
        }

        currentSphereBlock = currentSphereBlock->next;
    }

    return intersection;
}
