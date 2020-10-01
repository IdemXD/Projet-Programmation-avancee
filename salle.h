#ifndef SALLE_H
#define SALLE_H

/**
	*\file salle.h
	*\author Boudhane Medi
	*\version 1.0
*/

#include "plateau.h"

struct salle_s
{
    int x;      /*!< Tableau contenant la coordonnée x de la salle */
    int y;      /*!< Tableau contenant la coordonnée y de la salle */
    int state;   /*!< Etat de la salle(1 si la salle est utilisable )*/
    int visible;    /*!< Etat de la salle (1 si la salle est visible)*/
    char type;      /*!< Char représentant la salle*/
};
typedef struct salle_s salle_t;




salle_t Salle_mortelle(int** pl, character_s* player){
    
    
    
}



salle_t Salle_vide(tab_t* pl, character_s* player){
    
    
}



salle_t Salle_chute(){


}





salle_t Salle_vision(){

}



salle_t Salle_contrôle(){

}



salle_t Salle_vortex(){

}

salle_t Salle_tunnel(){

}

salle_t Salle_25(){

}

salle_t Salle_froide(){

}

salle_t Salle_mobile(){

}

salle_t Salle_départ(){

}

#endif


