#ifndef PERSONNAGES_H
#define PERSONNAGES_H

/**
	*\file personnages.h
	*\author Chloe Mathias
	*\version 1.0
*/


struct persos_t {
	int coord_x; /*!< Tableau contenant la coordonnée x du personnage */
	int coord_y; /*!< Tableau contenant la coordonnée y du personnage */
	int state; /*!< Etat du personnage(1 quand le joueur est vivant)*/
};

typedef struct persos_t persos_s;


/**
	*\brief alloue l'espace et initialise les personnages
	*\return tableau des struct de joueurs
*/

persos_s*  creer_persos();

void liberer_persos( persos_s*  persos);

#endif