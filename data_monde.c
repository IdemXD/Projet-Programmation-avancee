#include <stdlib.h>

/*
    *\file data_monde.c
    *\author TRUNKENWALD Marie
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "data_monde.h"

data_t* init_data()
{
	// Allocation de la structure
	data_t* data = (data_t *) malloc (sizeof(data_t));

    // Demande du niveau au joueur puis chargement du niveau correspondant
	data->salles = charger_plateau(preparation_chemin());
    data->nb_personnages = 2;
    //Les deux variables précédentes seront à changer à partir du menu

    // Preparation des variables d'interactions personnages / actions
	data->etape = 1; //etape 1 : choix de l'action
	data->active_direction = 'n'; // définit quel direction le joueur choisit
    data->trouve = data->terminer = data->nb_action = 0;
	data->tour_perso = data->tour_action = 0;

    // Initialisation des structures d'interactions personnages / actions
    data->joueur = creer_persos(data->nb_personnages);
	data->actions = creer_actions();
	data->actions[3].etat = 0;

	 return data;

}

void refresh_game(SDL_Renderer *ecran, ressources textures, data_t* data)
{
    SDL_RenderClear(ecran);
    SDL_RenderCopy(ecran, textures.fond, NULL, NULL);

    affichage_plateau(ecran,textures,data->salles);
    
    
    if (data->etape == 2 && data->joueur[data->tour_perso].actions[data->tour_action] == 0 && plateau_est_visible(data->salles)){
    //On affiche un message lorsque le joueur a choisi regarder mais le plateau est visible en entier
        
        SDL_Delay(1000);
        data->affiche_message = 0;
        change_action(data->actions,&(data->tour_action),&(data->tour_perso),&(data->etape),&(data->affiche_message),data->nb_personnages,data->joueur);        
    }

    affiche_tours(ecran,textures.police,data->tour_perso,data->tour_action);

    for (int i = 0; i<2; i++){
    	if (data->joueur[i].state)
    		affiche_joueur(ecran,textures.sprites_elements,data->joueur[i],i);
    }

    

    for (int i = 0; i<NB_ACTIONS_TOTAl; i++){
        if (data->actions[i].etat) { //On affiche seulement si la salle est visible
            affiche_action(ecran, textures.sprites_elements, data->actions[i], i);
        }
    }

    affiche_tours(ecran,textures.police,data->tour_perso,data->tour_action);
    
}


void clean_game(SDL_Window *fenetre, SDL_Renderer *ecran, ressources *textures, data_t* data)
{
	//Libération de l’écran (renderer)
	free_plateau(data->salles);
	
	free(data->actions);
	liberer_persos(data->joueur,data->nb_personnages);
	free(data);
	liberer_textures(textures);
	TTF_Quit();
	
	SDL_DestroyRenderer(ecran);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
}
