#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

typedef struct
{
    int r; // Número de filas
    int c; // Número de colúmnas
    float* inner_matrix; //Representación lineal de la matriz
} Matrix;

Matrix* matrix_new(int n, int m);

void matrix_print(Matrix* m);

Matrix* matrix_identity(int n, int m);

float matrix_get_elem(Matrix* m, int r, int c);

void matrix_set_elem(Matrix* m, int r, int c, float val);

void matrix_mult(Matrix* a, Matrix* b, Matrix* c);

void matrix_free(Matrix* m);

#endif //MATRIX_H
