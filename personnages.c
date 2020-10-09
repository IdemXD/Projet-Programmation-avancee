/**
	*\file personnages.c
	*\author Chloe Mathias
	*\version 1.0
*/

#include <stdlib.h>
#include "personnages.h"
#include "constantes.h"


 persos_s*  creer_persos()
 {

 	persos_s* persos = malloc (sizeof(persos_s)*NB_PERSONNAGES); //les personnages du joueur
 	for (int i=0; i<NB_PERSONNAGES;i++){
 		persos[i].coord_x = 2;//On place les personnages dans la salle de départ (au centre)
 		persos[i].coord_y = 2;
 		persos[i].state = 1 ; //les personnages sont vivants
 		
 	}
 	return persos ;

 }


 void liberer_persos(persos_s*  persos)
 {
 	free(persos);
 }