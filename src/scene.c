#include <stdio.h>
#include <stdlib.h>
#include "../framework/mm.h"
#include "scene.h"

Scene* scene_new()
{
    Scene *scene = (Scene *) cg_malloc(sizeof(Scene));
    scene->lights = list_new(sizeof(Light));
    scene->spheres = list_new(sizeof(Sphere));

    return scene;
} 

void scene_free(Scene* scene)
{
    list_free(scene->lights);
    list_free(scene->spheres);
    vec3_free(scene->camera);
    cg_free(scene);
}

void scene_print(Scene* scene)
{
    printf("%s\n", "Scene########################################################################");
    printf("%s\n", "Lights: ");
    list_print(scene->lights);
    Block* currentLightBlock = (Block *) scene->lights->head;
    while(currentLightBlock != NULL)
    {
        Light* light = (Light *) currentLightBlock->data;
        light_print(light);

        currentLightBlock = currentLightBlock->next;
    }

    printf("%s\n", "Spheres: ");
    list_print(scene->spheres);
    Block* currentSphereBlock = (Block *) scene->spheres->head;
    while(currentSphereBlock != NULL)
    {
        Sphere *sphere= (Sphere *) currentSphereBlock->data;
        sphere_print(sphere);

        currentSphereBlock = currentSphereBlock->next;
    }

    printf("\n\n%s\n", "Summary: ");
    printf("%s", "Camara: -> ");
    vec3_print(scene->camera);
    printf("Viewport -> [ w: %f, h: %f ]\n", scene->vw, scene->vh);
    printf("Distancia al plano de proyeccion -> %f\n", scene->distance);
    printf("Luces puntuales -> %d\n", list_size(scene->lights));
    printf("Esferas -> %d\n", list_size(scene->spheres));
}
