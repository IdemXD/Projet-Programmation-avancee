#ifndef ACTIONS_H
#define ACTIONS_H

/**
	*\file actions.h
	*\author Chloe Mathias
	*\version 1.0
*/

#include "plateau.h"
#include "salle.h"
#include "personnages.h"

void regarder(salle_t** plateau);

void deplacer(salle_t** plateau,perso_t* perso);

void controler(salle_t** plateau);

#endif