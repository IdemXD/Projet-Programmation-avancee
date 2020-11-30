/*
    *\file plateau.c
    *\author TRUNKENWALD Marie
*/
#include <stdio.h>
#include <stdlib.h>

#include "plateau.h"


void init_salles(salle_t** pl, int n, char curseur){

    int i = n/TAILLE_PL;
    int j = n%TAILLE_PL;
    pl[i][j].visible = 0;
    pl[i][j].state = 0;
    pl[i][j].type = curseur; // Le charactère de la salle correspondate est affecté dans la struct
    pl[i][j].x = j ; // initialisation des coordonées des salles
    pl[i][j].y = i ;
    if(pl[i][j].type=='C' || pl[i][j].type=='P'){
        pl[i][j].pres=0;
    }
    if (i = j = 2){
        pl[2][2].visible = 1;
        pl[2][2].state = 1;
    }
}

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

salle_t** charger_plateau(char* niveau)
{
     // Creation et allocation d'un plateau à deux dimensions
     salle_t** pl = creer_plateau() ;

     // Ouverture du fichier contenant une representation du plateau
     FILE* plateau = fopen(niveau,"r") ;

     int char_curseur = 0 ; // Curseur de lecture du fichier

     // Flag permettant de s'assurer qu'on ne prend en compts que des lettres reconnu par le jeu
     int flag_char = 0 ;

     int i = 0 ;

     if (plateau == NULL) perror("Erreur lors de l'ouverture du plateau") ;
     else {
         do
         {
                // Vérification nb char fichier > 25 pas assuré, en cours de travail
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

        } while ((char_curseur != EOF) && !(flag_char) && (i < 25)); // EOF est le character de fin de fichier
         fclose(plateau);

         if ((flag_char) || (i != TAILLE_PL*TAILLE_PL)) return pl;
         else return pl;
     }
}

void preparation_niveau(char niv[])
{
    printf( "Tapez le nom -exact- d'un fichier niveau parmi: \nplateau1.txt\nplateau2.txt\nplateau3.txt\n\nVotre choix: " );
    scanf( "%s", niv );
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
