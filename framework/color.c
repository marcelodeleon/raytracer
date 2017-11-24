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
    int r = (int) color.r;
    int g = (int) color.g;
    int b = (int) color.b;
    printf("Color -> r: %02x, g %02x, b: %02x\n", r, g, b);
}
