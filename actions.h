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
 * \param direction direction vers laquelle déplacer le personnage
 * \param choix_dir 1 si le joueur peut choisir une direction, 0 sinon
*/
void deplacer(salle_t** plateau,persos_s* perso,char* direction,int * choix_dir);


/**
 * \brief Permet au personnage de regarder dans n'importe quelle salle
 * \param plateau le tableau des salles
 * \param x l'abscisse de la salle qu'on veut regardé (l'origine étant en haut à gauche)
 * \param y l'ordonnée de la salle qu'on veut regardé (l'origine étant en haut à gauche)
*/
void regarder(salle_t** plateau,int x,int y);

/**
 * \brief Permet au personnage de déplacer sa colonne ou sa ligne d'un cran  
 * \param plateau le tableau des salles
 * \param direction direction de déplacement des salles
 * \param nbRangee numéro dde la rangée à déplacer
 * \param p les personnages
*/
void controler(salle_t** plateau, char* direction, int nbRangee,persos_s* p);
#endif