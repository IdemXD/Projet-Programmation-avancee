/**
	*\file actions.c
	*\author Chloe Mathias
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "actions.h"


action_t * creer_actions(){
	//allocation mémoire
	action_t* actions = (action_t *) malloc(sizeof(action_t)*4);

	//Initialisation des champs
	for (int i = 0;i < 4;i++){
		init_action(&actions[i],i);
		
	}
	return actions;
}

void init_action(action_t* action,int numA){

	int abs = numA%2, ord = numA/2;

	action->x_pix = 610 + abs*130;
	action->y_pix = 350 + ord*130;
	action->etat = 1;
	action->hauteur_pix = 0;
	action->largeur_pix = 0;

}

void affiche_donnees_action(action_t action){
	printf("x = %d\ny = %d\netat = %d\nhauteur = %d\nlargeur = %d\n",action.x_pix,action.y_pix,action.etat,action.hauteur_pix,action.largeur_pix);
}

int est_choisie(action_t* action, int x_souris,int y_souris){
	return sqrt((action->x_pix + (action->largeur_pix/2)- x_souris)*(action->x_pix + (action->largeur_pix/2)- x_souris) + (action->y_pix + (action->hauteur_pix/2)- y_souris)*(action->y_pix + (action->hauteur_pix/2)- y_souris)) <= action->hauteur_pix/2;
}

void clic_action(action_t* actions,int* nb_action,int* trouve,int x,int y){

	while (*nb_action<4 && actions[*nb_action].etat && !(*trouve)){//On détermine si le joueur clique sur un bouton d'actions
		*trouve = est_choisie(&actions[*nb_action],x,y);
		*nb_action = *nb_action + 1;
	}
	*nb_action = *nb_action - 1;//On a incrémenté une fois de trop dans la boucle

	if (!(*trouve)){
		*nb_action = 0;
	}

}

void applique_action(salle_t** plateau, persos_t* joueur, char* active_direction,int tour_action,int tour_perso){
	//printf("FDV %d\n",joueur[tour_perso].actions[tour_action]);
	if (joueur[tour_perso].actions[tour_action] == 1){ //Si le joueur a choisi l'action "se deplacer"

		deplacer(plateau,&joueur[tour_perso],active_direction);

	}else { //Si le joueur a choisi l'action "controler"

		int rangee;
		if (*active_direction == 'h' || *active_direction == 'b'){ 
			rangee = joueur[tour_perso].coord_x;

		}
		else{
			rangee = joueur[tour_perso].coord_y;
		}
		
		controler(plateau,active_direction,rangee,joueur);
	}
}


void deplacer(salle_t** plateau,persos_t* perso,char* direction){
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
		
		modif_visible_et_etat(plateau,perso->coord_x,perso->coord_y);
		char c = 'g'; //Variable à enlever quand action_salle sera modifié
		//action_salle(plateau,perso,&plateau[perso->coord_y][perso->coord_x].type,&c,'g',0,0,&plateau[perso->coord_y][perso->coord_x]);// Les 3 derniers paramètres sont seulement là pour utiliser la fonction
		
}

void pixToSalle(int x_pix,int y_pix,int* x, int* y){
	if (x_pix < TAILLE_S*5 && y_pix <TAILLE_S*5){
		*x = x_pix/TAILLE_S;
		*y = y_pix/TAILLE_S;
	}
}

void regarder(salle_t** plateau,int x,int y){
	
	modif_visible_et_etat(plateau,x,y);
}

void controler(salle_t** plateau, char* direction, int nbRangee, persos_t* p){

	if (nbRangee != 2){
		int mvt, case_depl;
		
		/*
			Dans le cas où on déplace vers le haut et la gauche, on commence par enregistrer la case 0.
			Ensuite, on déplace chaque case vers le haut ou la gauche du rang 0 à 3([0]<=[1]...[3]<=[4])
			case_depl indique l'indice de la carte recevant la nouvelle salle
			Enfin, on place la salle sauvegardé dans la dernière case de la ligne ([4]<=tmp soit [0] précédent)

			Dans le cas où on déplace vers le bas et la droite, on commence par enregistrer la dernière case.
			Ensuite, on déplace chaque case vers le haut ou la gauche du rang 4 à 1 ([4]<=[3]...[1]<=[0])
			La case qui va recevoir tmp est la première case de la rangée ([0]<=tmp soit [4] précédent)

			mvt permet de déterminer l'indice de la salle déplacé (par ex : pour d et b, [2]<=[1] 1 = 2 + mvt = 2 - 1)

		*/
		switch (*direction)
		{
			case 'h' : 
			case 'g' :
				
				case_depl = 0;
				mvt = 1;
				break;

			case 'b' :
			case 'd' :

				case_depl = 4;
				mvt = -1;
				break;
		}

		for (int i = 0 ;i<NB_PERSONNAGES;i++){
			//Le joueur se trouve sur la rangée déplacée
			if ((p[i].coord_x==nbRangee && (*direction=='h'||*direction == 'b'))||(p[i].coord_y==nbRangee)&&(*direction=='g'||*direction == 'd')){
				if (*direction == 'h'||*direction == 'b'){

					if (p[i].coord_y==case_depl){
						//Si le personnage est sur une case qui est replacée de l'autre côté de la rangée

						//Deux cas possibles, soit direction ='h' et case depl = 0 on a alors [4]<=[0], soit direction ='b' et case depl = 4 on a alors [0]<=[4]; 
						p[i].coord_y = 4 - case_depl ;
					}
					else{
						// Le personnage est sur une salle qui va être glissée d'un côté
						// - mvt = +1 si on va vers le bas et -1 si on va vers le haut
							p[i].coord_y = p[i].coord_y - mvt;
					}
				}
				else {
					if (p[i].coord_x==case_depl){
							//Deux cas possibles, soit direction ='g' et case depl = 0 on a alors [4]<=[0], soit direction ='d' et case depl = 4 on a alors [0]<=[4]; 
							p[i].coord_x = 4 - case_depl;
					}
					else{
							// - mvt = +1 si on va vers la droite et -1 si on va vers la gauche
							p[i].coord_x = p[i].coord_x - mvt;
					}
				}
			}	
		}

		salle_t tmp;

		// On stocke la salle qui va se retrouver de l'autre côté de la rangée
		if (*direction == 'h'||*direction == 'b'){
			tmp = plateau[case_depl][nbRangee];
		}
		else {
			tmp = plateau[nbRangee][case_depl];
		}

		while (case_depl+mvt>=0&&case_depl+mvt<TAILLE_PL){
			//On vérifie que la case dont on veut prendre le contenu est dans le plateau (exemple direction ='b',à la sortie case_depl = 0 mais case_depl+mvt =-1)
			if (*direction == 'h'||*direction == 'b'){
				plateau[case_depl][nbRangee] = plateau[case_depl+mvt][nbRangee];
			}
			else{
				plateau[nbRangee][case_depl] = plateau[nbRangee][case_depl+mvt];
			}
			case_depl = case_depl + mvt;
		}

		if (*direction == 'h'||*direction == 'b'){
			plateau[case_depl][nbRangee] = tmp;
		}
		else {
			plateau[nbRangee][case_depl] = tmp;
		}
		
		for(int i = 0; i < TAILLE_PL; i++){
        	for (int j = 0; j < TAILLE_PL; j++){

            	plateau[i][j].x = j ; 
    			plateau[i][j].y = i ;
       		}
    	}
	}

}

