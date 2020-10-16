#ifndef ACTIONS_H
#define ACTIONS_H

/**
	*\file actions.h
	*\author Chloe Mathias
	*\version 1.0
*/


#include "personnages.h"
#include "plateau.h"
#include "salle.h"

/**
 * \brief Action se déplacer du joueur
 * \param plateau le tableau des 
 * \param perso le personnage se truvant dans la salle
 * \
*/
void deplacer(salle_t** plateau,persos_s* perso,char* direction, );


/**
 * \brief Action se déplacer du joueur
 * \param plateau le tableau des salles

*/
void regarder(salle_t** plateau,int x, int y);

#endif