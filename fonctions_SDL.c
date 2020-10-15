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

	// Définition de la couleur transparente d'une surface
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

	if (surface == NULL){
		printf ("Erreur de chargement du texte : %s\n",SDL_GetError());
		return NULL;
	}
	text = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);

	if (text == NULL){
		printf ("Erreur d'affichage du texte : %s\n",SDL_GetError());
		return NULL;
	}
	return text;



}

void init_textures(ressources * textures,SDL_Renderer* renderer){


	textures->fond = charger_image("ressources/background.bmp", renderer );

 	textures->j1 = charger_image_transparente("ressources/character1.bmp", renderer,255,0,255);

 	textures->j2 = charger_image_transparente("ressources/character2.bmp", renderer,255,0,255);

}

void liberer_textures(ressources * textures){
	liberer_texture(textures->fond);
	liberer_texture(textures->j1);
	liberer_texture(textures->j2);
}

void liberer_texture(SDL_Texture * texture){
	if (texture != NULL){
		SDL_DestroyTexture(texture);
	}
}


void affiche_joueur(SDL_Renderer* renderer,SDL_Texture * perso,persos_s donnees_perso,int i){

	int persoW;
	int persoH;

	//On demande la largeur et hauteur de l'image
	SDL_QueryTexture(perso, NULL, NULL, &persoW,&persoH);

	SDL_Rect SrcR = {0,0,persoW,persoH};

	SDL_Rect DestR = {105*donnees_perso.coord_x + i*55,119*donnees_perso.coord_y,persoW,persoH};

	SDL_RenderCopy(renderer,perso, &SrcR, &DestR);
}

void affiche_salle(SDL_Renderer* renderer, SDL_Texture * image_salle, salle_t salle){

	int salleW;
	int salleH;

	//On demande la largeur et hauteur de l'image
	SDL_QueryTexture(image_salle, NULL, NULL, &salleW, &salleH);

	SDL_Rect SrcR = {0, 0, salleW, salleH};

	SDL_Rect DestR = {salle.x*salleW, salle.y*salleH, salleW, salleH};

	SDL_RenderCopy(renderer, image_salle, &SrcR, &DestR);
}
