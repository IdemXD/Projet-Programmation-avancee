#ifndef Salle_h
#define Salle_h

#include "plateau.h"

struct Salle
{
    int x;      /*!< Tableau contenant la coordonnée x de la salle */
    int y;      /*!< Tableau contenant la coordonnée y de la salle */
    int state;   /*!< Etat de la salle(1 si la salle est utilisable )*/
    char S;
};
typedef struct Salle Salle_t;
