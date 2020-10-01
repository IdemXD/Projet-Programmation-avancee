/**
	*\file personnages.c
	*\author Chloe Mathias
	*\version 1.0
*/

#include "personnages.h"
#include "constantes.h"


 character_s*  create_characters()
 {
 	character_s* player = malloc (sizeof(character_s)*NB_PERSONNAGES); //les personnages du joueur
 	for (int i=0; i<NB_PERSONNAGES;i++){
 		player[i].coord_x = 4;//On place les personnages dans la salle de départ (au centre)
 		player[i].coord_y = 4;
 		player[i].state = 1 ; //les personnages sont vivants
 		
 	}
 	return player ;

 }

 void free_characters( character_s*  ch)
 {
 	free(ch);
 }