#ifndef Salle_h
#define Salle_h

#include "plateau.h"

struct Salle
{
    int x;      /*!< Tableau contenant la coordonnée x de la salle */
    int y;      /*!< Tableau contenant la coordonnée y de la salle */
    int etat;   /*!< Etat de la salle(1 si la salle est utilisable )*/
    char S;     
    char R;
    char E;
    char V;
    char X;
    char T;
    char C; 
    char F;
    char M;
    char O;
    char N;
};
typedef struct Salle Salle_t;
