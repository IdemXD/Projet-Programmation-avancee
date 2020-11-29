#include <stdio.h>
#include <stdlib.h>

#include "plateau.h"
#include "salle.h"


void affichage_plateau_lettre(salle_t** pl)
/* Affichage des lettres du plateau telles qu'elle sont dans le niveau */
{
    // On parcourt le plateau case par case
    printf("Affichage des lettes des salles du plateau: \n");
    for(int i = 0; i < TAILLE_PL; i++)
    {
        for (int j = 0; j < TAILLE_PL; j++)
        {
            printf("%c", pl[i][j].type); // affichage du char de la case
        }
        printf("\n"); // saut à la ligne
    }
}

void affichage_plateau_coordonnees(salle_t** pl)
/* Affichage des coordonnées de chaque salles*/
{
    // On parcourt le plateau case par case
    printf("Affichage des coordonées des salles du plateau: [x,y] \n");
    for(int i = 0; i < TAILLE_PL; i++)
    {
        for (int j = 0; j < TAILLE_PL; j++)
        {
            printf("[%d,%d]", pl[i][j].x, pl[i][j].y);
        }
        printf("\n"); // saut à la ligne
    }
}

void affichage_plateau_caracteristique(salle_t** pl)
/* Affichage des caractérisique de visibilité, utilisabilité  et pres de chaque salles*/
{
    // On parcourt le plateau case par case
    printf("Affichage visibilité/utilisabilité/pres des salles du plateau: [v,u,p] \n");
    for(int i = 0; i < TAILLE_PL; i++)
    {
        for (int j = 0; j < TAILLE_PL; j++)
        {
            printf("[%d,%d,%d]", pl[i][j].visible, pl[i][j].state, pl[i][j].pres);
        }
        printf("\n"); // saut à la ligne
    }
}


int main(int argc, char *argv[]){
    /* Fonctions d'exposition detaillées des salles*/
    salle_t** pl = charger_plateau();
    affichage_plateau_lettre(pl);
    printf("\n");

    affichage_plateau_coordonnees(pl);
    printf("\n");

    affichage_plateau_caracteristique(pl);
    printf("\n");

    free_plateau(pl);

    /* Fonctions de vérification d'intégrité des fichiers */
    // A venir
}