void change_perso(action_t* actions,persos_t* joueur,int* tour_action,int* tour_perso,int* etape,int* nb_action, int* pas_affichage){
	if (*tour_action == 0){//Lorsque le joueur a choisi la première action

		*tour_action = *tour_action + 1;
		actions[3].etat = 1;//Mettre "aucune action" en visible pour la seconde action
	}
	else{//Lorsque le joueur a choisi la deuxième action

		if (*nb_action == 3)//Le joueur passe la deuxième action
			joueur[*tour_perso].nb_actions = 1; //Modifier le cas où le joueur a une seule action : il peut choisir le tour où il l'utilise


		if (*tour_perso == NB_PERSONNAGES-1){ //Si le joueur est le dernier à choisir (c'est le joueur à l'indice 1 du tableau de joueurs donc J2)
			*tour_perso = 0;
			actions[0].etat = 0;//On affiche plus les boutons d'actions à l'écran
			actions[1].etat = 0;
			actions[2].etat = 0;
			*etape = *etape + 1; //Quand on a entré toutes les actions choisies, on passe à l'étape 2
			*pas_affichage = 0;
		}
		else{ //Si un joueur a fini de choisir ses actions, on passe au joueur suivant
			*tour_perso = *tour_perso + 1;
		}

		*tour_action = 0;
		actions[3].etat = 0;
	}

	*nb_action = 0;

}

void change_action(action_t* actions,int* tour_action,int* tour_perso,int* etape,int* pas_affichage){
	if (*tour_perso == NB_PERSONNAGES-1){
		
		if (*tour_action == 1){//On a appliqué la dernière action du dernier joueur
			*etape = *etape - 1;
			actions[0].etat = 1;//On affiche plus les boutons d'actions à l'écran
			actions[1].etat = 1;
			actions[2].etat = 1;
			*tour_action = 0;
			*pas_affichage = 1;
			
		}
		else{// On a appliqué la premère action de chaque personnage
			*tour_action = *tour_action + 1;
			
		}
		*tour_perso = 0;
		
	}
	else{
		*tour_perso = *tour_perso + 1;
	}
}