#include "framework/canvas.h"
#include "framework/mm.h"
#include "cg_parser.h"
#include "src/raytracer.h"

enum bool {false, true};
typedef enum bool bool;

int main(int argc, char* argv[])
{
	// Crear una ventana de 500x500 pixels:
	int cw = 500;
	int ch = 500;
	cg_init(cw, ch, "Raytracer - Marcelo de León");

#ifdef WIN32
    freopen( "CON", "w", stdout );
	freopen( "CON", "w", stderr );
#endif

	Scene *scene = cg_parse_conf("Escenas_Raytracer/escena1.txt");
    scene_print(scene);

    int x;
    int y;
    int xPrime;
    int yPrime;
    int zPrime;
    // Origen del rayo.
    Vec3* O = scene->camera;
    // Dirección del rayo.
    Vec3* D;

    for (x = -cw/2; x < cw/2; x++)
    {
        for (y = -ch/2; y < ch/2; y++)
        {
            xPrime = x * (scene->viewport[0] / cw);
            yPrime = y * (scene->viewport[1] / ch);
            zPrime = scene->distance;

            D = vec3_new(xPrime, yPrime, zPrime);
            
            Color c = follow_ray(scene, O, D, 1, INF, 1);           
            cg_putpixel(x, y, c);           
        }
        cg_repaint();
    }

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
    scene_free(scene);

	return 0;
}

