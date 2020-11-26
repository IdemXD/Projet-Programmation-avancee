#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include "fonctions_SDL.h"
#include "personnages.h"
#include "plateau.h"
#include "actions.h"

int main(int argc, char *argv[]){
	SDL_Window* fenetre;
	// Déclaration de la fenêtre
	SDL_Event evenements;
	// Événements liés à la fenêtre
	SDL_Renderer* ecran;
	persos_t* joueur;
	action_t* actions;
	ressources textures;

	salle_t** salles = creer_plateau();
	init_salles(salles);

	int terminer = 0;
	int choix_action = 1; // Si le joueur choisit son action
	int etape = 1; //etape 1 : choix de l'action
	char active_direction = 'n'; // définit quel direction choisit le joueur
	int nb_action = 0, trouve = 0, tour_perso = 0,tour_action = 0;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	// Initialisation de la SDL
	{
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	// Créer la fenêtre
	fenetre = SDL_CreateWindow("Freedom", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 900, 600, SDL_WINDOW_RESIZABLE);

	if(fenetre == NULL)
		// En cas d’erreur
	{
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
	return EXIT_FAILURE;
	}


	// Mettre en place un contexte de rendu de l’écran

	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

	init_textures(&textures,ecran);
	joueur = creer_persos();
	actions = creer_actions();
	actions[3].etat = 0;


	modif_taille(textures.sprites_elements,actions);

	// Boucle principale
	while(!terminer)
	{

		SDL_RenderClear(ecran);
		SDL_RenderCopy(ecran, textures.fond, NULL, NULL);


		affichage_plateau(ecran,textures,salles);

		affiche_joueur(ecran,textures.sprites_elements,joueur[0],0);
		affiche_joueur(ecran,textures.sprites_elements,joueur[1],1);

		affiche_actions(ecran,textures.sprites_elements,actions[0], 0);
		affiche_actions(ecran,textures.sprites_elements,actions[1], 1);
		affiche_actions(ecran,textures.sprites_elements,actions[2], 2);
		affiche_actions(ecran,textures.sprites_elements,actions[3], 3);

		while( SDL_PollEvent( &evenements ) )
			switch(evenements.type)
			{
				case SDL_QUIT:
					terminer = 1;
					break;
				case SDL_KEYDOWN:
					switch(evenements.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						case SDLK_q:
							terminer = 1;
							break;

						case SDLK_DOWN:

							if(etape == 2 && (joueur[tour_perso].actions[tour_action] == 1 || joueur[tour_perso].actions[tour_action] == 2)){ //Seulement si le joueur est en train de faire un choix de direction
								active_direction = 'b';
							}

							break;

						case SDLK_UP:
							if(etape == 2 && (joueur[tour_perso].actions[tour_action] == 1 || joueur[tour_perso].actions[tour_action] == 2)){
								active_direction = 'h';
							}

							break;

						case SDLK_LEFT:

							if (etape == 2 && (joueur[tour_perso].actions[tour_action] == 1|| joueur[tour_perso].actions[tour_action]== 2)){
								active_direction = 'g';
							}
							break;

						case SDLK_RIGHT:
							if(etape == 2 && (joueur[tour_perso].actions[tour_action] == 1 || joueur[tour_perso].actions[tour_action] == 2)){
								active_direction = 'd';
							}

							break;


					}
					break;
				case SDL_MOUSEBUTTONDOWN:

					if (etape == 1){

						while (nb_action<4 && !trouve){//On détermine si le joueur clique sur un bouton d'actions
							trouve = clic_action(&actions[nb_action],evenements.button.x,evenements.button.y);
							nb_action++;
						}
					}

					if (etape == 2 && joueur[tour_perso].actions[tour_perso] == 0){//Le joueur a choisi "regarder"
						//Déterminer l'emplacement de la souris dans les cases
					}
					break;

			}

		if (trouve){
			nb_action--;

			if (tour_action == 0){//Lorsque le joueur a choisi la première action

				tour_action++;
				actions[3].etat = 1;//Mettre "aucune action" en visible pour la seconde action
			}
			else{//Lorsque le joueur a choisi la deuxième action

				if (nb_action == 3)//Le joueur passe la deuxième action
					joueur[tour_perso].nb_actions = 1; //Modifier le cas ôù le joueur a une seule action : il peut choisir le tour où il l'utilise


				if (tour_perso == NB_PERSONNAGES-1){ //Si le joueur est le dernier à choisir (c'est le joueur à l'indice 1 du tableau de joueurs donc J2)
					tour_perso = 0;
					actions[0].etat = 0;//On affiche plus les boutons d'actions à l'écran
					actions[1].etat = 0;
					actions[2].etat = 0;
					etape++; //Quand on a entré toutes les actions choisies, on passe à l'étape 2
				}
				else{ //Si un joueur a fini de choisir ses actions, on passe au joueur suivant
					tour_perso++;
				}

				tour_action = 0;
				actions[3].etat = 0;
			}


			joueur[tour_perso].actions[tour_perso] = nb_action;//On enregistre le numéro de l'action choisie
			trouve = 0;
			nb_action = 0;

		}

		if (active_direction!='n'){
			//Vérification que ce n'est pas un "aucune action"

			if (joueur[tour_perso].actions[tour_perso] == 1){ //Si le joueur a choisi l'action "se deplacer"

				deplacer(salles,&joueur[tour_perso],&active_direction);

			}else { //Si le joueur a choisi l'action "controler"
				int rangee;
				if (active_direction == 'h' && active_direction == 'b'){
					rangee = joueur[tour_perso].coord_x;
				}
				else{
					rangee = joueur[tour_perso].coord_y;
				}
				controler(salles,&active_direction,rangee,&joueur[tour_perso]);

			}


			if (tour_perso == NB_PERSONNAGES-1){//

				if (tour_action == 1){//On a appliqué la dernière action du dernier joueur
					etape--;
					tour_action = 0;
				}
				else{// On a appliqué la premère action de chaque personnage
					tour_action++;
				}
				tour_perso = 0;
			}
			else{
				tour_perso++;
			}
			active_direction = 'n';//None : aucune action n'a été choisi
		}




		SDL_RenderPresent(ecran);

	}
	// Fermer la police et quitter SDL_ttf
	TTF_Quit();
	//Libération de l’écran (renderer)
	free_plateau(salles);
	//free(actions);
	liberer_textures(&textures);
	liberer_persos(joueur);
	SDL_DestroyRenderer(ecran);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
