/**
	*\file fonctions_SDL.h
	*\author Chloe Mathias
*/

#ifndef FONCTIONSSDL_H
#define FONCTIONSSDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "actions.h"

struct textures_s{

	SDL_Texture * fond;/*!<Texture du fond de l'écran */
	SDL_Texture * sprites_salles;/*!<Textures des salles */
	SDL_Texture * sprites_elements;/*!<Textures des éléments du jeu*/
	TTF_Font* police; /*!<TPolice de texte*/
};

typedef struct textures_s ressources;

/**
	* \brief Initialise les bibliothèques SDL utilisées
*/
void init_sdl();

/**
	* \brief Charge les textures
	* \param textures l'ensemble des textures
	* \param renderer Surface de l'écran de jeu
*/
void init_textures(ressources * textures, SDL_Renderer* renderer);

/**
	* \brief Libère l'ensemble des textures utilisées
	* \param textures l'ensemble des textures
*/
void liberer_textures(ressources * textures);


/**
	* \brief Libère une texture
	* \param texture la texture a libéré
*/
void liberer_texture(SDL_Texture * texture);

/**
	* \brief Indique à quel personnage c'est le tour de jouer et son action
	* \param renderer Surface de l'écran de jeu
	* \param font Police d'écriture du jeu
	* \param tour_perso Indique le personnage qui doit joueur
	* \param tour_action Indique le numero de l'action du joueur
*/
void affiche_tours(SDL_Renderer* renderer,TTF_Font *font, int tour_perso, int tour_action);

/**
	* \brief Crée une texture à partir d'une image
	* \param nomFichier Chemin vers l'image qu'on veut importer
	* \param renderer Surface de l'écran de jeu
	* \return la texture de l'image
*/
SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer);

/**
	* \brief Crée une texture à partir d'une image en appliquant une transparence
	* \param nomFichier Chemin vers l'image qu'on veut importer
	* \param renderer Surface de l'écran de jeu
	* \param r Valeur de rouge de la couleur de transparence (entre 0 et 255)
	* \param g Valeur de vert de la couleur de transparence (entre 0 et 255)
	* \param b Valeur de bleu de la couleur de transparence (entre 0 et 255)
	* \return la texture de l'image
*/
SDL_Texture * charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b) ;

/**
	* \brief Crée une texture à partir d'un fichier de police
	* \param message message à afficher
	* \param renderer Surface de l'écran de jeu
	* \param font Police d'écriture
	* \param couleur couleur du message affiché
	* \return la texture
*/
void affiche_message (SDL_Renderer* renderer,TTF_Font *police,const char *message);


/**
	* \brief Permet d'afficher un texte à des coordonées données
	* \param renderer Surface de l'écran de jeu
	* \param x Abscisse du coin en haut a gauche du rectangle d'affichage
	* \param y Ordonnées du coin en haut a gauche du rectangle d'affichage
	* \param w Abscisse du coin en bas a droite du rectangle d'affichage
	* \param h Ordonnées du coin en bas a droite du rectangle d'affichage
	* \param text Message que l'on souhaite afficher
	* \param font Police d'écriture
*/
void appliquer_texte(SDL_Renderer *renderer,int x, int y, int w, int h, const char *text, TTF_Font *font);

/**
	* \brief Crée une texture à partir d'un fichier de police
	* \param action
	* \param donnees_action
*/
void modif_taille(SDL_Texture * action,action_t* donnees_action);

/**

*/
void affiche_action(SDL_Renderer* renderer,SDL_Texture * actions,action_t donnees_action ,int numA);

/**
	* \brief Affiche le sprite d'un personnage
	* \param renderer Surface de l'écran de jeu
	* \param perso Sprite du personnage
	* \param donnees_perso Informations sur le personnage
	* \param donnees_perso Informations sur le personnage
	* \param i numéro du personnage
*/
void affiche_joueur(SDL_Renderer* renderer,SDL_Texture * perso,persos_t donnees_perso,int i);

/**
	* \brief Affiche l'image correspondante à une salle
	* \param renderer Surface de l'écran du joueur
	* \param image_salle Texture de l'image que l'on veut afficher
	* \param salle Salle que l'on veut afficher
*/
void affiche_salle(SDL_Renderer* renderer, SDL_Texture* image_salle, salle_t salle);

/**
	* \brief Renvoie les coordonnées du sprite d'une salle
	* \param salle Salle dont on veut le sprite
	* \return la position (les coordonnées) de la texture de la salle dans l'image de départ
*/

int * texture_salle (salle_t salle);

/**
    * \brief Affiche le plateau sur l'ecran de jeu
    * \param renderer Surface de l'écran de joueur
    * \param texture_salles Ensemble des images correspondants aux salles
    * \param pl Tableau 2D representant le plateau
*/
void affichage_plateau(SDL_Renderer* renderer, ressources texture_salles, salle_t** pl);

/**
    * \brief Affiche le plateau sur l'ecran de jeu
    * \param peut_afficher Permet de savoir si l'on peut afficher
    * \param num_action Numero de l'action à executer
    * \param ecran Surface de l'écran de joueur
	* \param font Police d'écriture
*/
void affiche_message_actions(int peut_afficher,int num_action,SDL_Renderer* ecran,TTF_Font* police);

/**
	* \brief Affiche le texte correcpondant à la salle
	* \param renderer Surface de l'écran de joueur
	* \param font Police d'écriture
	* \param salle Salle dont on veut la description
*/
void affiche_texte_salle(SDL_Renderer* renderer, TTF_Font *police, salle_t salle);
#endif
