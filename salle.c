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


/**
    *\file salle.c
    *\author Boudhane Medi 
    *\version 1.0
*/

#include <stdlib.h>
#include <stdio.h>

#include "actions.h"
#include "personnages.h"
#include "plateau.h"
#include "salle.h"

void init_salles(salle_t**  pl){
    for (int i = 0 ; i<5 ; i++){
        for (int j =0 ; j<5 ; j++){
            //A remplir par Medi
        }
    }
}

void action_salle(salle_t**  pl,persos_s* joueur,char* type){
    switch (type){
        //Pour l'instant seulement l'exemple pour 2 cas (à continuer)
        case 'V':
            salle_vision(pl, joueur);
            break;
        case 'M':
            Salle_mobile();
            break;
            // ...A finir par Medi
    }
}

void salle_visible(salle_t* salle){
    //le si sera peut-être à modifier avec la salle noire
    if (salle->visible==0){
        salle->visible=1;

        if (salle->type != 'T')//A modifier pour mettre le cas avec les salles tunnels
            salle->state=1;
        
    }
}

void Salle_mortelle(salle_t**  pl, persos_s* player,salle_t* salle){
    player->state = 0;//Le joueur meurt s'il rentre dans la salle
    salle->state=0;
}




//
void Salle_mortelle(salle_t**  pl, persos_s* player,salle_t* salle){
    salle->visible=1;
    player->state = 0;
    salle->state = 1;
    salle->state = 0;
}



void  Salle_vide(salle_t**  pl, persos_s* player,salle_t* salle){
    
}



void Salle_chute(){


}





void Salle_vision(salle_t** pl, persos_s* player){

    regarder(pl,player);
    

}



void Salle_controle(){

}



void Salle_vortex(salle_t**  pl, persos_s* perso){
    perso->coord_x=2;
    perso->coord_y=2;
}


void Salle_tunnel(){
    


}

void Salle_25(){

}

void Salle_froide(){

}

void Salle_mobile(){

}

void Salle_depart(){

}




