#ifndef COLOR_H
#define COLOR_H

#ifndef APPLEMAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif //APPLEMAC

#include "../src/utils.h"

#define MAX_CHANNEL_VALUE 255
#define MIN_CHANNEL_VALUE 0

typedef unsigned char byte;

typedef struct
{
	byte r, g, b;
} Color;

/** 
 * Crear un color con los valores r, g, b. 
 * r,g,b deben pertenecer al rango 0-255.
 **/
Color cg_color_new(byte r, byte g, byte b);

/*
 * Devuelve el color resultante de multiplicar todos sus canales por un factor (incluído en [0, 1]).
 */
Color cg_color_mult_by_factor(Color color, float factor);

/*
 * Suma dos colores, sumando cada uno de sus canales (r, g y b).
 */
Color cg_color_add(Color color1, Color color2);

void cg_color_print(Color color);

#endif //COLOR_H

