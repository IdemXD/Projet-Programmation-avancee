#include <stdlib.h>
#include <stdio.h>
#include "salle.h"
#include "pile.h"

Pile *initialiser(){
    Pile *pile = malloc(sizeof(*pile));
    pile->premier = NULL;
}


void empiler_pile(Pile pile, const char LETTRES_SALLES[14]){
    Element *nouveau_element = malloc(sizeof(*nouveau_element));

    if(nouveau_element == NULL || pile=NULL){
        fprintf(stderr, "Probleme d'allocation\n");
        exit(EXIT_FAILURE);
    }

    nouveau_element->salle.type=nvsalle;
    nouveau_element->suivant = pile->premier;
    pile->premier = nouveau_element;

}

int depiler(Pile *pile){
    if (pile == NULL){
        exit(EXIT_FAILURE);
    }

    char *salleDepile = 0;
    Element *elementDepile = pile->premier;

    if (pile != NULL && pile->premier != NULL){
        salleDepile = elementDepile->salle.type;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }
    return;
}


void affichage_pile(Pile* pile){
    if (pile == NULL){
        exit(EXIT_FAILURE);
    }
    Element *element = pile->premier;

    while (element != NULL){
        printf("%d\n", element->salle.type);
        element = element->suivant;
    }
    printf("\n");

}


Pile free_pile(Pile pile){
    while(pile!=NULL) {
        pile = depiler(pile);
    }
    return pile;
}