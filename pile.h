
#ifndef PILE_H
#define PILE_H

#include <stdio.h>
#include <stdlib.h>
#include "salle.h"




typedef struct Element Element;

struct Element

{

    int salle;

    Element *suivant;

};

typedef struct Pile Pile;

struct Pile

{

    Element *premier;

};



Pile *initialiser();


void affichage_pile(Pile* pile);


void empiler_pile(Pile* pile, char salle);


int depiler(Pile* pile);

void creer_pile(Pile* pile);

#endif

