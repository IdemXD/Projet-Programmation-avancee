/**
	*\file testActions.c
	*\author Chloe Mathias
*/

#include <stdio.h>
#include <stdlib.h>

#include "actions.h"
#include "personnages.h"
#include "plateau.h"
#include "salle.h"

void affichage_visible(salle_t** pl){
	for (int i = 0;i< TAILLE_PL;i++){
		for (int j = 0;j< TAILLE_PL;j++){
			printf("| %d | ",pl[i][j].visible);
		}
		printf("\n");
	}
}

void affichage_utilisable(salle_t** pl){
	for (int i = 0;i< TAILLE_PL;i++){
		for (int j = 0;j< TAILLE_PL;j++){
			printf("| %d | ",pl[i][j].state);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[]) {

	salle_t ** pl;
	persos_s* p;

	pl = creer_plateau();
	
	p = creer_persos();
	//En attente du débogage du plateau
	affichage_plateau_brut(pl);
	//Test avec une salle normale
	regarder(pl,0,0);
	affichage_plateau_brut(pl);
	printf("\n");
	affichage_visible(pl);
	printf("\n");
	affichage_utilisable(pl);

	//Test avec une salle tunnel
	//Avec une seule salle visible

	free_plateau(pl);
	liberer_persos(p);

	return 0;
}