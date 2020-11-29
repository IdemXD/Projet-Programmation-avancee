/*
    *\file plateau.c
    *\author TRUNKENWALD Marie
*/
#include <stdio.h>
#include <stdlib.h>

#include "plateau.h"

int is_in(char element,const char *tab, int tab_length)
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
    salle_t** tab = malloc(sizeof(salle_t*)*TAILLE_PL) ;
    for(int i = 0; i < 5; i++)
    {
        tab[i] = malloc(sizeof(salle_t)*TAILLE_PL);
    }
    return tab;
}

salle_t** charger_plateau()
{
     // Creation et allocation d'un plateau à deux dimensions
     salle_t** pl = creer_plateau() ;

     // Ouverture du fichier contenant une representation du plateau
     FILE* plateau = fopen("plateau1.txt","r") ;

     int char_curseur = 0 ; // Curseur de lecture du fichier

     // Flag permettant de s'assurer qu'on ne prend en compts que des lettres reconnu par le jeu
     int flag_char = 0 ;

     int i = 0 ;

     if (plateau == NULL) perror("Erreur lors de l'ouverture du plateau") ;
     else {
         do
         {

             // #################### -- Travaux sur verif nb char fichier > 25 en cours -- ##########################
             //printf("i = %d, char_lu = %c, flag_char =%d \n", i, char_curseur, flag_char);
             //if (!(i/5 >= TAILLE_PL)) {
             //if (i < TAILLE_PL*TAILLE_PL) {

                char_curseur = fgetc(plateau) ; // Utilisation de fgetc avance le curseur

                if ((!is_in(char_curseur, LETTRES_SALLES, 12)) && (char_curseur != '\n'))
                {
                    flag_char = 1; // char lu pas compatible, ni saut de ligne
                } else {

                    if (char_curseur == '\n') {
                        char_curseur = fgetc(plateau) ; // saut de ligne, on prend le char suivant
                    }

                    init_salles(pl, i, char_curseur);

                    i++; }
            /**} else { // Trop de chars dans tableau
                printf("i/5 = %d \n", i/5);
                printf("--- Entrée dans le else flag_char du do \n");
                printf("char_curseur = %c \n", char_curseur);
                printf("EOF = %c \n", EOF);
                flag_char = 1;
            }*/
        } while ((char_curseur != EOF) && !(flag_char) && (i < 25)); // EOF est le character de fin de fichier
         fclose(plateau);

         //printf("Valeur de i avant Flag zone i= %d \n",i);
         if ((flag_char) || (i != TAILLE_PL*TAILLE_PL)) {
             /*printf("Flag_char = %d, Taille_carre = %d, i = %d \n", flag_char, TAILLE_PL*TAILLE_PL, i);
             perror("Erreur lors du remplissage du plateau \n") ;
             printf("Flag zone \n");*/
             return pl;
         }  else {
             //printf("Safe zone \n");
             return pl;
         }
    }
    //return pl;
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
