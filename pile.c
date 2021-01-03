#include <stdlib.h>
#include <stdio.h>
#include "salle.h"
#include "pile.h"


Pile *initialiser(){
    Pile *pile = malloc(sizeof(*pile));
    pile->premier = NULL;
}


void empiler_pile(Pile* pile, char nvsalle ){
    Element * element = malloc(sizeof(*element));

    if(element == NULL || pile==NULL){
        fprintf(stderr, "Probleme d'allocation\n");
        exit(EXIT_FAILURE);
    }
    element->salle = nvsalle;
    element->suivant = pile->premier;
    pile->premier = element;

}

int depiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int salleDepile = 0;
    Element *elementDepile = pile->premier;

    if (pile != NULL && pile->premier != NULL)
    {
        salleDepile = elementDepile->salle;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }

    return salleDepile;
}

void creer_pile(Pile* pile) {
    for(int i = 0; i < 18; i++) {
        empiler_pile(pile, LETTRES_SALLES[rand() % 18]);
    }
}


void affichage_pile(Pile* pile){
    if (pile == NULL){
        exit(EXIT_FAILURE);
    }
    Element *element = pile->premier;

    while (element != NULL){
        printf("%c\n", element->salle);
        element = element->suivant;
    }
    printf("\n");

}
