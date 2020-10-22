/*
    *\file plateau.c
    *\author TRUNKENWALD Marie
*/
#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "fonctions_SDL.h"
#include "salle.h"

int is_in(int element, int* tab, int tab_length)
{
    trouve = 0;
    i = 0;
    while (!(trouve) && (i < tab_length))
    {
        if (tab[i] == element)
        {
            trouve = 1; // l'element est dans le tableau
        }
        i++;
    }
    return trouve;
}

salle_t** creer_plateau()
{
     // Creation d'un plateau à deux dimensions
     salle_t** pl = malloc(sizeof(salle_t*)*TAILLE_PL);

     // Ouverture du fichier contenant une representation du plateau
     FILE* plateau = fopen("plateau1","r");

     // Curseur de lecture du fichier
     int char_curseur = 0;

     // Flag permettant de s'assurer qu'on ne prend en compts que des lettres reconnu par le jeu
     int flag_char = 0;

     if (plateau != NULL)
     {
          do
          {
               for(int i = 0; i < TAILLE_PL; i++)
               {
                    pl[i] = malloc(sizeof(salle_t)*TAILLE_PL);
                    for(int j = 0; j < TAILLE_PL; j++)
                    {
                        char_curseur = fgetc(plateau); // Utilisation de fgetc avance le curseur
                        if !(is_in(char_curseur, LETTRES_SALLES, 12)) // La charactère (lol) lu n'est pas celui d'une salle
                            {
                                flag_char = 1;
                            }
                        pl[i][j].type = char_curseur; // Le charactère de la salle correspondate est affecté dans la struct
                        pl[i][j].x = i; // initialisation des coordonées des salles
                        pl[i][j].y = j;
                    }
               }
          } while ((char_curseur != EOF) && !(flag_char)); // EOF est le character de fin de fichier

          if (flag_char) // La boucle s'est arreté car un char non exploitable a été lu
          {
              return -1; // on ne retourne pas un plateau incorrect, -1 erreur par convention
          }
          fclose(plateau);
     }
     return pl;
}

void affichage_plateau_brut(salle_t** pl)
{
    // On parcourt le plateau case par case
    for(int i = 0; i < TAILLE_PL; i++)
    {
        for (int j = 0; i < TAILLE_PL; j++)
        {
            printf("%c", pl[i][j]); // affichage du char de la case
        }
        printf("\n"); // saut à la ligne
    }
}

void affichage_plateau(SDL_Renderer* renderer, ressources texture_salles, salle_t** pl)
{
    SDL_Texture * image_salle;
    // On parcourt le plateau case par case
    for(int i = 0; i < TAILLE_PL; i++)
    {
        for (int j = 0; i < TAILLE_PL; j++)
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
            affichage_salle(renderer, image_salle, pl[i][j]);
        }
    }
}

void free_plateau(salle_t** pl)
{
  for(int i = 0; i < TAILLE_PL; i++)
  {
    free(pl[i]); // Libère l'espace des sous tableaux
  }
  free(pl);
}
