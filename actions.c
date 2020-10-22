/**
	*\file actions.c
	*\author Chloe Mathias
*/

#include <stdlib.h>

#include "actions.h"
#include "personnages.h"
#include "plateau.h"
#include "salle.h"


void deplacer(salle_t** plateau,persos_s* perso,char* direction,int * choix_dir){
	// Le plateau sera utilisé pour l'appel de la fonction des salles
	if (*choix_dir){
		//Lorsque le joueur choisit une direction

		//Cas où le joueur choisit droite
		if(perso->coord_x+1 < 5 && *direction == 'd'){
			perso->coord_x = perso->coord_x + 1 ;
		}
		//Cas où le joueur choisit gauche
		else if(perso->coord_x-1 >= 0 && *direction == 'g'){
			perso->coord_x = perso->coord_x - 1 ;
		}
		//Cas où le joueur choisit bas
		else if (perso->coord_y+1 < 5 && *direction == 'b'){
			perso->coord_y = perso->coord_y + 1 ;
		}
		//Cas où le joueur choisit haut
		else if (perso->coord_y-1 >= 0 && *direction == 'h'){
			perso->coord_y = perso->coord_y - 1 ;	
		}

		if (*direction != 'n'){//None : aucune action n'a été choisi
		//Lorsque le joueur a choisit une direction , il ne peut plus choisir de direction,on rend visible la salle (s'il faut) et on fait l'action de la salle
			*choix_dir = 0;
			*direction = 'n';
			
			modif_visible_et_etat(plateau,perso->coord_x,perso->coord_y);
			action_salle(plateau,perso,&plateau[perso->coord_x][perso->coord_y].type,0,0,&plateau[perso->coord_x][perso->coord_y]);// Les 3 derniers paramètres sont seulement là pour utiliser la fonction

		}
	}
	else{

		*choix_dir = 1;// Pour que l'entrée d'une touche permette de choisir la direction 

	}

}

void regarder(salle_t** plateau,int x,int y){
	
	modif_visible_et_etat(plateau,x,y);
}

void controler(salle_t** plateau, char* direction, int nbRangee){

	if (nbRangee != 2){
		int mvt, case_tmp;

		/* 
			mvt est la direction 
		 */
		switch (*direction)
		{
			case 'h' : 
			case 'g' :

				case_tmp = 0;
				mvt = 1;
				break;

			case 'b' :
			case 'd' :

				case_tmp = 4;
				mvt = -1;
				break;
		}
		//Déplacement du joueur à ajouter
			salle_t tmp;

			if (*direction == 'h'||*direction == 'b'){
				tmp = plateau[case_tmp][nbRangee];
			}
			else {
				tmp = plateau[nbRangee][case_tmp];
			}
			for (int i = 0 ; i<4 ; i++){
				if (*direction == 'h'||*direction == 'b'){
					plateau[i][nbRangee] = plateau[i+mvt][nbRangee];
				}
				else{
					plateau[nbRangee][i] = plateau[nbRangee][i+mvt];
				}
			}
			if (*direction == 'h'||*direction == 'b'){
				plateau[4-case_tmp][nbRangee] = tmp;
			}
			else {
				plateau[nbRangee][4-case_tmp] = tmp;
			}

		///////////////////////////////////////
		/*
		if (*direction == 'h'||*direction == 'b'){
			salle_t tmp = plateau[case_tmp][nbRangee];
			for (int i = 0 ; i<4 ; i++){
				plateau[i][nbRangee] = plateau[i+mvt][nbRangee];
			}
			plateau[4-case_tmp][nbRangee] = tmp;
		}
		else if (*direction == 'g'||*direction == 'd'){
			salle_t tmp = plateau[nbRangee][case_tmp];
			for (int i = 0 ; i<4 ; i++){
				plateau[nbRangee][i] = plateau[nbRangee][i+mvt];
			}
			plateau[nbRangee][4-case_tmp] = tmp;
		*/
	}

}