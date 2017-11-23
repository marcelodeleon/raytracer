#include "framework/canvas.h"
#include "framework/mm.h"

enum bool {false, true};
typedef enum bool bool;

int main(int argc, char* argv[])
{
	// Crear una ventana de 500x500 pixels:
	int cw = 500;
	int ch = 500;
	cg_init(cw, ch, NULL);
	
#ifdef WIN32
    freopen( "CON", "w", stdout );
	freopen( "CON", "w", stderr );
#endif

	bool b = true;
	b = 1 && 0;
	float r = rand() / (float)RAND_MAX;
	if(!b)
		printf("bool ok!!! %f\n",r);
	// Dibujar un pequeno "+" en el centro de la ventana:
	Color color = cg_color_new(0xff, 0x0, 0x0);
	//int x, y;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 || y == 0)
			{
				cg_putpixel(x, y, color);
			}
		}
	}
	cg_parse_conf("Escenas_Raytracer/escena1.txt");
	// Actualizar la pantalla:
	cg_repaint();

	int done = 0;
	while (!done)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN: 
					if (event.key.keysym.sym != SDLK_ESCAPE)
						break;
				case SDL_QUIT : done = 1;
			}
		}
	}

	// Liberar recursos:
	cg_close();

	// Ejemplo del modulo de Manejo de Memoria (MM):
	int* pint = (int *)cg_malloc(10*sizeof(int));
	printf("pint is a pointer: %p\n", pint);
	cg_free(pint); // olvidarse de liberar este objeto produce un mensaje

	
	return 0;
}
