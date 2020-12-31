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

#include "constantes.h"

struct persos_s {
	int coord_x; /*!< Tableau contenant la coordonnée x du personnage */
	int coord_y; /*!< Tableau contenant la coordonnée y du personnage */
	int state; /*!< Etat du personnage(1 quand le joueur est vivant)*/
	int nb_actions;/*!< Nombre d'actions que le personnage peut faire*/
	int vie;
	int* actions; /*!< Actions du personnage*/
};

typedef struct persos_s persos_t;


/**
	*\brief Alloue l'espace et initialise les personnages
	*\return tableau des struct de joueurs
*/

persos_t*  creer_persos(int nbJoueurs);

int joueurToPersos (int nbJoueurs);

/**
 * \brief Libère l'espace en mémoire utilisé pour les personnages
*/
void liberer_persos( persos_t*  persos,int nbPersos);

/**
 * \brief Affiche la position du joueur dans un tableau reprenant le plateau
*/
void affichage_joueur(persos_t* p);

#endif
