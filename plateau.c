/*
    *\file plateau.c
    *\author TRUNKENWALD Marie
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void init_salles(char salle[5], salle_t** pl, int n)
{
    int i = n/TAILLE_PL;
    int j = n%TAILLE_PL;
    pl[i][j].x = j ; // initialisation des coordonées des salles
    pl[i][j].y = i ;

    pl[i][j].type = salle[0]; // 1er charactère de la salle correspondant est affecté dans la struct
    pl[i][j].visible = salle[1] - '0';  // 2e Caractère suivant définit la visibilité
    pl[i][j].state = salle[2] - '0'; // 3e Caractère suivant définit l'etat
    pl[i][j].pres= salle[3] - '0';
}

char* preparation_chemin()
{
    int no;
    printf( "Choisissez un numero de plateau: " );
    scanf( "%i", &no ); // on récupère le numero du niveau

    char* niv; // Taille: nb de char + '\0' de fin de chaine de charactère
    niv = malloc(sizeof(char)*23);

    // fonction de concatenation du numero du niveau de du chemin
    snprintf(niv, 23,"niveaux/plateau%i.txt", no);

    return niv;
}

char * nom_du_plateau(int plateau){

    char* niv; // Taille: nb de char + '\0' de fin de chaine de charactère
    niv = malloc(sizeof(char)*23);

    // fonction de concatenation du numero du niveau de du chemin
    snprintf(niv, 23,"niveaux/plateau%d.txt",plateau);

    return niv;
}

int chars_valide(char paquet[6])
{
    // Si un des elements le respecte pas cette suite, on renvoie 0
    if ((!is_in(paquet[0], LETTRES_SALLES, 17)) && (paquet[0] != '\n'))
        return 0;

    // Si un des trois, supposés boolean, ne sont pas sous le bon format, envoie 0
    for(int i = 1; i < 4; i++)
        if (!(paquet[i] == '1' || paquet[i] == '0'))
            return 0;

    // Les 2 derniers elements du buffer sont '\n' suivi de '\0'
    if ((paquet[4] != '\n') || (paquet[5] != '\0'))
        return 0;

    return 1; // les elements s'enchainent correctement
}

int verif_emplacements(salle_t** pl)
{
    int count_S_R = 0;

    for(int j = 0; j < 5; j++){
        for (int i = 0; i < 5; i++){

            if(pl[j][i].type == 'R'){
                // La salle 25 existe
                count_S_R += 1;

                if((i == 2) || (j == 2) || (i+j == 2)|| (i+j == 6) || (i+j == 4)){
                    if (!((i == 4) || (j == 4))){
                        perror("Salle 25 n'a pas le bon emplacement");
                        return 1;
                    }
                }
            }

            if(pl[j][i].type == 'S'){
                // La salle Centrale existe
                count_S_R += 1;

                // On souhaite que la salle centrale soit disposée
                // au mileu du plateau soit visible et utilisable
                if(!((i == 2) && (j == 2) && (pl[j][i].visible == 1) && (pl[j][i].state == 1))){
                    perror("Salle Centrale n'a pas le bon format/emplacement");
                    return 1;
                }
            }
        }
    }

    if (count_S_R != 2) {
        perror("Nombre d'elements Salle 25 ou/et Salle Centrale incorrect");
        return 1;
    }

    return 0;
}

salle_t** creer_plateau()
{
    salle_t** tab = malloc(sizeof(salle_t*)*TAILLE_PL) ;
    if (tab == NULL) exit(EXIT_FAILURE);
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
     FILE* plateau = NULL;
     plateau = fopen(niveau,"r");

     // Flag permettant de s'assurer qu'on ne prend en compte que des lettres reconnu par le jeu
     int flag_char = 0 ;

     // "buffer" permettant de stocké les chars representant une salle et ses caracts
     char tampon[6] = "";

     int salle_count = 0; // nb de chars parcouru dans le fichier

     if (plateau == NULL) {
         perror("Erreur ouverture du niveau") ;
         flag_char = 1;
     }
     else {
         while((fgets(tampon, 6, plateau) != NULL) && (!flag_char))
         // Le fichier est lu jusqu'à ce qu'on arrive sur EOF, la fonction fgets reconnait \n et EOF
         // ou jusqu'à ce que l'on rencontre une erreur dans la lecture
         {
             // Un des caractère lu ne respecte pas le format d'un plateau
             // ou on a une ligne en trop dans le fichier
             if(!chars_valide(tampon) || (salle_count >= 25))
             {
                 perror("Mauvais format de caractères et/ou de ligne");
                 flag_char = 1;
             } else {
                 init_salles(tampon, pl, salle_count);
                 salle_count += 1; // On prend en compte qu'on a avancé de char_count elements dans le fichier
             }
         }
         fclose(plateau);
    }

    if(salle_count != 25) // Pas assez de salle dans le plateau
    {
        perror("Pas assez de caractères dans le fichier");
        flag_char = 1;
    }

    // On vérifie l'existance et l'emplacement de la salle 25 et Centrale
    if(verif_emplacements(pl)) flag_char = 1;

    // On exit et free la mémoire si on rencontre une erreur dans le niveau
    // sinon on renvoie le plateau
    //(flag_char) ? exit(0) : return pl;
    if (flag_char) exit (0);
    else return pl;
}

void proposition_sauvegarde(salle_t** pl)
{
    int choix;
	printf( "Voulez vous sauvegarder le plateau actuel ? [1/0]" );
    scanf( "%i", &choix );

	if(choix)
        sauvegarder_plateau(pl);
}

void sauvegarder_plateau(salle_t** pl)
{
    // Création du fichier qui va contenir la sauvegarde car mode w
    FILE* save = NULL ;
    save = fopen("niveaux/plateau7.txt","w") ;

    // "buffer" permettant de stocké les chars representant une salle et ses caracts
    char tampon[6] = "" ;

    if (save == NULL)
        perror ("Probleme creation de sauvegarde");
    else {
        for(int i = 0; i < TAILLE_PL; i++) {
            for(int j = 0; j < TAILLE_PL; j++) {
                snprintf(tampon, 6, "%c%i%i%i\n", pl[i][j].type, pl[i][j].visible, pl[i][j].state, pl[i][j].pres);
                fputs(tampon, save);
            }
        }
    }
    fclose(save);
    printf("Plateau sauvegardé en tant que plateau no 7 !");
}

int existence_sauvegarde(){
    FILE* save = NULL ;
    save = fopen("niveaux/plateau7.txt","r") ;

    if (save == NULL){
        return 0;
    }
    else {
        fclose(save);
        return 1;
    }
}

void free_plateau(salle_t** pl)
{
  for(int i = 0; i < TAILLE_PL; i++)
  {
    free(pl[i]); // Libère l'espace des sous tableaux
  }
  free(pl);
  pl = NULL;
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

int plateau_est_visible(salle_t** pl){
    int est_visible = 1;//On considère que le plateau est plein
    int x = 0, y = 0;
    while (est_visible && x != 5){
        while (est_visible && y != 5){
            if (pl[x][y].visible == 0){
                est_visible = 0;
            }
            y++;
        }
        y = 0;
        x++;
    }
    return est_visible;
}
