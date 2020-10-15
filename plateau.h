/**
  * \file plateau.c
  * \author Trunkenwald Marie
  * \brief Création d'un tableau pl à deux dimensions de structures
*/

#ifndef PLATEAU_H
#define PLATEAU_H

#include "salle.h"

/**
  * \brief Création du tableau de structures 2D
  * \return Pointeur du tableau créé
*/
salle_t** creer_plateau();

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
