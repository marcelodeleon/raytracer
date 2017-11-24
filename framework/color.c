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
