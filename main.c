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

	// Demande du niveau au joueur puis chargement du niveau correspondant
	/*char* nivo[23];
	nivo = preparation_niveau();
	printf("dans main: sortie preparation niveau = %s", nivo);*/
	salle_t** salles = charger_plateau(preparation_niveau());

	int pas_affichage; //variable temporaire
	int terminer = 0;
	int etape = 1; //etape 1 : choix de l'action
	char active_direction = 'n'; // définit quel direction le joueur choisit
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

	printf("Tour du personnage %d \n",tour_perso);
	printf("Action numéro %d \n\n",tour_action);
	// Boucle principale
	while(!terminer)
	{

		SDL_RenderClear(ecran);
		SDL_RenderCopy(ecran, textures.fond, NULL, NULL);


		affichage_plateau(ecran,textures,salles);

		affiche_joueur(ecran,textures.sprites_elements,joueur[0],0);
		affiche_joueur(ecran,textures.sprites_elements,joueur[1],1);

		affiche_action(ecran,textures.sprites_elements,actions[0], 0);
		affiche_action(ecran,textures.sprites_elements,actions[1], 1);
		affiche_action(ecran,textures.sprites_elements,actions[2], 2);
		affiche_action(ecran,textures.sprites_elements,actions[3], 3);

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
						clic_action(actions,&nb_action,&trouve,evenements.button.x,evenements.button.y);

					}

					if (etape == 2 && joueur[tour_perso].actions[tour_action] == 0){//Le joueur a choisi "regarder"


						int x,y;
						pixToSalle(evenements.button.x,evenements.button.y,&x,&y);

						regarder(salles,x,y);
						pas_affichage = 0;
						change_action(actions,&tour_action,&tour_perso,&etape,&pas_affichage);

						if (pas_affichage == 0)
							if(joueur[tour_perso].actions[tour_action] == 0){

								printf("Cliquez sur la case que vous voulez voir\n");
							} else {
								if (joueur[tour_perso].actions[tour_action] == 1 || joueur[tour_perso].actions[tour_action] == 2)
									printf("Choisissez la direction avec les touches directionnelles du clavier\n");
							}
					}
					break;

			}

		if (trouve){

			joueur[tour_perso].actions[tour_action] = nb_action;//On enregistre le numéro de l'action choisie
			pas_affichage = 1;
			change_perso(actions,joueur,&tour_action,&tour_perso,&etape,&nb_action,&pas_affichage);
			trouve = 0;
			if (pas_affichage == 0)
				if(joueur[tour_perso].actions[tour_action] == 0){

					printf("Cliquez sur la case que vous voulez voir\n");
				} else {
					if (joueur[tour_perso].actions[tour_action] == 1 || joueur[tour_perso].actions[tour_action] == 2)
						printf("Choisissez la direction avec les touches directionnelles du clavier\n");
				}

		}

		if (active_direction!='n'){
			//On attend que le joueur choisisse une direction pour appliquer l'action 'contrôler' ou 'déplacer'
			applique_action(salles, joueur, &active_direction,tour_action,tour_perso);
			pas_affichage = 0;
			change_action(actions,&tour_action,&tour_perso,&etape,&pas_affichage);
			active_direction = 'n';//On remet à aucune action choisie

			if (pas_affichage == 0)
				if(joueur[tour_perso].actions[tour_action] == 0){

					printf("Cliquez sur la case que vous voulez voir\n");
				} else {
					if (joueur[tour_perso].actions[tour_action] == 1 || joueur[tour_perso].actions[tour_action] == 2)
						printf("Choisissez la direction avec les touches directionnelles du clavier\n");
				}
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
	joueur = NULL;
	SDL_DestroyRenderer(ecran);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
