#ifndef MONDE_H
#define MONDE_H

/**
  * \file data_monde.h
  * \author Trunkenwald Marie
  * \brief Rassemble les éléments du jeu
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "actions.h"
#include "fonctions_SDL.h"
#include "personnages.h"
#include "plateau.h"

struct data_s {

    int nb_personnages; /*!< Nombre de personnages (2 pour 1 joueur sinon le nombre de joueurs est égal au nombre de personnages) */
    int terminer;           /*!< Indique que la partie est terminée */
    int etape;              /*!< Indique à quel étape du jeu on se trouve */
    int trouve;             /*!< Indique qu'on a trouvé la salle 25 */
    int tour_perso;         /*!< Indique à quel joueur c'est le tour */
    int tour_action;        /*!< Indique ordre d'execution des actions  */
    int nb_action;          /*!< Donne le nb d'action accordé au joueur */
    char active_direction;  /*!< Définit quel direction le joueur choisit */
    int affiche_message; /*!< Indique si on doit afficher un message à l'écran */

    salle_t** salles;       /*!< Represente le plateau de jeu */
    persos_t* joueur;        /*!< Represente les joueurs */
    action_t* actions;      /*!< Organise les actions des joueurs */
};

/**
    * \brief Type qui correspond aux données du jeu
*/

typedef struct data_s data_t;

/**
    * \brief Initialisation des données du jeu
    * \param data les éléments du joueur
*/
data_t* init_data();

/**
    * \brief Rafraichis l'affichage du jeu
    * \param ecran l'ecran
    * \param textures les textures
    * \param data les elements
*/
void refresh_game(SDL_Renderer *ecran, ressources textures, data_t* data);

/**
    * \brief Nettoie le jeu, ses éléments et libère la mémoire
    * \param fenetre la fenêtre du jeu
    * \param ecran l'ecran
    * \param textures les textures
    * \param data les elements
*/
void clean_game(SDL_Window *fenetre, SDL_Renderer *ecran, ressources *textures, data_t* data);

/**
    * \brief Nettoie le jeu car erreur dans la création du plateau
    * \param fenetre la fenêtre du jeu
    * \param ecran l'ecran
    * \param textures les textures
    * \param data les elements
*/
//void exit_erreur_pl(SDL_Window *fenetre, SDL_Renderer *ecran, data_t* data);

#endif
