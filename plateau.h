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
struct_t** creer_plateau();

/**
  * \brief Libère l'espace alloué au tableau
*/
void free_plateau(struct_t** pl);

#endif
