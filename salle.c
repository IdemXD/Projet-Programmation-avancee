/**
	*\file salle.c
	*\author Boudhane Medi
	*\version 1.0
*/


#include <stdlib.h>
#include <stdio.h>
#include "salle.h"
#include "actions.h"


void action_salle(salle_t**  pl,persos_t* joueur,char* dir ,int x_pix,int y_pix,int* a, int* b){
    int x=joueur->coord_x;
    int y=joueur->coord_y;
    switch (pl[y][x].type){
        case 'V':
            Salle_vision(pl,x,y);
            break;
        case 'M':
            Salle_mobile(pl,&pl[x][y],joueur,x_pix,y_pix,a,b);
            break;
        case 'D':
            Salle_mortelle(joueur,&pl[x][y]);
            break;
        case 'C':
            Salle_chute(joueur,&pl[x][y]);
            break;
        case 'F':
            Salle_froide(joueur,&pl[x][y]);
            break;
        case 'N':
            Salle_noire(pl,joueur);
            break;
        case 'O':
            Salle_controle(pl,dir,x,joueur);
            break;
        case 'X':
            Salle_vortex(joueur);
            break;
        case 'T':
            Salle_tunnel(pl,joueur);
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


void Salle_mortelle(persos_t* player,salle_t* salle){                       //fonctionne
    player->state=0;//Le joueur meurt s'il rentre dans la salle
    salle->state=0;
}



void Salle_chute(persos_t* perso,salle_t* salle){                               //fonctionne
    if (salle->pres==0){
        salle->pres=1;  //L'etat de présence passe à 1 et permet d'enclencher le piège au prochain marqueur de présence
    }else{
        perso->state=0;  //Le joueur meurt
        salle->pres=0;    // La salle reprend son état original
    }
}



void Salle_vision(salle_t** pl, int x, int y){
    regarder(pl,x,y); // appel de la fonction regarder pour simuler l'effet de la salle vision
}



void Salle_controle(salle_t** pl, char* direction, int nbRangee,persos_t* p){
    controler(pl,direction,nbRangee, p);
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



void Salle_froide(persos_t* perso,salle_t* salle) {
    if(perso->nb_actions=2){
        perso->nb_actions=1;            //Effet reste sur le personnage
    }else{
        perso->nb_actions=0;
    }
}


void Salle_mobile(salle_t** pl,salle_t* salle, persos_t* perso ,int x_pix,int y_pix,int* x, int*y){
    int new_x ,new_y;
    pixToSalle(x_pix,y_pix,x,y);
    new_x= salle->x;
    new_y= salle->y;
    salle->x=*x;
    salle->y=*y;
    perso->coord_x=*x;
    perso->coord_y=*y;
    *x=salle->x;
    *y=salle->y;

}



void Salle_noire(salle_t** pl, persos_t* perso){
    for (int i = 0 ; i<5 ; i++){
        for (int j =0 ; j<5 ; j++){                                                     // fonctionne
            pl[i][j].visible=0;
            pl[2][2].visible=1;
            if(j== perso[0].coord_x && i== perso[0].coord_y || j== perso[1].coord_x && i== perso[1].coord_y) {
                pl[i][j].visible = 1;
            }
        }
    }
}



void Salle_prison(persos_t* perso){
    perso->nb_actions=0;
}



