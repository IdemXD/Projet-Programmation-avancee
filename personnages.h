/**
	*\file characters.h
	*\author Chloe Mathias
	*\version 1.0
*/

struct character_t {
	int coord_x; /*!< Tableau contenant la coordonnée x du personnage */
	int coord_y; /*!< Tableau contenant la coordonnée y du personnage */
	int state; /*!< Etat du personnage(4 quand le joueur est vivant)*/
}

typedef struct character_t character_s;



