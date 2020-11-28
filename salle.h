#ifndef SALLE_H
#define SALLE_H

/**
	*\file salle.h
	*\author Boudhane Medi
	*\version 1.0
*/

#include "personnages.h"

struct salle_s
{
    int x;       /*!< Tableau contenant la coordonnée x de la salle */
    int y;       /*!< Tableau contenant la coordonnée y de la salle */
	int new_x;
	int new_y;
	int pres;    /*!< Présence de la salle(1 si la salle est utilisable )*/
    int state;   /*!< Etat de la salle(1 si la salle est utilisable )*/
    int visible; /*!< Etat de la salle (1 si la salle est visible)*/
    char type;   /*!< Char représentant la salle*/
};
typedef struct salle_s salle_t;


void action_salle(salle_t**  pl,persos_t* joueur,char* type,char* dir , char nbr,int x,int y,salle_t* salle);

/**
	*\brief Initialise les caractéristique des salles
    *\param pl plateau considéré 
	*\param n indice du parcours du fichier niveau
    *\param curseur permet d'affecter la lettre correspondante à la salle
*/
void init_salles(salle_t** pl, int n, char curseur);

/**
	*\brief Actualise la visibilité de la salle aux coordonnées (x,y) et son état
	*\param plateau le tableau des salles
	*\param x l'abscisse de la salle concernée (l'origine étant en haut à gauche)
	*\param y l'ordonnée de la salle concernée(l'origine étant en haut à gauche)
*/

void modif_visible_et_etat(salle_t** plateau,int x, int y);

/**
	*\brief Fonction qui tue le joueur sur la case
*/

void Salle_mortelle(persos_t* player,salle_t* salle);


/**
	*\brief Fonction qui tue un personnage après une activation de la case
*/
void Salle_chute(persos_t* perso,salle_t* salle);

/**
	*\brief Fonction qui appel la fonction regarder pour une cases sur le plateau
*/
void Salle_vision(salle_t ** pl, int x, int y);


/**
	*\brief Fonction qui appel la fonction déplacer pour mouvoir les lignes ou colonnes
*/
void Salle_controle(salle_t** pl, char* direction, int nbRangee,persos_t* p);

/**
	*\brief Fonction qui place le personnage sur la case de départ
*/
void Salle_vortex(persos_t* perso);

/**
	*\brief Fonction qui déplace le personnage sur un deuxième case tunnel si elle est découverte
*/
void Salle_tunnel(salle_t** pl, persos_t* perso);


/**
	*\brief Fonction qui initialise les états de la salle et qui permet la victoire
*/
void Salle_25();


/**
	*\brief Fonction qui oblige le joueur à programmer une seule action
*/
void Salle_froide(persos_t* perso);

/**
	*\brief Fonction qui permet d'échanger la position du joueur étant sur la salle mobile avec la position d'une autre salle caché
*/
void Salle_mobile(salle_t** pl,salle_t* salle, persos_t* perso );


void Salle_noire(salle_t** pl, persos_t* perso);


void Salle_prison(salle_t** pl,salle_t salle,persos_t* perso);
#endif
