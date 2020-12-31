#ifndef ACTIONS_H
#define ACTIONS_H

/**
	*\file actions.h
	*\author Chloe Mathias
	*\version 1.1
*/

#include "constantes.h"
#include "personnages.h"
#include "salle.h"

struct action_s {
	int x_pix; /*!< Abscisse en pixel de l'image de l'action */
	int y_pix; /*!< Ordonnée en pixel de l'image de l'action */
	int hauteur_pix; /*!< Hauteur en pixel de l'image de l'action */
	int largeur_pix; /*!< Largeur en pixel de l'image de l'action */
	int etat; /*!< Indique si l'action est utilisable ou non (1 si on peut utiliser l'action, 0 sinon)*/
};

typedef struct action_s action_t;

/**
 * \brief Créer les informations des actions
 * \return Données sur les actions
*/
action_t * creer_actions(char type_de_jeu);
/**
 * \brief Initialise les informations d'une action
 * \param action Action que l'on veut initialiser
 * \param numA Numéro de l'action
*/
void init_action(action_t* action,int numA);
/**
 * \brief Affiche les données d'une action sur la sortie standard
 * \param action Action dont on veut voir les données
*/
void affiche_donnees_action(action_t action);
/**
 * \brief Renvoie si une action est choisie
 * \param action Action qu'on veut vérifier
 * \param x_souris Coordonnée en abscisse de la souris
 * \param y_souris Coordonnée en ordonnée de la souris
 * \return 1 si le joueur a choisi l'action en paramètre, 0 sinon
*/
int est_choisie(action_t* action, int x_souris,int y_souris);
/**
 * \brief Renvoie si le joueur clique sur une action
 * \param action Action qu'on veut vérifier
 * \param x_nb_action Numéro de l'action sur laquelle le joueur clique (on remet à 0 si aucune n'est choisie)
 * \param trouve Indique si on trouve une action à l'endroit où le joueur clique
 * \param x Coordonnée en abscisse de la souris
 * \param y Coordonnée en ordonnée de la souris
*/
void clic_action(action_t* actions,int* nb_action,int* trouve,int x,int y);
/**
 * \brief Applique l'action choisie, parmi les actions ayant besoin d'une direction
 * \param plateau Plateau de jeu
 * \param joueurs Les personnages en jeu
 * \param active_direction Direction qu'a choisi le joueur
 * \param tour_action Numéro du tour de l'action 
 * \param tour_perso Numéro du personnage dont c'est le tour
 * \param nb_personnage Nombre de personnages choisi
*/
void applique_action(salle_t** plateau, persos_t* joueurs, char* active_direction,int tour_action,int tour_perso, int nb_personnage,int* direction_salle);

/**
 * \brief Permet au personnage de se déplacer sur une des salles adjacentes
 * \param plateau le tableau des salles
 * \param perso le personnage se trouvant dans la salle
 * \param direction direction vers laquelle déplacer le personnage
 * \param choix_dir 1 si le joueur peut choisir une direction, 0 sinon
*/
void deplacer(salle_t** plateau,persos_t* perso,const char* direction,int tour_perso,int* direction_salle);

/**
 * \brief Renvoie la lettre représentant l'action
 * \param numero Numéro de l'action
 * \param etape Etape de jeu
 * \return Lettre représentant l'action
*/

char lettre_action(int numero,int etape);
/**
 * \brief Renvoie les coordonnées d'une salle à partir des coordonnées de la souris
 * \param x_pix coordonnée de la souris en abscisse
 * \param y_pix coordonnée de la souris en ordonnée
 * \param x coordonnée de la salle choisie en abscisse
 * \param y coordonnée de la salle choisie en ordonnée
*/
void pixToSalle(int x_pix,int y_pix,int* x, int* y);
/**
 * \brief Permet au personnage de regarder dans n'importe quelle salle
 * \param plateau le tableau des salles
 * \param x l'abscisse de la salle qu'on veut regardé (l'origine étant en haut à gauche)
 * \param y l'ordonnée de la salle qu'on veut regardé (l'origine étant en haut à gauche)
*/
void regarder(salle_t** plateau,int x,int y);

/**
 * \brief Permet au personnage de déplacer sa colonne ou sa ligne d'un cran  
 * \param plateau le tableau des salles
 * \param direction direction de déplacement des salles
 * \param nbRangee numéro dde la rangée à déplacer
 * \param p les personnages
 * \param nb_personnage Nombre de personnages 
*/
void controler(salle_t** plateau, const char* direction, int nbRangee,persos_t* p,int nb_personnage);

/**
 * \brief Recherche le prochain personnage vivant, si n'en trouve pas, renvoie le dernier personnage
 * \param tour_perso Indique le tour du personnage 
 * \param nb_personnage Nombre de personnages total
 * \param joueur Informations sur un joueur
*/

void prochain_vivant(int* tour_perso,int nb_personnage,persos_t* joueur);

/**
 * \brief Changement de personnage pour l'étape 1
 * \param actions Actions possibles
 * \param joueurs Ensemble des joueurs
 * \param tour_action Numéro du tour de l'action 
 * \param tour_perso Numéro du personnage dont c'est le tour
 * \param etape Etape de jeu
 * \param affiche_message Indique si on affiche le message pour l'action à l'étape 2
 * \param nb_personnage Nombre de personnages 
 * \param type_de_jeu Type de jeu (solo ou multi)
*/

void change_perso(action_t* actions,persos_t* joueurs,int* tour_action,int* tour_perso,int* etape,int* nb_action, int* affiche_message, int nb_personnages,char type_de_jeu);

/**
 * \brief Changement d'action pour l'étape 2
 * \param actions Actions possibles
 * \param tour_action Numéro du tour de l'action 
 * \param tour_perso Numéro du personnage dont c'est le tour
 * \param etape Etape de jeu
 * \param pas_affichage Indique si on affiche le message pour l'action à l'étape 2
 * \param nb_personnage Nombre de personnages 
 * \param joueur Ensemble des joueurs
 * \param type_de_jeu Type de jeu (solo ou multi)
*/

void change_action(action_t* actions,int* tour_action,int* tour_perso,int* etape,int* pas_affichage,int nb_personnage,persos_t* joueur,char type_de_jeu);

/**
 * \brief Action pour pousser d'autres joueurs, disponible seulement en multi
 * \param joueurs Ensemble des joueurs
 * \param num_joueur Numéro du joueur faisant l'action
 * \param nb_personnage Nombre de personnages 
 * \param direction direction de déplacement des salles
 * \param plateau Plateau de jeu
 * \param tour_perso Numéro du personnage dont c'est le tour
 * \param direction_salle direction vers laquelle les personnages seront poussés
*/

void pousser(persos_t* joueurs,int num_joueur, int nb_personnages,char* direction, salle_t** plateau,int tour_perso,int* direction_salle);
#endif