
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
	char active_direction = 'n'; // définit quel direction choisit le joueur 

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
							if(choix_action){ //Seulement si le joueur est en train de faire un choix de direction
								active_direction = 'b';
							}

							break;

						case SDLK_UP:
							if(choix_action){
								active_direction = 'h';
							}

							break;

						case SDLK_LEFT:
							if(choix_action){ //Seulement si le joueur est en train de faire un choix de direction
								active_direction = 'g';
							}

							break;

						case SDLK_RIGHT:
							if(choix_action){ //Seulement si le joueur est en train de faire un choix de direction
								active_direction = 'd';
							}

							break;


					}
					break;
				case SDL_MOUSEBUTTONDOWN: ;
					int nb_action = 0, trouve = 0;
					while (nb_action<3 && !trouve){
						trouve = clic_action(&actions[nb_action],evenements.button.x,evenements.button.y);
						nb_action++;
					}
					

					break;
						
			}
		/*SDL_RenderClear();
		SDL_RenderCopy();*/

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