
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include <SDL2/SDL_ttf.h>
#include "personnages.h"

int main(int argc, char *argv[]){
	SDL_Window* fenetre;  
	// Déclaration de la fenêtre
	SDL_Event evenements; 
	// Événements liés à la fenêtre
	SDL_Renderer* ecran;
	persos_s* joueur;
	ressources textures;
	bool terminer = false;

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
		affiche_joueur(ecran,textures.j1,joueur[0],0);
		affiche_joueur(ecran,textures.j2,joueur[1],1);
	


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
					}
						
			}
		SDL_RenderPresent(ecran);
	}
	// Fermer la police et quitter SDL_ttf
	TTF_Quit();
	//Libération de l’écran (renderer)
	liberer_textures(&textures);
	liberer_persos(joueur);
	SDL_DestroyRenderer(ecran);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}