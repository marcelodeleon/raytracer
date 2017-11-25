#include "raytracer.h"

Intersection* intersection_new()
{
    Intersection *intersection = (Intersection *) cg_malloc(sizeof(Intersection));
    intersection->sphere = NULL;
    intersection->closestLambda = INF;

    return intersection;
}

float min(float a, float b)
{
    float min = a;
    if(a > b)
    {
        min = b;
    }

    return min;
}

float solveCuadraticEquation(float a, float b, float c)
{
    float solution1;
    float solution2;
    float solution; // Solución final, lambda más cercano a la cámara.

    // Analizo el determinante para ver si existen raíces reales.
    float delta = pow(b, 2) - 4 * a * c;

    if(delta < 0)
    {
        // No existen raíces reales. Retorno infinito como solución.
        solution = INF;
    }
    else
    {
        // Retorno la solución más chica, este es el lambda de la intersección más cercano a la cámara.
        solution1 = ( -b + sqrt(delta) ) / 2 * a;
        solution2 = ( -b - sqrt(delta) ) / 2 * a;

        solution = min(solution1, solution2);
    }

    return solution;
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

Color follow_ray(Scene* scene, Vec3* O, Vec3* D, float minLambda, float maxLambda, int recursionLimit)
{
    Color result = cg_color_new(0, 0, 0);
    Intersection *intersection = intersect(scene, O, D, minLambda, maxLambda);
    if(intersection->sphere != NULL)
    {
        Vec3* lambdaD = vec3_mult_by_scalar(D, intersection->closestLambda);
        Vec3* P = vec3_add(O, lambdaD);
        Vec3* N = vec3_diff(P, intersection->sphere->center);
        Vec3* V = vec3_mult_by_scalar(D, -1.0f);

        // Add light foreach.
        if(recursionLimit > 0 && intersection->sphere->material->reflectionFraction > 0)
        {
            // Calcúlo el rayo reflejado.
            float dotNV = vec3_dot_product(N, V);
            Vec3* RV = vec3_diff(vec3_mult_by_scalar(N, 2 * dotNV), V);

            result = follow_ray(scene, P, RV, EPSILON, INF, recursionLimit - 1);
        }
    }

    return result;
}

