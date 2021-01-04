#ifndef MONDE_H
#define MONDE_H

/**
  * \file data_monde.h
  * \author Trunkenwald Marie
  * \brief Rassemble les éléments du jeu
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "fonctions_SDL.h"
#include "actions.h"
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
    int active_direction_salle ;
    int move;
    int affiche_message; /*!< Indique si on doit afficher un message à l'écran */
    char type_de_jeu;  /*!< Indique le type de jeu que le joueur choisit (s pour solo et m pour multijoueur)*/
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
data_t * init_data();

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
    * \brief Vérifie si la partie est terminée
    * \param terminer Indique la fin du jeu
    * \param joueurs Ensemble des joueurs
    * \param plateau Ensemble des salles
    * \param type_de_jeu Type de jeu (solo ou multi)
    * \param nb_personnage Nombre de personnages total
*/

void verifie_fin_du_jeu(int* terminer,persos_t* joueurs,salle_t** plateau,char type_de_jeu,int nb_personnage);

data_t* gestion_plateau(int num_plateau);

void mode_de_jeu(int choix,SDL_Rect rectPlateau, char* mode);

void affichage_menu(int* jouer, SDL_Event* evenements,SDL_Renderer* ecran,ressources textures,data_t** data);

void appliquer_texte_menu(int numero_menu,SDL_Renderer* ecran,SDL_Rect** rectMessages,ressources textures);

void choix_du_menu(int choix,int* rester_dans_menu, int* numero_menu);

SDL_Rect* recherche_rect_messages(int numero_menu, int* nb_choix,SDL_Rect** rectMessages);
/**
    * \brief Actualise le menu à partir du choix du joueur
    * \param x_souris Abscisse de la souris
    * \param y_souris Ordonnée de la souris
    * \param rester_dans_menu Indique si le joueur reste dans le menu
    * \param data Les données du jeu
    * \param jouer Indique si le joueur veut lancer une partie
    * \param rectMessages Ensemble des choix possibles dans le menu pous le joueur
    * \param actions Le sprite des actions
*/
void trouve_selection_menu(int x_souris,int y_souris, int* rester_dans_menu,int* numero_menu,data_t** data,int * jouer, SDL_Rect** rectMessages,SDL_Texture* actions);

#endif
