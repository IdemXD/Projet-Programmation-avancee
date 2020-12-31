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
    char SALLES[13] = {'V', 'C', 'O', 'S', 'E', 'F', 'M', 'D', 'N', 'T', 'X', 'P', 'Z'};
    empiler_pile(pile, SALLES[0]);
    empiler_pile(pile, SALLES[1]);
    empiler_pile(pile, SALLES[2]);
    empiler_pile(pile, SALLES[3]);
    empiler_pile(pile, SALLES[4]);
    empiler_pile(pile, SALLES[5]);
    empiler_pile(pile, SALLES[6]);
    empiler_pile(pile, SALLES[7]);
    empiler_pile(pile, SALLES[8]);


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
