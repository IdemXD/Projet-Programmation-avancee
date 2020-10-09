/**
	*\file fonctions_SDL.h
	*\author Chloe Mathias
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "personnages.h"

struct textures_s{

	SDL_Texture * fond;
	SDL_Texture * j1;
	SDL_Texture * j2;

};

typedef struct textures_s ressources;

void init_textures(ressources * textures, SDL_Renderer* renderer);

void liberer_textures(ressources * textures);

void liberer_texture(SDL_Texture * texture);

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer);

SDL_Texture * charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b) ;

SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color) ;

void affiche_joueur(SDL_Renderer* renderer,SDL_Texture * perso,persos_s donnees_perso,int i);

