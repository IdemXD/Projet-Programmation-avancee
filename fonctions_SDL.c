/**
	*\file fonctions_SDL.c
	*\author Chloe Mathias
*/
#include "fonctions_SDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer){
	
	// Chargement d' une image
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	surface = SDL_LoadBMP(nomfichier) ;

	if (surface == NULL){
		printf ("Erreur de chargement de l'image BMP : %s",SDL_GetError());
		return NULL;
	}
	// Conversion de la surface de l’image au format texture avant de l’appliquer
	texture = SDL_CreateTextureFromSurface(renderer,surface) ;
	SDL_FreeSurface(surface);

	if (texture == NULL){
		printf ("Erreur lors de la creation de la texture à partir d'une surface : %s",SDL_GetError());
		return NULL;
	}
	return texture;
}

SDL_Texture * charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b){
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;

	surface = SDL_LoadBMP(nomfichier) ;

	if (surface == NULL){
		printf ("Erreur de chargement de l'image BMP : %s\n",SDL_GetError());
		return NULL;
	}

	// Définition la couleur (pixel transparent) dans une surface.
	if (0!=SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,r,g,b))){
		printf("Erreur de la transparence : %s\n",SDL_GetError());
		return NULL;
	}
	
	texture = SDL_CreateTextureFromSurface(renderer,surface) ;
	SDL_FreeSurface(surface);

	if (texture == NULL){
		printf ("Erreur lors de la creation de la texture à partir d'une surface : %s\n",SDL_GetError());
		return NULL;
	}
	return texture;


}

SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color)
{
	SDL_Surface * surface = NULL;
	SDL_Texture * text = NULL;

	surface = TTF_RenderText_Solid(font,message,color);
	text = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	if (text == NULL){
		printf ("Erreur d'affichage du texte : %s\n",SDL_GetError());
		return NULL;
	}
	return text;


}