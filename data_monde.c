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
    char * nom_du_fichier = preparation_chemin();
	data->salles = charger_plateau(nom_du_fichier);
    free(nom_du_fichier);
    data->type_de_jeu = 's';//Mode solo
    data->nb_personnages = 2;//A partir du mode de jeu
    //Les trois variables précédentes seront à changer à partir du menu

    // Preparation des variables d'interactions personnages / actions
	data->etape = 1; //etape 1 : choix de l'action
	data->active_direction = 'n'; // définit quel direction le joueur choisit
    data->active_direction_salle = 0;
    data->trouve = 0;
    data->terminer =0;
    data->nb_action = 0;
	data->tour_perso = data->tour_action = 0;

    // Initialisation des structures d'interactions personnages / actions
    data->joueur = creer_persos(data->nb_personnages);
	data->actions = creer_actions(data->type_de_jeu);


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
        change_action(data->actions,&(data->tour_action),&(data->tour_perso),&(data->etape),&(data->affiche_message),data->nb_personnages,data->joueur,data->type_de_jeu);
    }

    affiche_tours(ecran,textures.police,data->tour_perso,data->tour_action,lettre_action(data->joueur[data->tour_perso].actions[data->tour_action],data->etape));

    for (int i = 0; i<data->nb_personnages; i++){
    	if (data->joueur[i].state)
    		affiche_joueur(ecran,textures.sprites_elements,data->joueur[i],i);
    }

    for (int i = 0; i<NB_ACTIONS_TOTAl; i++){
        if (data->actions[i].etat) { //On affiche seulement si la salle est visible
            affiche_action(ecran, textures.sprites_elements, data->actions[i], i);
        }
    }

}


void clean_game(SDL_Window *fenetre, SDL_Renderer *ecran, ressources *textures, data_t* data)
{
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

void verifie_fin_du_jeu(int* terminer,persos_t* joueurs,salle_t** plateau,char type_de_jeu,int nb_personnage){
    if (type_de_jeu == 's' &&(!joueurs[0].state || !joueurs[1].state)){//Si le joueur joue en mode solo et qu'un des deux persos est mort
        *terminer = 1; //On sort de la boucle de jeu
    } else {
        int i = 0,est_vivant = 0;
        while(i < nb_personnage && !est_vivant){
            if (joueurs[i].state)
                est_vivant = 1;
            i++;
        }
        if (type_de_jeu == 'm' && !est_vivant){//si tous les joueurs ont perdu
            *terminer = 1; //On sort de la boucle de jeu
        }
    }
}
