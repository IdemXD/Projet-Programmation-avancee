/**
	*\file actions.c
	*\author Chloe Mathias
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "actions.h"


action_t * creer_actions(char type_de_jeu){
	//allocation mémoire
	action_t* actions = (action_t *) malloc(sizeof(action_t)*NB_ACTIONS_TOTAl);

	//Initialisation des champs
	for (int i = 0;i < NB_ACTIONS_TOTAl;i++){
		init_action(&actions[i],i);
	}
	if (type_de_jeu == 's')//En mode solo, on utilise pas pousser 
		actions[3].etat = 0;
	actions[4].etat = 0;//Pour la première action, on ne peut pas passer 
	return actions;
}

void init_action(action_t* action,int numA){
	//Dans l'ordre de numA, on a REGARDER, DEPLACER, CONTROLER, POUSSER et AUCUNE ACTION
	int abs = numA%3, ord = numA/3;

	action->x_pix = 610 + abs*100;
	action->y_pix = 350 + ord*100;
	action->etat = 1;
	action->hauteur_pix = 0;
	action->largeur_pix = 0;

}

void affiche_donnees_action(action_t action){
	printf("x = %d\ny = %d\netat = %d\nhauteur = %d\nlargeur = %d\n",action.x_pix,action.y_pix,action.etat,action.hauteur_pix,action.largeur_pix);
}

int est_choisie(action_t* action, int x_souris,int y_souris){
	return sqrt((action->x_pix + (action->largeur_pix / 2) - x_souris) *
                (action->x_pix + (action->largeur_pix / 2) - x_souris) +
                (action->y_pix + (action->hauteur_pix / 2) - y_souris) *
                (action->y_pix + (action->hauteur_pix / 2) - y_souris)) <= action->hauteur_pix / 2;
}

void clic_action(action_t* actions,int* nb_action,int* trouve,int x,int y){

	while (*nb_action<NB_ACTIONS_TOTAl && !(*trouve)){//On détermine si le joueur clique sur un bouton d'actions actif
		if (actions[*nb_action].etat){
			*trouve = est_choisie(&actions[*nb_action],x,y);
		}
		*nb_action = *nb_action + 1;
	}
	*nb_action = *nb_action - 1;//On a incrémenté une fois de trop dans la boucle
	
	if (!(*trouve)){
		*nb_action = 0;
	} 

}

void applique_action(salle_t** plateau, persos_t* joueurs, char* active_direction,int tour_action,int tour_perso,int nb_personnage){
	
	if (joueurs[tour_perso].actions[tour_action] == 1){ //Si le joueur a choisi l'action "se deplacer"

		deplacer(plateau,&joueurs[tour_perso],active_direction);

	}
	if (joueurs[tour_perso].actions[tour_action] == 2) { //Si le joueur a choisi l'action "controler"

		int rangee;
		if (*active_direction == 'h' || *active_direction == 'b'){ 
			rangee = joueurs[tour_perso].coord_x;

		}
		else{
			rangee = joueurs[tour_perso].coord_y;
		}
		
		controler(plateau,active_direction,rangee,joueurs,nb_personnage);
	}
	if (joueurs[tour_perso].actions[tour_action] == 3) {//Si le joueur choisit "pousser"
		pousser(joueurs,tour_perso,nb_personnage,active_direction,plateau);
	} 
}


void deplacer(salle_t** plateau,persos_t* perso,const char* direction){
		//Cas où le joueur choisit droite
	if(perso->coord_x+1 < TAILLE_PL && *direction == 'd'){
		perso->coord_x = perso->coord_x + 1 ;
	}
	//Cas où le joueur choisit gauche
	else if(perso->coord_x-1 >= 0 && *direction == 'g'){
		perso->coord_x = perso->coord_x - 1 ;
	}
	//Cas où le joueur choisit bas
	else if (perso->coord_y+1 < TAILLE_PL && *direction == 'b'){
		perso->coord_y = perso->coord_y + 1 ;
	}
	//Cas où le joueur choisit haut
	else if (perso->coord_y-1 >= 0 && *direction == 'h'){
		perso->coord_y = perso->coord_y - 1 ;	
	}
	
	modif_visible_et_etat(plateau,perso->coord_x,perso->coord_y);

}

char lettre_action(int numero,int etape){
	char lettre;
	if (etape == 2){
		switch (numero){
			case 0:
				lettre = 'R';//Regarder
				break;
			case 1:
				lettre = 'D';//Se déplacer
				break;
			case 2:
				lettre = 'C';//Contrôler
				break;
			case 3:
				lettre = 'P';//Pousser
				break;
			case 4:
				lettre = 'N';//None, aucune action
				break;
			default :
				lettre = ' ';
				break;
		}
	} else {
		lettre = ' ';
	}
	return lettre;
}

void pixToSalle(int x_pix,int y_pix,int* x, int* y){
	if (x_pix < TAILLE_S*TAILLE_PL && y_pix <TAILLE_S*TAILLE_PL){
		*x = x_pix/TAILLE_S;
		*y = y_pix/TAILLE_S;
	}
}

void regarder(salle_t** plateau,int x,int y){
	
	modif_visible_et_etat(plateau,x,y);
}

void controler(salle_t** plateau, const char* direction, int nbRangee, persos_t* p, int nb_personnages){

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

		for (int i = 0 ;i<nb_personnages;i++){
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

void prochain_vivant(int* tour_perso,int nb_personnage,persos_t* joueur){

	do {
		
		*tour_perso = *tour_perso + 1;
		
	} while (*tour_perso != nb_personnage-1 && !joueur[*tour_perso].state);//On cherche le prochain joueur en vie
	if (*tour_perso > nb_personnage-1)
		*tour_perso = nb_personnage-1;
}

void change_perso(action_t* actions,persos_t* joueurs,int* tour_action,int* tour_perso,int* etape,int* nb_action, int* affiche_message,int nb_personnages,char type_de_jeu){
	
	if (*tour_action == joueurs[*tour_perso].nb_actions - 1) {//Lorsque le joueur a choisi sa dernière action
		
		if (*nb_action == 4){
			joueurs[*tour_perso].nb_actions = 1;
		}
		

		if (*tour_perso == nb_personnages-1){ //Si le joueur est le dernier à choisir
			
			*tour_perso = 0;
			actions[0].etat = 0;//On affiche plus les boutons d'actions à l'écran
			actions[1].etat = 0;
			actions[2].etat = 0;
			if (type_de_jeu == 'm')
				actions[3].etat = 0;
			*etape = *etape + 1; //Quand on a entré toutes les actions choisies, on passe à l'étape 2
			*affiche_message = 0;
		}
		else{ //Si un joueur a fini de choisir ses actions, on passe au joueur suivant
			prochain_vivant(tour_perso,nb_personnages,joueurs);
			if (*tour_perso == nb_personnages -1 && !joueurs[*tour_perso].state){//Si aucun joueur n'est vivant à la fin
				*tour_perso = 0;
				actions[0].etat = 0;//On affiche plus les boutons d'actions à l'écran
				actions[1].etat = 0;
				actions[2].etat = 0;
				if (type_de_jeu == 'm')
					actions[3].etat = 0;
				*etape = *etape + 1; //Quand on a entré toutes les actions choisies, on passe à l'étape 2
				*affiche_message = 0;
			
			} 
		}

		*tour_action = 0;
		actions[4].etat = 0;
		
	}
	else {
		*tour_action = *tour_action + 1;
		actions[4].etat = 1;//Mettre "aucune action" en visible pour la seconde action
	}

	*nb_action = 0;

}

void change_action(action_t* actions,int* tour_action,int* tour_perso,int* etape,int* pas_affichage,int nb_personnage,persos_t* joueur,char type_de_jeu){
	
	if (*tour_perso == nb_personnage-1){
		
		if (*tour_action == 1){//On a appliqué la dernière action du dernier joueur
			*etape = *etape - 1;
			actions[0].etat = 1;//On affiche plus les boutons d'actions à l'écran
			actions[1].etat = 1;
			actions[2].etat = 1;
			if (type_de_jeu == 'm')
				actions[3].etat = 1;
			*tour_action = 0;
			*pas_affichage = 1;
			*tour_perso = 0;
			for (int i = 0; i<nb_personnage;i++){//on remet tous les nombres d'actions à 2 (sera peut-être modifié)
				joueur[i].nb_actions = 2;
			}
		}
		else{// On a appliqué la premère action de chaque personnage
			*tour_action = *tour_action + 1;
			*tour_perso = 0;
			if (joueur[*tour_perso].nb_actions == 1){//Si aucun des joueurs qui reste n'ont de deuxième action, on repasse à l'étape 1
				change_action(actions,tour_action,tour_perso,etape,pas_affichage,nb_personnage,joueur,type_de_jeu);
			}
		}
		
	}
	else{
		if (*tour_action == 0){//Premier tour d'action
			prochain_vivant(tour_perso,nb_personnage,joueur);
			if (*tour_perso == nb_personnage-1 && !joueur[*tour_perso].state){//Si aucun joueur n'est vivant à la fin
				*tour_action = *tour_action + 1;//On passe à l'action suivante
				*tour_perso = 0;
				if (!joueur[*tour_perso].state)
					prochain_vivant(tour_perso,nb_personnage,joueur);//On cherche le premier joueur vivant
			}

		} else {//Deuxième tour d'action
			//On cherche le prochain joueur qui a une deuxième action
			do {
		
				*tour_perso = *tour_perso + 1;
				
			} while (*tour_perso != nb_personnage-1 && (!joueur[*tour_perso].state || joueur[*tour_perso].nb_actions == 1));//On cherche le prochain joueur en vie
			if (*tour_perso > nb_personnage-1)
				*tour_perso = nb_personnage-1;
			
			if (*tour_perso == nb_personnage-1 && !joueur[*tour_perso].state){
				*etape = *etape - 1;
				actions[0].etat = 1;//On affiche plus les boutons d'actions à l'écran
				actions[1].etat = 1;
				actions[2].etat = 1;
				if (type_de_jeu == 'm')
					actions[3].etat = 1;
				*tour_action = 0;
				*pas_affichage = 1;
				*tour_perso = 0;
				for (int i = 0; i<nb_personnage;i++){//on remet tous les nombres d'actions à 2 (sera peut-être modifié)
					joueur[i].nb_actions = 2;
				}
				if (!joueur[*tour_perso].state)
					prochain_vivant(tour_perso,nb_personnage,joueur);//On cherche le premier joueur vivant
			} else {
				if (*tour_perso == nb_personnage-1 && joueur[*tour_perso].nb_actions == 1){//Si aucun des joueurs qui reste n'ont de deuxième action, on repasse à l'étape 1
					change_action(actions,tour_action,tour_perso,etape,pas_affichage,nb_personnage,joueur,type_de_jeu);
				}
			}

		}
	}
}

void pousser(persos_t* joueurs,int num_joueur, int nb_personnages,char* direction, salle_t** plateau){
	int x = joueurs[num_joueur].coord_x, y = joueurs[num_joueur].coord_y;
	for (int i = 0; i < nb_personnages; i++){
		if (joueurs[i].coord_x == x && joueurs[i].coord_y == y && i != num_joueur){//On cherche les personnages qui sont sur la même case
			deplacer(plateau,&joueurs[i],direction);
		} 
	}
}
