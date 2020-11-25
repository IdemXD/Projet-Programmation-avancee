#ifndef ACTIONS_H
#define ACTIONS_H

/**
	*\file actions.h
	*\author Chloe Mathias
	*\version 1.1
*/


#include "personnages.h"
#include "salle.h"

struct action_s {
	int x_pix;
	int y_pix;
	int hauteur_pix;
	int largeur_pix;
	int etat;
};

typedef struct action_s action_t;


action_t * creer_actions();

void init_action(action_t* action,int numA);

void affiche_donnees_action(action_t action);

int clic_action(action_t* action, int x_souris,int y_souris);

/**
 * \brief Permet au personnage de se déplacer sur une des salles adjacentes
 * \param plateau le tableau des salles
 * \param perso le personnage se trouvant dans la salle
 * \param direction direction vers laquelle déplacer le personnage
 * \param choix_dir 1 si le joueur peut choisir une direction, 0 sinon
*/
void deplacer(salle_t** plateau,persos_t* perso,char* direction);


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
*/
void controler(salle_t** plateau, char* direction, int nbRangee,persos_t* p);
#endif