#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "actions.h"
#include "fonctions_SDL.h"
#include "personnages.h"
#include "plateau.h"
#include "data_monde.h"


int main(int argc, char *argv[]){
	SDL_Window* fenetre;
	// Déclaration de la fenêtre
	SDL_Event evenements;
	// Événements liés à la fenêtre
	SDL_Renderer* ecran;

	ressources textures;

	data_t* data;
	data = init_data();

	int pas_affichage; //variable temporaire

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

	modif_taille(textures.sprites_elements,data->actions);

	printf("Tour du personnage %d \n",data->tour_perso);
	printf("Action numéro %d \n\n",data->tour_action);
	// Boucle principale
	while(!data->terminer)
	{
		refresh_game(ecran, textures, data);


		while( SDL_PollEvent( &evenements ) )
			switch(evenements.type)
			{
				case SDL_QUIT:
					data->terminer = 1;
					break;
				case SDL_KEYDOWN:
					switch(evenements.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						case SDLK_q:
							data->terminer = 1;
							break;

						case SDLK_DOWN:

							if(data->etape == 2 && (data->joueur[data->tour_perso].actions[data->tour_action] == 1 || data->joueur[data->tour_perso].actions[data->tour_action] == 2)){ //Seulement si le joueur est en train de faire un choix de direction
								data->active_direction = 'b';
							}

							break;

						case SDLK_UP:
							if(data->etape == 2 && (data->joueur[data->tour_perso].actions[data->tour_action] == 1 || data->joueur[data->tour_perso].actions[data->tour_action] == 2)){
								data->active_direction = 'h';
							}

							break;

						case SDLK_LEFT:

							if (data->etape == 2 && (data->joueur[data->tour_perso].actions[data->tour_action] == 1|| data->joueur[data->tour_perso].actions[data->tour_action]== 2)){
								data->active_direction = 'g';
							}
							break;

						case SDLK_RIGHT:
							if(data->etape == 2 && (data->joueur[data->tour_perso].actions[data->tour_action] == 1 || data->joueur[data->tour_perso].actions[data->tour_action] == 2)){
								data->active_direction = 'd';
							}

							break;


					}
					break;
				case SDL_MOUSEBUTTONDOWN:

					if (data->etape == 1){
						clic_action(data->actions,&(data->nb_action),&(data->trouve),evenements.button.x,evenements.button.y);

					}

					if (data->etape == 2 && data->joueur[data->tour_perso].actions[data->tour_action] == 0){//Le joueur a choisi "regarder"


						int x,y;
						pixToSalle(evenements.button.x,evenements.button.y,&x,&y);

						regarder(data->salles,x,y);
						pas_affichage = 0;
						change_action(data->actions,&(data->tour_action),&(data->tour_perso),&(data->etape),&pas_affichage);

						if (pas_affichage == 0)
							if(data->joueur[data->tour_perso].actions[data->tour_action] == 0){

								printf("Cliquez sur la case que vous voulez voir\n");
							} else {
								if (data->joueur[data->tour_perso].actions[data->tour_action] == 1 || data->joueur[data->tour_perso].actions[data->tour_action] == 2)
									printf("Choisissez la direction avec les touches directionnelles du clavier\n");
							}
					}
					break;

			}

		if (data->trouve){

			data->joueur[data->tour_perso].actions[data->tour_action] = data->nb_action;//On enregistre le numéro de l'action choisie
			pas_affichage = 1;
			change_perso(data->actions,data->joueur,&(data->tour_action),&(data->tour_perso),&(data->etape),&(data->nb_action),&pas_affichage);
			data->trouve = 0;
			if (pas_affichage == 0)
				if(data->joueur[data->tour_perso].actions[data->tour_action] == 0){

					printf("Cliquez sur la case que vous voulez voir\n");
				} else {
					if (data->joueur[data->tour_perso].actions[data->tour_action] == 1 || data->joueur[data->tour_perso].actions[data->tour_action] == 2)
						printf("Choisissez la direction avec les touches directionnelles du clavier\n");
				}

		}

		if (data->active_direction!='n'){
			//On attend que le joueur choisisse une direction pour appliquer l'action 'contrôler' ou 'déplacer'
			applique_action(data->salles, data->joueur, &(data->active_direction),data->tour_action,data->tour_perso);
			pas_affichage = 0;
			change_action(data->actions,&(data->tour_action),&(data->tour_perso),&(data->etape),&pas_affichage);
			data->active_direction = 'n';//On remet à aucune action choisie

			if (pas_affichage == 0)
				if(data->joueur[data->tour_perso].actions[data->tour_action] == 0){

					printf("Cliquez sur la case que vous voulez voir\n");
				} else {
					if (data->joueur[data->tour_perso].actions[data->tour_action] == 1 || data->joueur[data->tour_perso].actions[data->tour_action] == 2)
						printf("Choisissez la direction avec les touches directionnelles du clavier\n");
				}
		}




		SDL_RenderPresent(ecran);

	}
	clean_game(fenetre, ecran, &textures, data);
	return 0;
}
