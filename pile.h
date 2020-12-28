
#ifndef PILE_H
#define PILE_H

#include <stdio.h>
#include <stdlib.h>
#include "salle.h"
#include "constantes.h"



struct Element
{
    char LETTRES_SALLES[14];
    struct Element *suivant;
};
typedef struct Element Element;

struct Pile
{
    Element *premier;
};
typedef struct Pile Pile;


/* Prototypes des fonctions */


Pile *initialiser();


void affichage_pile(Pile* pile);


void empiler_pile(Pile* pile, const char LETTRES_SALLES[14] );


int depiler(Pile* pile);

Pile free_pile(Pile* pile);

#endif

