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

Color cg_color_mult_by_factor(Color color, float factor)
{
    // Me aseguro que el valor del factor esté siempre definido en [0, 1].
    factor = keep_between_0_and_1(factor);

    Color result = cg_color_new(color.r * factor, color.g * factor, color.b * factor);
    return result;
}

Color cg_color_add(Color color1, Color color2)
{
    int r = color1.r + color2.r;
    int g = color1.g + color2.g;
    int b = color1.b + color2.b;

    // Los canales r, g y b tienen que estar dentro del intervalo [0, 255].
    r = keep_in_range(MIN_CHANNEL_VALUE, MAX_CHANNEL_VALUE, r);
    g = keep_in_range(MIN_CHANNEL_VALUE, MAX_CHANNEL_VALUE, g);
    b = keep_in_range(MIN_CHANNEL_VALUE, MAX_CHANNEL_VALUE, b);

    Color result = cg_color_new(r, g, b);
    return result;
}
