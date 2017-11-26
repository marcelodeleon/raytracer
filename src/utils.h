#ifndef UTILS_H
#define UTILS_H

#include <float.h>
#include <math.h>

/* Como calculamos las intersecciones con esferas matemáticamente perfectas, puede ser posible que el punto
 * interceptado esté dentro de la esfera (por cálculos computacionales). Por eso, definimos la siguiente
 * constante EPSILON que nos asegura que el punto de intersección se mueva un poquito hacia afuera de la
 * esfera.
 * */
#define EPSILON 0.001f

// Defino el infiníto como el float más grande que C puede representar.
#define INF FLT_MAX

/*
 * Se asegura que el valor siempre se encuentre dentro del intervalo [min, max] especificado.
 * En caso de que no sea así, el valor se trunca al extremo más cercano.
 */
int keep_in_range(int min, int max, int value);

/*
 * Se asegura que el valor siempre se encuentre en el intervalo [0, 1].
 * En caso de que no sea así, el valor se trunca al extremo más cercano.
 */
float keep_between_0_and_1(float value);

/*
 * Resuelve la función cuadrática que calcula la intersección entre el rayo y las esferas.
 * Es importante notar que la función retorna el valor más chico de las dos soluciones, esto se debe a que
 * el valor más chico representa el punto de intersección más cercano a la cámara.
 */
float solveCuadraticEquation(float a, float b, float c);

float min(float a, float b);

#endif //UTILS_H
