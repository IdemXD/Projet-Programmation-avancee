/**
	*\file actions.c
	*\author Chloe Mathias
	*\version 1.0
*/

#include "actions.h"
#include "plateau.h"
#include "salle.h"
#include "personnages.h"

void deplacer(salle_t** plateau,persos_s* perso){

	//Cas où le joueur choisit droite
	if(perso->coord_x+1<5){
		perso->coord_x = perso->coord_x + 1 ;
		plateau[perso->coord_x+1][perso->coord_y]->visible = 1;

		//Activer la salle
	}

}

void regarder(salle_t** plateau,persos_s* perso){
	//Cas où le joueur veut regarder à droite

	if(perso->coord_x+1<5){
		plateau[perso->coord_x+1][perso->coord_y]->visible = 1;
	}

}