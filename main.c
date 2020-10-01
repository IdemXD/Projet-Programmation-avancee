
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include <SDL2/SDL_ttf.h>

int main(int argc, char *argv[]){
	SDL_Window* fenetre;  
	// Déclaration de la fenêtre
	SDL_Event evenements; 
	// Événements liés à la fenêtre
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

	// Mettre en place un contexte de rendu de l’écran
	SDL_Renderer* ecran;
	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
	// Charger l’image
	SDL_Texture* fond = charger_image("ressources/background.bmp", ecran );

	// Charger l’image avec la transparence
	Uint8 r = 255, g = 0, b = 255;
	SDL_Texture* obj = charger_image_transparente("ressources/character1.bmp", ecran,r,g,b);
	
	int objetW;
	int objetH;

	SDL_QueryTexture(obj, NULL, NULL, &objetW,&objetH);

	SDL_Rect SrcR, DestR;
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = objetW; // Largeur de l’objet en pixels 
	SrcR.h = objetH; // Hauteur de l’objet en pixels 

	DestR.x = 350;
	DestR.y = 350;
	DestR.w = objetW;
	DestR.h = objetH;

	// Boucle principale
	while(!terminer)
	{
		SDL_RenderClear(ecran);
		SDL_RenderCopy(ecran, fond, NULL, NULL);
		SDL_RenderCopy(ecran, obj, &SrcR, &DestR);



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
	// Libération de l’écran (renderer)
	SDL_DestroyRenderer(ecran);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}