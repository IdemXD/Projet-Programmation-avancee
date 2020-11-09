
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include "fonctions_SDL.h"
#include "personnages.h"
#include "actions.h"

int main(int argc, char *argv[]){
	SDL_Window* fenetre;  
	// Déclaration de la fenêtre
	SDL_Event evenements; 
	// Événements liés à la fenêtre
	SDL_Renderer* ecran;
	persos_s* joueur;
	ressources textures;

	salle_t** salles = creer_plateau();
	init_salles(salles);
	bool terminer = false;
	bool choix_action = false; // Si le joueur doit la direction de son action
	char active_direction = 'n'; // définit quel direction choisit le joueur 

	if(SDL_Init(SDL_INIT_VIDEO) < 0) 
	// Initialisation de la SDL
	{
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	// Créer la fenêtre
	fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 900, 600, SDL_WINDOW_RESIZABLE);
	
	if(fenetre == NULL) 
		// En cas d’erreur
	{
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
	return EXIT_FAILURE;
	}

	joueur = creer_persos();

	// Mettre en place un contexte de rendu de l’écran
	
	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
	init_textures(&textures,ecran);


	// Boucle principale
	while(!terminer)
	{
		SDL_RenderClear(ecran);
		SDL_RenderCopy(ecran, textures.fond, NULL, NULL);
		affichage_plateau(ecran,textures,salles);
		affiche_joueur(ecran,textures.sprites,joueur[0],0);
		affiche_joueur(ecran,textures.sprites,joueur[1],1);

		while( SDL_PollEvent( &evenements ) )
			switch(evenements.type)
			{
				case SDL_QUIT:
					terminer = true; 
					break;
				case SDL_KEYDOWN:
					switch(evenements.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						case SDLK_q:
							terminer = true;  
							break;

						case SDLK_DOWN:
							if(choix_action){ //Seulement si le joueur est en train de faire un choix de direction
								active_direction = 'b';
							}
							else{
								//Affichage que c'est impossible à faire pour les 4 directions
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
						
			}
		SDL_RenderPresent(ecran);
	}
	// Fermer la police et quitter SDL_ttf
	TTF_Quit();
	//Libération de l’écran (renderer)
	free_plateau(salles);
	liberer_textures(&textures);
	liberer_persos(joueur);
	SDL_DestroyRenderer(ecran);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}