/*
    *\file plateau.c
    *\author TRUNKENWALD Marie
*/
#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "fonctions_SDL.h"
#include "salle.h"

int is_in(int element,const char* tab, int tab_length)
{
    int trouve = 0;
    int i = 0;
    while (!trouve && (i < tab_length))
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
     FILE* plateau = fopen("plateau1.txt","r");

     // Curseur de lecture du fichier
     int char_curseur = 0;

     // Flag permettant de s'assurer qu'on ne prend en compts que des lettres reconnu par le jeu
     int flag_char = 0;

     // Indices
     int i = 0;
     int j = 0;

     char LETTRES_SALLES[12] = {'R','C','O','S','E','F','M','D','N','T','X','V'};

     if (plateau != NULL)
     {
        
          do
          {
               while ((i < TAILLE_PL) && !(flag_char))
               {
                    pl[i] = malloc(sizeof(salle_t)*TAILLE_PL);
                    j = 0;
                    while((j < TAILLE_PL) && !(flag_char)){
                       // printf("||2 c = %c , i = %d , j = %d,||",char_curseur,i,j);
                        char_curseur = fgetc(plateau); // Utilisation de fgetc avance le curseur
                        

                        if (char_curseur == '\n'){//Lorsqu'on arrive à la fin d'une ligne, on passe au caractère d'après pour accéder à la ligne du dessous
                          
                          char_curseur = fgetc(plateau); 
                        }
                        
                        if (!is_in(char_curseur, LETTRES_SALLES, 12)) // La charactère (lol) lu n'est pas celui d'une salle
                            {
                                flag_char = 1;
                            }
                        else{
                          pl[i][j].type = char_curseur; // Le charactère de la salle correspondate est affecté dans la struct
                        }
                        pl[i][j].x = j; // initialisation des coordonées des salles
                        pl[i][j].y = i;
                        j++;
                    }

                    i++;

               }
               char_curseur = fgetc(plateau); 
          } while ((char_curseur != EOF) && !(flag_char)); // EOF est le character de fin de fichier

          if (flag_char) // La boucle s'est arreté car un char non exploitable a été lu
          {
              return NULL; // on ne retourne pas un plateau incorrect, -1 erreur par convention
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
        for (int j = 0; j < TAILLE_PL; j++)
        {

            printf("%c", pl[i][j].type); // affichage du char de la case
        }
        printf("\n"); // saut à la ligne
    }
}

void affichage_plateau(SDL_Renderer* renderer, ressources texture_salles, salle_t** pl)
{
    // On parcourt le plateau case par case
    for(int i = 0; i < TAILLE_PL; i++)
    {
        for (int j = 0; j < TAILLE_PL; j++)
        {
            affiche_salle(renderer, texture_salles.sprites, pl[i][j]);
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
