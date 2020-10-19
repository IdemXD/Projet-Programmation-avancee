/*
    *\file plateau.c
    *\author TRUNKENWALD Marie
*/
#include <stdio.h>
#include "salle.h"

salle_t** creer_plateau()
{
     // Creation d'un plateau à deux dimensions
     salle_t** pl=malloc(sizeof(salle_t*)*5);

     // Ouverture du fichier contenant une representation du plateau
     FILE* plateau = fopen("plateau1","r");

     // Curseur de lecture du fichier
     int char_curseur = 0;

     if (plateau != NULL)
     {
          do
          {
               for(int i=0; i<5; i++)
               {
                    pl[i]=malloc(sizeof(salle_t)*5);
                    for(int j=0; j<5; j++)
                    {
                         char_curseur = fgetc(plateau); // Utilisation de fgetc avance le curseur
                         pl[i][j].type = char_curseur; // Le charactère de la salle correspondate est affecté dans la struct
                         pl[i][j].x = i;
                         pl[i][j].y = j;
                    }
               }
          } while (char_curseur != EOF); // EOF est le character de fin de fichier
          fclose(plateau);
     }
     return pl;
}

void affichage_plateau(SDL_Renderer* renderer, ressources texture_salles, salle_t** pl)
{
    SDL_Texture * image_salle;
    // On parcourt le plateau case par case
    for(int i = 0; i < 5; i++)
    {
        for (int j = 0; i < 5; j++)
        {
            if (pl[i][j].visible == 1)
            {
                // Selon le char definissant le type de la salle, on associe la texture correspondante
                switch (pl[i][j].type)
                {
                    case 'S':
                    // Salle de départ
                        image_salle = textures_salles.s_depart;
                        break;

                    case 'R':
                    // Salle 25
                        image_salle = textures_salles.s_25;
                        break;

                    case 'E':
                    // Salle vide
                        image_salle = textures_salles.s_vide;
                        break;

                    case 'V':
                    // Salle vision
                        image_salle = textures_salles.s_vision;
                        break;

                    case 'D':
                    // Salle mortelle
                        image_salle = textures_salles.s_mortelle;
                        break;

                    case 'X':
                    // Salle vortex
                        image_salle = textures_salles.s_vortex;
                        break;

                    case 'T':
                    // Salle tunnel
                        image_salle = textures_salles.s_tunnel;
                        break;

                    case 'C':
                    // Salle chute
                        image_salle = textures_salles.s_chute;
                        break;

                    case 'F':
                    // Salle froide
                        image_salle = textures_salles.s_froide;
                        break;

                    case 'M':
                    // Salle mobile
                        image_salle = textures_salles.s_mobile;
                        break;

                    case 'O':
                    // Salle controle
                        image_salle = textures_salles.s_controle;
                        break;

                    case 'N':
                    // Salle noire
                        image_salle = textures_salles.s_noire;
                        break;
                }
            }
            else
            {
                // La salle est cachée, on ne sait pas ce qu'il se trouve à cet endroit.
                image_salle = textures_salles.s_cache;
            }
            affichage_salle(renderer, image_salle, pl[i][j])
        }
    }
}

void free_plateau(salle_t** pl)
{
  for(int i=0; i<5; i++)
  {
    free(pl[i]); // Libère l'espace des sous tableaux
  }
  free(pl);
}
