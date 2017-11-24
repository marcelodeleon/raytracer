#include <stdio.h>
#include <stdlib.h>
#include "../framework/mm.h"
#include "scene.h"

Scene* scene_new(Vec3* camera, float viewportWidth, float viewportHeight, float distance)
{
    Scene *scene = (Scene *) cg_malloc(sizeof(Scene));
    scene->lights = list_new(sizeof(Light));
    scene->spheres = list_new(sizeof(Sphere));
    scene->camera = camera;
    scene->viewport[0] = viewportWidth;
    scene->viewport[1] = viewportHeight;
    scene->distance = distance;

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
    printf("%s\n", "Scene");
    vec3_print(scene->camera);
    printf("Viewport -> w: %f, h: %f\n", scene->viewport[0], scene->viewport[1]);
    printf("Distancia al plano de proyeccion -> w: %f, h: %f\n", scene->viewport[0], scene->viewport[1]);
    printf("%s\n", "Lights: ");
    list_print(scene->lights);
    Block* currentLightBlock = (Block *) scene->lights->head;
    while(currentLightBlock != NULL)
    {
        Light* light = (Light *) currentLightBlock->data;
        light_print(light);

        currentLightBlock = currentLightBlock->next;
    }

    printf("%s\n", "Scene: ");
    list_print(scene->spheres);
    Block* currentSphereBlock = (Block *) scene->spheres->head;
    while(currentSphereBlock != NULL)
    {
        Sphere *sphere= (Sphere *) currentSphereBlock->data;
        sphere_print(sphere);

        currentSphereBlock = currentSphereBlock->next;
    }
    list_print(scene->spheres);
}
