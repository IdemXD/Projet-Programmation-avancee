#ifndef PERSONNAGES_H
#define PERSONNAGES_H

/**
	*\file personnages.h
	*\author Chloe Mathias
	*\version 1.0
*/


struct character_t {
	int coord_x; /*!< Tableau contenant la coordonnée x du personnage */
	int coord_y; /*!< Tableau contenant la coordonnée y du personnage */
	int state; /*!< Etat du personnage(1 quand le joueur est vivant)*/
}

typedef struct character_t character_s;


/**
	*\brief alloue l'espace et initialise les personnages
	*\return tableau des struct de joueurs
*/

character_s*  create_characters();

#endif