#include <stdlib.h>

/*
    *\file data_monde.c
    *\author TRUNKENWALD Marie
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "data_monde.h"

void init_data(data_t* data)
{
    // Demande du niveau au joueur puis chargement du niveau correspondant
	data->salles = charger_plateau(preparation_chemin());

    // Preparation des variables d'interactions personnages / actions
	data->etape = 1; //etape 1 : choix de l'action
	data->active_direction = 'n'; // définit quel direction le joueur choisit
    data->trouve = data->terminer = data->nb_action = 0;
	data->tour_perso = data->tour_action = 0;

    // Initialisation des structures d'interactions personnages / actions
    data->joueur = creer_persos();
	data->actions = creer_actions();
	data->actions[3].etat = 0;

}

void refresh_game(SDL_Renderer *ecran, ressources textures, data_t* data)
{
    SDL_RenderClear(ecran);
    SDL_RenderCopy(ecran, textures.fond, NULL, NULL);


    affichage_plateau(ecran,textures,data->salles);

    affiche_joueur(ecran,textures.sprites_elements,data->joueur[0],0);
    affiche_joueur(ecran,textures.sprites_elements,data->joueur[1],1);

    affiche_action(ecran,textures.sprites_elements,data->actions[0], 0);
    affiche_action(ecran,textures.sprites_elements,data->actions[1], 1);
    affiche_action(ecran,textures.sprites_elements,data->actions[2], 2);
    affiche_action(ecran,textures.sprites_elements,data->actions[3], 3);
}


void clean_game(SDL_Window *fenetre, SDL_Renderer *ecran, ressources *textures, data_t* data)
{
    // Fermer la police et quitter SDL_ttf
	TTF_Quit();

	//Libération de l’écran (renderer)
	free_plateau(data->salles);

	//free(actions);
	liberer_textures(textures);
	liberer_persos(data->joueur);
	data->joueur = NULL; // !!! A deplacer dans la fonction liberer elle même

	SDL_DestroyRenderer(ecran);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
}
