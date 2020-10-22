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
 * \brief Permet au personnage de se déplacer sur une des salles adjacentes
 * \param plateau le tableau des salles
 * \param perso le personnage se trouvant dans la salle
 * \param direction 
*/
void deplacer(salle_t** plateau,persos_s* perso,char* direction,int * choix_dir);


/**
 *\brief Permet au personnage de regarder dans n'importe quelle salle
 *\param plateau le tableau des salles
 *\param x l'abscisse de la salle qu'on veut regardé (l'origine étant en haut à gauche)
 *\param y l'ordonnée de la salle qu'on veut regardé (l'origine étant en haut à gauche)
*/
void regarder(salle_t** plateau,int x,int y);

/**
 *\brief Permet au personnage de déplacer sa colonne ou sa ligne d'un cran  
 *\param plateau le tableau des salles
*/
void controler(salle_t** plateau, char* direction, int nbRangee);
#endif