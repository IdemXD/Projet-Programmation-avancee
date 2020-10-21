/**
	*\file actions.c
	*\author Chloe Mathias
*/

#include <stdbool.h.h>
#include <stdlib.h>

#include "actions.h"
#include "personnages.h"
#include "plateau.h"
#include "salle.h"


void deplacer(salle_t** plateau,persos_s* perso,char,char* direction,bool * choix_dir){
	// Le plateau sera utilisé pour l'appel de la fonction des salles
	if (*choix_dir){
		//Lorsque le joueur choisit une direction

		//Cas où le joueur choisit droite
		if(perso->coord_x+1 < 5 && *direction == 'd'){
			perso->coord_x = perso->coord_x + 1 ;
		}
		//Cas où le joueur choisit gauche
		else if(perso->coord_x-1 >= 0 && *direction == 'g'){
			perso->coord_x = perso->coord_x - 1 ;
		}
		//Cas où le joueur choisit bas
		else if (perso->coord_y+1 < 5 && *direction == 'b'){
			perso->coord_y = perso->coord_y + 1 ;
		}
		//Cas où le joueur choisit haut
		else if (perso->coord_y-1 >= 0 && *direction == 'h'){
			perso->coord_y = perso->coord_y - 1 ;	
		}

		if (*direction != NULL){
		//Lorsque le joueur a choisit une direction , il ne peut plus choisir de direction,on rend visible la salle (s'il faut) et on fait l'action de la salle
			*choix_dir = false;
			*direction = NULL;
			
			visible_et_etat(plateau,perso->coord_x,perso->coord_y);
			action_salle(plateau,perso,plateau[perso->coord_x][perso->coord_y].type);

		}
	}
	else{
		*choix_dir = true;// Pour que l'entrée d'une touche permette de choisir la direction 
	}

}

void regarder(salle_t** plateau,int x,int y){
	modif_visible_et_etat(plateau,x,y);
}

void controler(salle_t** plateau, char* direction, int nbRangee){

}