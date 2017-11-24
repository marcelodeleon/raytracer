#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "../framework/mm.h"

void matrix_initialize(Matrix* m, float initial_value)
{
    int rows = m->r;
    int columns = m->c;
    
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            matrix_set_elem(m, i, j, initial_value);
        }
    }
}

float dot_product(Matrix* m1, Matrix* m2, int row, int column)
{

    int columns = m1->c;
    float dot_product = 0.0f;
    
    int i;
    for (i = 0; i < columns; i++)
    {
        dot_product += matrix_get_elem(m1, row, i) * matrix_get_elem(m2, i, column);
    }
    
    return dot_product;
}

Matrix* matrix_new(int n, int m)
{
    float* innerMatrix = (float *) cg_malloc(sizeof(float)*n*m);
    Matrix* matrix = (Matrix *) cg_malloc(sizeof(Matrix));
    matrix->inner_matrix = innerMatrix;
    matrix->r = n;
    matrix->c = m;
    
    //Inicializo matriz, de otra manera la matríz tendría basura.
    matrix_initialize(matrix, 0.0f);
    
    return matrix;
}

float matrix_get_elem(Matrix* m, int r, int c)
{
    int rows = m->r;
    int columns = m->c;
    
    if( (r < rows && r >= 0) && (c < columns && c >= 0))
    {
        // Calculamos el índice de la posición
        int elem_index = r * columns + c;
        return m->inner_matrix[elem_index];
    }
    return -1;
}

void matrix_set_elem(Matrix* m, int r, int c, float val)
{
    int rows = m->r;
    int columns = m->c;
    
    if( (r < rows && r >= 0) && (c < columns && c >= 0))
    {
        // Calculamos el índice de la posición
        int elem_index = r * columns + c;
        m->inner_matrix[elem_index] = val;
    }
}

void matrix_print(Matrix* m)
{
    int rows = m->r;
    int columns = m->c;
    
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            float elem = matrix_get_elem(m, i, j);
            //Si estoy en la última columna imprimo un newline
            if (j == columns - 1)
            {
                printf("%.2f\n", elem);
            }else
            {
                printf("%.2f ", elem);
            }
        }
    }
}

Matrix* matrix_identity(int n, int m)
{
    Matrix* matrix = matrix_new(n, m);
    int rows = matrix->r;
    int columns = matrix->c;
    
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            // Si estamos en la diagonal, insertamos un 1
            if (i == j)
            {
                matrix_set_elem(matrix, i, j, 1.0f);
            }else
            {
                matrix_set_elem(matrix, i, j, 0.0f);
            }
        }
    }
    
    return matrix;
}

void matrix_mult(Matrix* a, Matrix* b, Matrix* c)
{
    int columns_a = a->c;
    int rows_b = b->r;
    int rows_c = c->r;
    int columns_c = c->c;
    
    //Chequea si las matrices son compatibles para multiplicarse
    if(columns_a == rows_b)
    {
        int i, j;
        for (i = 0; i < columns_c; i++)
        {
            for (j = 0; j < rows_c; j++)
            {
                matrix_set_elem(c, i, j, dot_product(a, b, i, j));
            }
        }
    }else
    {
        printf("El número de columnas de a (%d) y el número de filas de b (%d) no son iguales, no puede realizarse el producto.", columns_a, rows_b);
    }

}

void matrix_free(Matrix* m)
{
    free(m->inner_matrix);
    free(m);
}
