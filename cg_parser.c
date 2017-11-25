#include "cg_parser.h"
#include "src/scene.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Scene* cg_parse_conf(char* scene_file){
    char str [512];
    FILE * pFile;

    pFile = fopen (scene_file,"r+");
    char* token;
    fgets(str,512,pFile);
    Scene *scene = scene_new();
    while(!feof(pFile))
    {
        token = strtok(str," \n\t");
        if(token){
            if(strcmp(token,"pos") == 0)
            {
                token = strtok(NULL," \n\t");
                float cam_pos_x = atof(token);
                token = strtok(NULL," \n\t");
                float cam_pos_y = atof(token);
                token = strtok(NULL," \n\t");
                float cam_pos_z = atof(token);

                // Almacenar posición de la cámara.
                Vec3 *camera = vec3_new(cam_pos_x, cam_pos_y, cam_pos_z);
                scene->camera = camera;
            }
            else
            {
                if(strcmp(token,"dist") == 0)
                {
                    token = strtok(NULL," \n\t");
                    float d = atof(token);

                    // Almacenar distancia al plano de proyección.
                    scene->distance = d;
                }
                else
                {
                    if(strcmp(token,"viewport") == 0)
                    {
                        token = strtok(NULL," \n\t");
                        float vw = atof(token);
                        token = strtok(NULL," \n\t");
                        float vh = atof(token);

                        // Almacenar viewport.
                        scene->viewport[0] = vw;
                        scene->viewport[1] = vh;
                    }
                    else
                    {
                        if(strcmp(token,"ambient") == 0)
                        {
                            token = strtok(NULL," \n\t");
                            float ambient = atof(token);
                            // Almacenar intensidad del ambiente.
                            scene->ambienceLight = ambient;
                        }
                        else
                        {
                           if(strcmp(token,"view") == 0)
                            {
                                token = strtok(NULL," \n\t");
                                float cam_view_x = atof(token);
                                token = strtok(NULL," \n\t");
                                float cam_view_y = atof(token);
                                token = strtok(NULL," \n\t");
                                float cam_view_z = atof(token);
                                /**********************************************************************/
                                /*Insertar código para almacenar vector VIEW de la cámara (OPCIONAL)  */
                                /**********************************************************************/
                                printf("VIEW: [%f %f %f]\n",cam_view_x,cam_view_y,cam_view_z);
                            }
                            else
                            {
                                if(strcmp(token,"up") == 0)
                                {
                                    token = strtok(NULL," \n\t");
                                    float cam_up_x = atof(token);
                                    token = strtok(NULL," \n\t");
                                    float cam_up_y = atof(token);
                                    token = strtok(NULL," \n\t");
                                    float cam_up_z = atof(token);
                                    /**********************************************************************/
                                    /*Insertar código para almacenar vector UP de la cámara (OPCIONAL)    */
                                    /**********************************************************************/
                                    printf("UP: [%f %f %f]\n",cam_up_x,cam_up_y,cam_up_z);
                                }
                                else
                                {
                                    if(strcmp(token,"lightP") == 0)
                                    {
                                        token = strtok(NULL," \n\t");
                                        float l_int = atof(token);
                                        token = strtok(NULL," \n\t");
                                        float l_pos_x = atof(token);
                                        token = strtok(NULL," \n\t");
                                        float l_pos_y = atof(token);
                                        token = strtok(NULL," \n\t");
                                        float l_pos_z = atof(token);

                                        // Almacenar luz puntual.
                                        Light* light = light_new(l_pos_x, l_pos_y, l_pos_z, l_int);
                                        list_add(scene->lights, light);
                                    }
                                    else
                                    {
                                        if(strcmp(token,"lightD") == 0)
                                        {
                                            token = strtok(NULL," \n\t");
                                            float l_int = atof(token);
                                            token = strtok(NULL," \n\t");
                                            float l_dir_x = atof(token);
                                            token = strtok(NULL," \n\t");
                                            float l_dir_y = atof(token);
                                            token = strtok(NULL," \n\t");
                                            float l_dir_z = atof(token);
                                            /******************************************************/
                                            /*Insertar código para almacenar luz Direccional      */
                                            /******************************************************/
                                            printf("LIGHT_D: %f [%f %f %f]\n",l_int,l_dir_x,l_dir_y,l_dir_z);
                                        }
                                        else
                                        {
                                            if(strcmp(token,"sphere") == 0)
                                            {
                                                // Almacenar Esfera.
                                                token = strtok(NULL," \n\t");
                                                float center_x = atof(token);
                                                token = strtok(NULL," \n\t");
                                                float center_y = atof(token);
                                                token = strtok(NULL," \n\t");
                                                float center_z = atof(token);
                                                Vec3* center = vec3_new(center_x, center_y, center_z);

                                                token = strtok(NULL," \n\t");
                                                float radius = atof(token);

                                                token = strtok(NULL," \n\t");
                                                unsigned char col_dif_r = (unsigned char)(255*atof(token));
                                                token = strtok(NULL," \n\t");
                                                unsigned char col_dif_g = (unsigned char)(255*atof(token));
                                                token = strtok(NULL," \n\t");
                                                unsigned char col_dif_b = (unsigned char)(255*atof(token));
                                                Color diffuseColor = cg_color_new(col_dif_r, col_dif_g, col_dif_b);

                                                token = strtok(NULL," \n\t");
                                                unsigned char col_spec_r = (unsigned char)(255*atof(token));
                                                token = strtok(NULL," \n\t");
                                                unsigned char col_spec_g = (unsigned char)(255*atof(token));
                                                token = strtok(NULL," \n\t");
                                                unsigned char col_spec_b = (unsigned char)(255*atof(token));
                                                Color specularColor = cg_color_new(col_spec_r, col_spec_g, col_spec_b);

                                                token = strtok(NULL," \n\t");
                                                float coef_spec = atof(token);

                                                token = strtok(NULL," \n\t");
                                                float coef_refl = atof(token);

                                                Material* material = material_new(specularColor, diffuseColor, coef_spec, coef_refl);
                                                Sphere *sphere = sphere_new(material, center, radius);
                                                list_add(scene->spheres, sphere);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        fgets(str,512,pFile);
    }
    fclose (pFile);

    return scene;
}
