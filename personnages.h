#ifndef PERSONNAGES_H
#define PERSONNAGES_H

/**
	*\file personnages.h
	*\author Chloe Mathias
	*\version 1.0
*/
/**
 * \brief Représentation d'un personnage
*/

struct persos_s {
	int coord_x; /*!< Tableau contenant la coordonnée x du personnage */
	int coord_y; /*!< Tableau contenant la coordonnée y du personnage */
	int state; /*!< Etat du personnage(1 quand le joueur est vivant)*/
	int nb_actions;/*!< Nombre d'actions que le personnage peut faire*/
	int* actions; /*!< Actions du personnage*/
};

typedef struct persos_s persos_t;


/**
	*\brief Alloue l'espace et initialise les personnages
	*\return tableau des struct de joueurs
*/

persos_t*  creer_persos();

/**
 * \brief Libère l'espace en mémoire utilisé pour les personnages
*/
void liberer_persos( persos_t*  persos);

#endif