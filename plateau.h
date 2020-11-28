/**
  * \file plateau.c
  * \author Trunkenwald Marie
  * \brief Création d'un tableau pl à deux dimensions de structures
*/

#ifndef PLATEAU_H
#define PLATEAU_H

#include "constantes.h"
#include "actions.h"
#include "plateau.h"
#include "salle.h"
#include "personnages.h"

/**
  * \brief Parcours d'un tableau d'elements
  * \param element que l'on cherche
  * \param tab Tableau que l'on parcourt
  * \param tab_length longueur du tableau
  * \return 1 si l'element est dans le tableau, 0 sinon
*/
int is_in(char element,const char* tab, int tab_length);

/**
  * \brief Creation et allocation d'un tableau de structures 2D
  * \return Pointeur du tableau créé
*/
salle_t** creer_plateau();

/**
  * \brief Creation et remplissage d'un plateau en tableau 2D
  * \return Pointeur du tableau créé
*/
salle_t** charger_plateau();

/**
  * \brief Affichage du tableau résultant de la création du plateau
  * \param pl Tableau 2D representant le plateau
*/
void affichage_plateau_brut(salle_t** pl);

/**
    * \brief Sauvegarde le plateau dans un fichier
    * \param pl Tableau 2D representant le plateau
*/
void sauvegarder_plateau(salle_t** pl);

/**
  * \brief Libère l'espace alloué au tableau
  * \param pl Tableau 2D representant le plateau
*/
void free_plateau(salle_t** pl);

#endif
