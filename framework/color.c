#include "color.h"

Color cg_color_new(byte r, byte g, byte b)
{
	Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	return color;
}

void cg_color_print(Color color)
{
    printf("Color -> { r: %d, g: %d, b: %d }\n", color.r, color.g, color.b);
}

// Devuelve el color resultante de multiplicar todos sus canales por un factor (incluído en [0, 1]).
Color cg_color_mult_by_factor(Color color, float factor)
{
    // Me aseguro que el valor del factor esté siempre definido en [0, 1].
    if(factor > MAX_FACTOR)
    {
        factor = MAX_FACTOR;
    }
    else
    {
        if(factor < MIN_FACTOR)
        {
            factor = MIN_FACTOR;
        }
    }

    Color result = cg_color_new(color.r * factor, color.g * factor, color.b * factor);

    return result;
}
