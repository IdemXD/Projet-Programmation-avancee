#include <stdio.h>
#include <stdlib.h>

#include "plateau.h"
#include "salle.h"

int main(int argc, char *argv[]){
    /* Mise en place du plateau */
    // Demande du niveau au joueur puis chargement du niveau correspondant
	salle_t** pl = charger_plateau(preparation_chemin());

    /* Fonctions d'exposition detaillées des salles*/
    affichage_plateau_lettre(pl);
    printf("\n");

    affichage_plateau_coordonnees(pl);
    printf("\n");

    affichage_plateau_caracteristique(pl);
    printf("\n");

	/* Tests de sauvegarde plateau */
	proposition_sauvegarde(pl);

    /* Fonctions de vérification d'intégrité des fichiers */
    // A venir

	/* Fin d'utilisation du plateau */
	free_plateau(pl);
}
