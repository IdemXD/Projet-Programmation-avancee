/**
  * \file plateau.c
  * \author Trunkenwald Marie
  * \brief Création d'un tableau pl à deux dimensions de structures
*/

#ifndef PLATEAU_H
#define PLATEAU_H

#include "constantes.h"
#include "fonctions_SDL.h"
#include "salle.h"
#include "personnages.h"


/**
  * \brief Parcours d'un tableau d'elements
  * \return 1 si l'element est dans le tableau, 0 sinon
*/
int is_in(int element, int* tab, int tab_length);

/**
  * \brief Création du tableau de structures 2D
  * \return Pointeur du tableau créé
*/
salle_t** creer_plateau();

/**
  * \brief Affichage du tableau résultant de la création du plateau
  * \param pl Tableau 2D representant le plateau
*/
void affichage_plateau_brut(salle_t** pl);

/**
    * \brief Affiche le plateau sur l'ecran de jeu
    * \param renderer Surface de l'écran de joueur
    * \param texture_salles Ensemble des images correspondants aux salles
    * \param pl Tableau 2D representant le plateau
*/
void affichage_plateau(SDL_Renderer* renderer, ressources texture_salles, salle_t** pl);

/**
  * \brief Libère l'espace alloué au tableau
  * \param pl Tableau 2D representant le plateau
*/
void free_plateau(salle_t** pl);

#endif
