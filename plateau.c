/*
    *\file plateau.c
    *\author TRUNKENWALD Marie
*/
#include <stdio.h>
#include <stdlib.h>

#include "plateau.h"

void init_salles(FILE* plateau, salle_t** pl, int n, char* p_curseur)
{

    int i = n/TAILLE_PL;
    int j = n%TAILLE_PL;
    pl[i][j].x = j ; // initialisation des coordonées des salles
    pl[i][j].y = i ;
    pl[i][j].type = *p_curseur; // 1er charactère de la salle correspondant est affecté dans la struct

    *p_curseur = fgetc(plateau); // 2e Caractère suivant définie la visibilité
    pl[i][j].visible = atoi(p_curseur);

    *p_curseur = fgetc(plateau); // 3e Caractère suivant définie l'etat
    pl[i][j].state = atoi(p_curseur);

    *p_curseur = fgetc(plateau); // 4e Caractère suivant définie la presence
    pl[i][j].pres= atoi(p_curseur);
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

char* preparation_niveau()
{
    int niv;
    printf( "Choisissez un plateau entre 1, 2 et 3: " );
    scanf( "%d", &niv );

    if (niv == 1) return "plateau1.txt" ;
    else if (niv == 2) return "plateau2.txt";
    else if (niv == 3) return "plateau3.txt";
    else {
        printf("Votre choix n'est pas parmi 1, 2, 3. Chargement plateau1 par défaut.");
        return "plateau1.txt";
    }
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

     char char_curseur; // Curseur de lecture du fichier

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

                    init_salles(plateau, pl, i, &char_curseur);

                    i++; }

        } while ((char_curseur != EOF) && !(flag_char) && (i < 25)); // EOF est le character de fin de fichier
         fclose(plateau);

         if ((flag_char) || (i != TAILLE_PL*TAILLE_PL)) return pl;
         else return pl;
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

void affichage_plateau_lettre(salle_t** pl)
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
