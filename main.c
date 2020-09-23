
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
	fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
	
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
	SDL_Texture* fond = charger_image( "ressources/fond.bmp", ecran );

	// Charger l’image avec la transparence
	Uint8 r = 255, g = 255, b = 255;
	SDL_Texture* obj = charger_image_transparente("ressources/obj.bmp", ecran,r,g,b);
	
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
	DestR.w = objetW/3;
	DestR.h = objetH/3;

	r = 0;//Pour mettre le fond cyan en transparence, on a seulement besoin de modifier le pourcentage de rouge

	SDL_Texture* sprite = charger_image_transparente("ressources/sprites.bmp",ecran,r,g,b);
	int tailleW;
	int tailleH;

	SDL_QueryTexture(sprite, NULL, NULL, &tailleW,&tailleH);

	tailleW = tailleW/3;
	tailleH = tailleH/2;

	SDL_Rect SrcR_sprite[6];

	for (int i=0;i<6;i++)
	{
		SrcR_sprite[i].x = i > 2 ? (i-3)*tailleW : i*tailleW;
		SrcR_sprite[i].y = i > 2 ? tailleH : 0;
		SrcR_sprite[i].w = tailleW;
		SrcR_sprite[i].h = tailleH;

	}

	SDL_Rect DestR_sprite[6];

	for(int i=0; i<6; i++)
	{
		DestR_sprite[i].x = i > 2 ? 60*(i+1)+100 : 60*(i+1);
		DestR_sprite[i].y =  i > 2 ? 60 : 120;
		DestR_sprite[i].w = tailleW; // Largeur du sprite
		DestR_sprite[i].h = tailleH; // Hauteur du sprite
	}

	int texteW;
	int texteH;


	TTF_Init();
	TTF_Font *font = TTF_OpenFont("./ressources/arial.ttf",28);
	SDL_Color color = {0,0,0,0};
	char msg[] = "TP sur Makefile et SDL";
	SDL_Texture* texte = charger_texte(msg,ecran,font,color);

	SDL_QueryTexture(texte,NULL,NULL,&texteW,&texteH);

	SDL_Rect text_pos; // Position du texte

	text_pos.x = 10;
	text_pos.y = 100;

	text_pos.w = texteW; // Largeur du texte en pixels 
	text_pos.h = texteH; // Hauteur du texte en pixels

	// Boucle principale
	while(!terminer)
	{
		SDL_RenderClear(ecran);
		SDL_RenderCopy(ecran, fond, NULL, NULL);
		SDL_RenderCopy(ecran, obj, &SrcR, &DestR);
		for (int i=0; i<6 ; i++){
			SDL_RenderCopy(ecran,sprite,&SrcR_sprite[i],&DestR_sprite[i]);
		}


		//Appliquer la surface du texte sur l’écran
		SDL_RenderCopy(ecran,texte,NULL,&text_pos);

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
	TTF_CloseFont( font );
	TTF_Quit();
	// Libération de l’écran (renderer)
	SDL_DestroyRenderer(ecran);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}