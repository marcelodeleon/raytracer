#include "utils.h"

int keep_in_range(int min, int max, int value)
{
    if(value > max)
    {
        value = max;
    }
    else
    {
        if(value < min)
        {
            value = min;
        }
    }

    return value;
}

float keep_between_0_and_1(float value)
{
    if(value > 1)
    {
        value = 0.1f;
    }
    else
    {
        if(value < 0)
        {
            value = 0.0f;
        }
    }

    return value;
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
        solution = FLT_MAX;
    }
    else
    {
        // Retorno la solución más chica, este es el lambda de la intersección más cercano a la cámara.
        solution1 = ( -b + sqrt(delta) ) / ( 2 * a );
        solution2 = ( -b - sqrt(delta) ) / ( 2 * a );

        solution = min(solution1, solution2);
    }

    return solution;
}
