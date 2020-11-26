/*
    *\file plateau.c
    *\author TRUNKENWALD Marie
*/
#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "plateau.h"


int is_in(int element,const char *tab, int tab_length)
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
     salle_t** pl = malloc(sizeof(salle_t*)*TAILLE_PL) ;
     for(int j = 0; j < 5; j++)
     {
         pl[j] = malloc(sizeof(salle_t)*TAILLE_PL);
     }

     // Ouverture du fichier contenant une representation du plateau
     FILE* plateau = fopen("plateau1.txt","r") ;

     // Curseur de lecture du fichier
     int char_curseur = 0 ;

     // Flag permettant de s'assurer qu'on ne prend en compts que des lettres reconnu par le jeu
     int flag_char = 0 ;

     // Indices
     int i = 0 ;

     if (plateau == NULL) perror("Erreur lors de l'ouverture du plateau") ;
     else {
         do
         {
             //if (!(i/5 >= TAILLE_PL)) {
             if (i < TAILLE_PL*TAILLE_PL) {

                char_curseur = fgetc(plateau) ; // Utilisation de fgetc avance le curseur

                // Attention: Le plateau ne vérifie pas que le le char est compatible avec le jeu
                // Issue prob fixed in the next commit
                if (!is_in(char_curseur, LETTRES_SALLES, 12)) { /**flag_char = 1*/; } else {

                pl[i/TAILLE_PL][i%TAILLE_PL].type = char_curseur; // Le charactère de la salle correspondate est affecté dans la struct
                pl[i/TAILLE_PL][i%TAILLE_PL].x = i%TAILLE_PL ; // initialisation des coordonées des salles
                pl[i/TAILLE_PL][i%TAILLE_PL].y = i/TAILLE_PL ;

                i++; }
            } else { // Trop de chars dans tableau
                flag_char = 1;
            }
         } while ((char_curseur != EOF) && !(flag_char)); // EOF est le character de fin de fichier
         fclose(plateau);

         if ((flag_char) || (i != TAILLE_PL*TAILLE_PL)) // La boucle s'est arreté car un char non exploitable a été lu
         {
             return pl; // on ne retourne pas un plateau incorrect, -1 erreur par convention
         }
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
            affiche_salle(renderer, texture_salles.sprites_salles, pl[i][j]);
        }
    }
}

void sauvegarder_plateau(salle_t** pl)
{
    // Création du fichier qui va contenir la sauvegarde
    FILE* save = fopen("save.txt","w") ;

    // On parcourt le plateau case par case
    for(int i = 0; i < TAILLE_PL; i++)
    {
        for (int j = 0; j < TAILLE_PL; j++)
        {
            fputc(pl[i][j].type, save) ; // lettre
            fputc(pl[i][j].state, save) ; // utilisabilité
            fputc(pl[i][j].visible, save) ; // visibilité
        }
        fputc('\n', save) ; // saut à la ligne
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
