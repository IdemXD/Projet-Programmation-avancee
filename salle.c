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



//
void Salle_mortelle(salle_t**  pl, persos_s* player,salle_t* salle){
    salle->state=1;
    salle->visible=0;
    player->state = 1;
    salle->visible=1;
    salle->state=0;
}



void  Salle_vide(salle_t**  pl, persos_s* player,salle_t* salle){
     salle->state=1;
     salle->visible=1;
    
}



void Salle_chute(){


}





void Salle_vision(salle_t** pl, persos_s* player,salle_t* salle){
    salle->state=1;
    salle->visible=1;
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




