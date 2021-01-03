#include <stdlib.h>

/*
    *\file data_monde.c
    *\author TRUNKENWALD Marie
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "data_monde.h"

data_t * init_data()
{
	// Allocation de la structure
	data_t* data = (data_t *) malloc (sizeof(data_t));

    // Preparation des variables d'interactions personnages / actions
	data->etape = 1; //etape 1 : choix de l'action
	data->active_direction = 'n'; // définit quel direction le joueur choisit
    data->active_direction_salle = 0;
    data->trouve = 0;
    data->terminer = 0;
    data->nb_action = 0;
	data->tour_perso = data->tour_action = 0;
	//data->affiche_message = 1;
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
	if (data != NULL){
		free_plateau(data->salles);
		free(data->actions);
		liberer_persos(data->joueur,data->nb_personnages);
		free(data);
	}
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
    int abs,ord;
    lettreToCoords('R',&abs,&ord,plateau);//On recherche les coordonnées de la salle 25
    int i = 0,fini = 1;
    while(i < nb_personnage && fini){
        if (joueurs[i].coord_x != abs || joueurs[i].coord_y != ord)
            fini = 0;
        i++;
    }
    if (fini){
        *terminer = 2; //On sort de la boucle de jeu
    }

}

data_t* gestion_plateau(int num_plateau){
    data_t* data = init_data();
    char * nom_du_fichier = nom_du_plateau(num_plateau);
    data->salles = charger_plateau(nom_du_fichier);
    free(nom_du_fichier);
    return data;
}

void affichage_menu(int* jouer, SDL_Event* evenements,SDL_Renderer* ecran,ressources textures,data_t** data){
    int rester_dans_menu = 0;
    int numero_menu = 1;
    SDL_Rect Jouer={330,245,255,40};
    SDL_Rect Quitter={330,445,295,40};
    SDL_Rect rectMessage[2]={Jouer,Quitter};
    SDL_Rect Plateau_1={40,145,255,40};
    SDL_Rect Plateau_2={340,145,255,40};
    SDL_Rect Plateau_3={640,145,255,40};
    SDL_Rect Plateau_4={40,345,255,40};
    SDL_Rect Plateau_5={340,345,255,40};
    SDL_Rect Plateau_6={640,345,255,40};
	SDL_Rect rectPlateau[6]={Plateau_1,Plateau_2,Plateau_3,Plateau_4,Plateau_5,Plateau_6};
    SDL_Rect Player_1={230,245,255,40};
    SDL_Rect Player_2={230,445,255,40};
    SDL_Rect Player_3={530,245,255,40};
    SDL_Rect Player_4={530,445,255,40};
    SDL_Rect rectPlayer[4] = {Player_1,Player_2,Player_3,Player_4};
    SDL_Rect* rectTout[3] = {rectMessage,rectPlateau,rectPlayer};
    while (!rester_dans_menu){
        SDL_RenderClear(ecran);
        SDL_RenderCopy(ecran, textures.sprites_menu, NULL, NULL);
        appliquer_texte(ecran,325, 45, 295, 50, "Freedom", textures.police);
        appliquer_texte_menu(numero_menu,ecran,rectTout,textures);
	    while(SDL_PollEvent( evenements ))
            switch(evenements->type)
            {
                case SDL_QUIT:
                    rester_dans_menu = 1;
                    break;
                case SDL_KEYDOWN:
                    switch(evenements->key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            rester_dans_menu = 1;
                            break;
                    }
                	break;
                case SDL_MOUSEBUTTONDOWN:
                	trouve_selection_menu(evenements->button.x, evenements->button.y,&rester_dans_menu,&numero_menu,data,jouer,rectTout,textures.sprites_elements);
                   	break;
            }
        SDL_RenderPresent(ecran);
    }
}

void appliquer_texte_menu(int numero_menu,SDL_Renderer* ecran,SDL_Rect** rectMessages,ressources textures){

	if (numero_menu == 1){
        appliquer_texte(ecran,rectMessages[numero_menu-1][0].x, rectMessages[numero_menu-1][0].y,rectMessages[numero_menu-1][0].w,rectMessages[numero_menu-1][0].h, "Jouer", textures.police);
        appliquer_texte(ecran,rectMessages[numero_menu-1][1].x, rectMessages[numero_menu-1][1].y, rectMessages[numero_menu-1][1].w, rectMessages[numero_menu-1][1].h, "Quitter", textures.police);
    }
    if(numero_menu==2){

        appliquer_texte(ecran,rectMessages[numero_menu-1][0].x, rectMessages[numero_menu-1][0].y, rectMessages[numero_menu-1][0].w, rectMessages[numero_menu-1][0].h, "Plateau 1", textures.police);
        appliquer_texte(ecran,rectMessages[numero_menu-1][1].x, rectMessages[numero_menu-1][1].y, rectMessages[numero_menu-1][1].w, rectMessages[numero_menu-1][1].h, "Plateau 2", textures.police);
        appliquer_texte(ecran,rectMessages[numero_menu-1][2].x, rectMessages[numero_menu-1][2].y, rectMessages[numero_menu-1][2].w, rectMessages[numero_menu-1][2].h, "Plateau 3", textures.police);
        appliquer_texte(ecran,rectMessages[numero_menu-1][3].x, rectMessages[numero_menu-1][3].y, rectMessages[numero_menu-1][3].w, rectMessages[numero_menu-1][3].h, "Plateau 4", textures.police);
        appliquer_texte(ecran,rectMessages[numero_menu-1][4].x, rectMessages[numero_menu-1][4].y, rectMessages[numero_menu-1][4].w, rectMessages[numero_menu-1][4].h, "Plateau 5", textures.police);
		if(existence_sauvegarde()){
			appliquer_texte(ecran,rectMessages[numero_menu-1][5].x, rectMessages[numero_menu-1][5].y, rectMessages[numero_menu-1][5].w, rectMessages[numero_menu-1][5].h, "Plateau 6", textures.police);
		}
    }
    if(numero_menu==3){
        appliquer_texte(ecran,325, 145, 295, 50, "Mode de jeu", textures.police);
        appliquer_texte(ecran,rectMessages[numero_menu-1][0].x, rectMessages[numero_menu-1][0].y, rectMessages[numero_menu-1][0].w, rectMessages[numero_menu-1][0].h, "1 Joueur", textures.police);
        appliquer_texte(ecran,rectMessages[numero_menu-1][1].x, rectMessages[numero_menu-1][1].y, rectMessages[numero_menu-1][1].w, rectMessages[numero_menu-1][1].h, "2 Joueurs", textures.police);
        appliquer_texte(ecran,rectMessages[numero_menu-1][2].x, rectMessages[numero_menu-1][2].y, rectMessages[numero_menu-1][2].w, rectMessages[numero_menu-1][2].h,"3 Joueurs", textures.police);
        appliquer_texte(ecran,rectMessages[numero_menu-1][3].x, rectMessages[numero_menu-1][3].y, rectMessages[numero_menu-1][3].w, rectMessages[numero_menu-1][3].h, "4 Joueurs", textures.police);
    }
}

void choix_du_menu(int choix,int* rester_dans_menu,SDL_Rect message, int* numero_menu){
    if(choix){
    	*rester_dans_menu = 0;
    } else {
    	*numero_menu = *numero_menu + 1;
    }
}

SDL_Rect* recherche_rect_messages(int numero_menu, int* nb_choix,SDL_Rect** rectMessages){
	if (numero_menu == 1){
		*nb_choix = 2;
	}
	if (numero_menu == 2){
		*nb_choix = 6;
	}
	if (numero_menu == 3){
		*nb_choix = 4;
	}
	return rectMessages[numero_menu-1];
}

void trouve_selection_menu(int x_souris,int y_souris, int* rester_dans_menu,int* numero_menu,data_t** data,int * jouer, SDL_Rect** rectMessages,SDL_Texture* actions){
	int trouve = 0, choix = 0, nb_choix;
	SDL_Rect* rect = recherche_rect_messages(*numero_menu,&nb_choix,rectMessages);
	while (!trouve && choix<nb_choix){
		if (clic_menu(rect[choix],x_souris, y_souris)){
			if (*numero_menu == 3){
				if (!choix){
                	(*data)->type_de_jeu = 's';
                } else {
                	(*data)->type_de_jeu = 'm';
                }
                (*data)->nb_personnages = joueurToPersos(choix+1);

				(*data)->joueur = creer_persos((*data)->nb_personnages);
				(*data)->actions = creer_actions((*data)->type_de_jeu);
                modif_taille(actions, (*data)->actions);
                *jouer = 1;//On sort du menu et on peut jouer
        		*rester_dans_menu = 1;
			}
			if (*numero_menu == 2){
				*data = gestion_plateau(choix + 1);
                *numero_menu = *numero_menu + 1;
			}
			if (*numero_menu == 1){
				choix_du_menu(choix, rester_dans_menu, rect[choix], numero_menu);
			}
			trouve++;

		} else {
			choix++;
		}
	}
}
