/**
	*\file salle.c
	*\author Boudhane Medi
	*\version 1.0
*/


#include <stdlib.h>
#include <stdio.h>
#include "salle.h"
#include "actions.h"
#include "constantes.h"
#include "pile.h"


void action_salle(salle_t**  pl,persos_t* joueur,int tour_perso,int* dir){
    int x=joueur->coord_x;
    int y=joueur->coord_y;
    int a,b;
    Pile* pile =initialiser();
    creer_pile(pile);
    //Perte_vie(pl,&pl[y][x],joueur,tour_perso,a,b);
    char type;
        switch (pl[y][x].type) {
            case 'V':
                *dir = 2;
                break;
            case 'M':
                *dir = 3;
                break;
            case 'D':
                Salle_mortelle(joueur, &pl[y][x]);
                break;
            case 'C':
                Salle_chute(joueur, &pl[y][x]);
                break;
            case 'F':
                Salle_froide(joueur, tour_perso);
                break;
            case 'N':
                Salle_noire(pl, joueur);
                break;
            case 'O':
                *dir = 1;
                break;
            case 'X':
                Salle_vortex(joueur);
                break;
            case 'T':
                Salle_tunnel(pl,joueur);
                break;
            case 'P':
                Salle_prison(joueur);
                break;
            case 'Z':
                type=depiler(pile);
                Salle_surprise(pl,joueur,type,tour_perso,a,b,dir);
                break;
            case 'Y':
                *dir=4;
                break;
            case 'U':
               // Salle_virus(joueur);
                break;
            case 'H':
             //   Salle_soin(joueur);
                break;

    }
}



void modif_visible_et_etat(salle_t** plateau,int x, int y){

    //Si la salle n'est pas visible, on la met en visible
    if (plateau[y][x].visible == 0){
        if(plateau)
            if (plateau[y][x].type == 'T'){//Le cas de la salle tunnel
                int i = 0,j;
                int trouve = 0;
                while (i < 5 && !trouve){
                    j = 0;
                    while(j < 5 && !trouve){
                        if (plateau[i][j].type == 'T' && plateau[i][j].visible == 1){

                            //Si les deux salles sont visibles, on les rend utilisable
                            plateau[i][j].state = 1;
                            plateau[y][x].state = 1;

                            trouve = 1;
                        }

                        j++;
                    }
                    i++;
                }
                //Dans le cas où l'autre salle tunnel n'est pas découverte, on ne change rien car elle est inutilisable à l'initialisation
            }
            else{

                plateau[y][x].state = 1;
                plateau[y][x].pres= 1;
            }

        plateau[y][x].visible = 1; //On rend la salle visible après pour que la boucle ne puisse trouver que l'autre salle tunnel, si elle est visible
    }

}


void Salle_mortelle(persos_t* perso,salle_t* salle){                       //fonctionne
    perso->state=0;//Le joueur meurt s'il rentre dans la salle
    salle->state=0;
}



void Salle_chute(persos_t* perso,salle_t* salle){                               //fonctionne
    if (salle->pres==1){
        salle->pres=2;  //L'etat de présence passe à 1 et permet d'enclencher le piège au prochain marqueur de présence
    }else {
        if (salle->pres == 2) {
            perso->state = 0;  //Le joueur meurt
            salle->pres = 0;    // La salle reprend son état original
        }
    }
}


void Salle_vision(salle_t** pl, int x, int y){
    if(x != -1 && y != -1 && pl[y][x].visible==0) {
        regarder(pl, x, y); // appel de la fonction regarder pour simuler l'effet de la salle vision
    }
}



void Salle_controle(salle_t**  pl,persos_t* perso,int tour_perso,char* direction,int nb_personnage){
    int rangee;
    if (*direction== 'h' || *direction == 'b'){
        rangee = perso[tour_perso].coord_x;

    }
    else{
        rangee = perso[tour_perso].coord_y;
    }
    controler(pl,direction,rangee,perso,nb_personnage);
}



void Salle_vortex(persos_t* perso){                             //Fonctionne
    perso->coord_x=2;   // Changement des coordonnées du personnage pour le renvoyer sur la cases de départ
    perso->coord_y=2;
}



void Salle_tunnel(salle_t** pl, persos_t* perso ){                  //Fonctionne
    for (int i = 0 ; i<5 ; i++){
        for (int j =0 ; j<5 ; j++){
            if (pl[i][j].type == 'T' && perso->coord_x != pl[i][j].x && perso->coord_y != pl[i][j].y && pl[perso->coord_y][perso->coord_x].state){
                perso->coord_x=j;
                perso->coord_y=i;
            }
        }
    }

}


void Salle_froide(persos_t* perso,int tour_perso) {
    perso->nb_actions--;

}



void Cherche_salle(salle_t** pl ,persos_t*  persos,int tour_perso ,char salle, int* a , int* b) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {

            if (pl[i][j].type == salle && persos[tour_perso].coord_x == pl[i][j].x &&
                persos[tour_perso].coord_y == pl[i][j].y) {
                *a = i;
                *b = j;
            }
        }
    }
}

void Salle_mobile(salle_t** pl,persos_t* perso ,int tour_perso, int* x, int*y){
    if(*x != -1 && *y != -1 && pl[*y][*x].visible==0) {
       change_type(pl, perso, tour_perso, x, y);
       perso[tour_perso].coord_y=*y;
       perso[tour_perso].coord_x=*x;
    }
}

void change_type(salle_t** pl,persos_t* perso ,int tour_perso, int *x, int *y){
    int a,b;
    Cherche_salle(pl,perso,tour_perso,'M',&a,&b);
    char type_salle=pl[a][b].type;
    char type=pl[*y][*x].type;
    pl[a][b].type=type;
    pl[a][b].visible=0;
    pl[*y][*x].type=type_salle;
    pl[*y][*x].visible=1;
}


void Salle_noire(salle_t** pl, persos_t* perso){
    for (int i = 0 ; i<5 ; i++){
        for (int j =0 ; j<5 ; j++){                                                     // fonctionne
            pl[i][j].visible=0;
            pl[2][2].visible=1;
            pl[i][j].state=0;
            if(j== perso[0].coord_x && i== perso[0].coord_y || j== perso[1].coord_x && i== perso[1].coord_y) {
                pl[i][j].visible = 1;
            }
        }
    }
}



void Salle_prison(persos_t* perso){
    perso->nb_actions=0;
}

void Salle_copie(salle_t** pl,persos_t* persos,int x,int y){
    pl[persos->coord_y][persos->coord_x].type=pl[y][x].type;
}

void Salle_surprise(salle_t **pl,persos_t* persos,char salle_Depile,int tour_perso,int a,int b,int* dir){
    Cherche_salle(pl,persos,tour_perso,'X',&a,&b);
    pl[a][b].type=salle_Depile;
}


//void Salle_virus(persos_t* persos){
    //persos->vie--;
//}

//void Perte_vie(salle_t** pl,salle_t* salle , persos_t* persos,int tour_perso,int a,int b){
   // Cherche_salle(pl,persos,tour_perso,'U',&a,&b);
  //  if(pl[a][b].state==1 && pl[salle->y][salle->x].type!='H' &&pl[salle->y][salle->x].state==0){
   //     Salle_virus(persos);
        
   //     }
//}

//void Salle_soin(persos_t* persos){
    //persos->vie=10;
//}