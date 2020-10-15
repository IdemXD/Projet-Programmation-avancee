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

	SDL_Texture * s_depart;
	SDL_Texture * s_25;
	SDL_Texture * s_vide;
	SDL_Texture * s_vision;
	SDL_Texture * s_mortelle;
	SDL_Texture * s_vortex;
	SDL_Texture * s_tunnel;
	SDL_Texture * s_chute;
	SDL_Texture * s_froide;
	SDL_Texture * s_mobile;
	SDL_Texture * s_controle;
	SDL_Texture * s_noire;
	SDL_Texture * s_cache;
	}

};

typedef struct textures_s ressources;

void init_textures(ressources * textures, SDL_Renderer* renderer);

void liberer_textures(ressources * textures);

void liberer_texture(SDL_Texture * texture);

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer);

SDL_Texture * charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b) ;

SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color) ;

void affiche_joueur(SDL_Renderer* renderer,SDL_Texture * perso,persos_s donnees_perso,int i);

/**
	* \brief Affiche l'image correspondante à une salle
	* \param renderer Surface de l'écran de joueur
	* \param image_salle Texture de l'image que l'on veut afficher
	* \param salle Salle que l'on veut afficher
*/
void affiche_salle(SDL_Renderer* renderer, SDL_Texture image_salle, salle_t salle);
