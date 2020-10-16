#ifndef SALLE_H
#define SALLE_H

/**
	*\file salle.h
	*\author Boudhane Medi
	*\version 1.0
*/

#include "plateau.h"

struct salle_s
{
    int x;       /*!< Tableau contenant la coordonnée x de la salle */
    int y;       /*!< Tableau contenant la coordonnée y de la salle */
    int state;   /*!< Etat de la salle(1 si la salle est utilisable )*/
    int visible; /*!< Etat de la salle (1 si la salle est visible)*/
    char type;   /*!< Char représentant la salle*/
};
typedef struct salle_s salle_t;


void init_salles(salle_t**  pl);


void action_salle(salle_t**  pl,persos_s* joueur,char* type);


void salle_visible(salle_t* salle);

/**
	*\brief Fonction qui tue le joueurs sur la case
*/

void Salle_mortelle(salle_t **, persos_s *player);

/**
	*\brief Fonction qui appel à un choix d'action
*/
void Salle_vide(salle_t **, persos_s *player, salle_t *salle);




/**
	*\brief Fonction qui tue un personnage après une activation de la case
*/
void Salle_chute();

/**
	*\brief Fonction qui appel la fonction regarder pour une cases sur le plateau
*/
void Salle_vision(salle_t **, persos_s *perso, salle_t *salle);


/**
	*\brief Fonction qui appel la fonction déplacer pour mouvoir les lignes ou colonnes 
*/
void Salle_controle();

/**
	*\brief Fonction qui place le personnage sur la case de départ
*/
void Salle_vortex(salle_t **pl, persos_s *perso, salle_t *salle);

/**
	*\brief Fonction qui déplace le personnage sur un deuxième case tunnel si elle est découverte
*/
void Salle_tunnel();


/**
	*\brief Fonction qui initialise les états de la salle et qui permet la victoire 
*/
void Salle_25();


/**
	*\brief Fonction qui oblige le joueur à programmer une seule action 
*/
void Salle_froide();

/**
	*\brief Fonction qui permet d'échanger la position du joueur étant sur la salle mobile avec la position d'une autre salle caché 
*/
void Salle_mobile();


/**
	*\brief Fonction qui appel les fonctions de choix 
*/
void Salle_depart();

#endif
