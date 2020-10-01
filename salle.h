#ifndef SALLE_H
#define SALLE_H

/**
	*\file salle.h
	*\author Boudhane Medi
	*\version 1.0
*/

#include "plateau.h"

struct Salle
{
    int x;      /*!< Tableau contenant la coordonnée x de la salle */
    int y;      /*!< Tableau contenant la coordonnée y de la salle */
    int state;   /*!< Etat de la salle(1 si la salle est utilisable )*/
    char A;      /*!< Char représentant la salle*/
};
typedef struct Salle Salle_t;
