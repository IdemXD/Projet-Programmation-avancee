/**
	*\file salle.c
	*\author Boudhane Medi 
	*\version 1.0
*/

#include "salle.h"
#include "personnages.h"        
#include "plateau.h"        
#include "actions.h"        
#include <stdlib.h>     
#include <stdio.h>

void init_salles(salle_t**  pl){
    for (int i = 0 ; i<5 ; i++){
        for (int j =0 ; j<5 ; j++){
            pl[i][j].visible = 0;
            pl[i][j].state = 0;
            
        }
    }
    pl[2][2].visible = 1;
    pl[2][2].state = 1;

}

void action_salle(salle_t**  pl,persos_s* joueur,char* type,int x,int y,salle_t* salle){
    switch (*type){
        case 'V':
            salle_vision(pl,x,y);
            break;
        case 'M':
            Salle_mobile(pl,salle,joueur);
            break;
        case 'D':
            Salle_mortelle(joueur,pl);
            break;
        case 'C':
            Salle_chute(pl,joueur,salle);
            break;
        case 'F':
            Salle_froide();
            break;
        case 'N':
            Salle_noire();
            break;
        case 'O':
            Salle_controle();
            break;
        case 'X':
            Salle_vortex(pl,joueur);
            break;
        case 'T':
            Salle_tunnel();
            break;
        case 'R':
            Salle_25();
            break;
    }
}

void modif_visible_et_etat(salle_t** plateau,int x, int y){

    //Si la salle n'est pas visible, on la met en visible
    if (plateau[x][y].visible == 0){

        if (plateau[x][y].type == 'T'){//Le cas de la salle tunnel
            int i = 0;
            int trouve = 0;
            while (i < 5 && !trouve){
                j = 0;
                while(j < 5 && !trouve){
                    if (plateau[i][j].type == 'T' && plateau[i][j].visible == 1){

                        //Si les deux salles sont visibles, on les rend utilisable
                        plateau[i][j].state = 1;
                        plateau[x][y].state = 1;

                        trouve = 1;
                    }
                    j++;
                }
                i++;
            }
            //Dans le cas où l'autre salle tunnel n'est pas découverte, on ne change rien car elle est inutilisable à l'initialisation
        }
        else{

            plateau[x][y].state = 1;
            
        }

        plateau[x][y].visible = 1; //On rend la salle visible après pour que la boucle ne puisse trouver que l'autre salle tunnel, si elle est visible
    }
               
}


void Salle_mortelle(persos_s* player,salle_t* salle){
    player->state = 0;//Le joueur meurt s'il rentre dans la salle
    salle->state=0;
}



void Salle_chute(salle_t** pl,persos_s* perso,salle_t* salle){
    int temp;
        while((perso->coord_x && perso->coord_y)==(salle->x &&salle->y)){
            temp=0;                                                     // Ne pas prendre en compte cette fonction boucle infinie
        }
    temp++;
        if (temp==1){
            perso->state=0;                     
        }

}





void Salle_vision(salle_t** pl, int x, int y){
    regarder(pl,x,y); // appel de la fonction regarder pour simuler l'effet de la salle vision
}



void Salle_controle(){
    printf("");
}



void Salle_vortex(salle_t**  pl, persos_s* perso){
    perso->coord_x=2;   // Changement des coordonnées du personnage pour le renvoyer sur la cases de départ
    perso->coord_y=2;   
}


void Salle_tunnel(){
     printf("");
}

void Salle_25(){
    printf("");
}

void Salle_froide(){
     printf("");
}

void Salle_mobile(salle_t** pl,salle_t* salle, persos_s* perso ){
    int new_x,new_y;
    int coord_i,coord_j;
    if(pl[salle->new_x][salle->new_y].visible = 1 ){
        if (salle->type= 'M'){                         
            coord_i= salle->x;
            coord_j= salle->y;                 // coordonnée tampon de la salle mobile
            salle->x=new_x;                
            salle->y=new_y;                    // affectation des coordonnées de la salle à échanger
            perso->coord_x=new_x;             // place le personnage sur la salle échangée
            perso->coord_y=new_y;                   
            salle->new_x=coord_i;            //affectation des coordonnées initiales de la salle mobile  
            salle->new_y=coord_j;
        }      
    }            
}

