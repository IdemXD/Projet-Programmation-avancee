/**
  * \file plateau.c
  * \author Trunkenwald Marie
  * \brief Création d'un tableau pl à deux dimensions de structures
*/



#ifndef PLATEAU_H
#define PLATEAU_H

#include "salle.h"
#include "constantes.h"

/**
  *\brief Initialise les caractéristique des salles
    *\param pl plateau considéré
  *\param n indice du parcours du fichier niveau
    *\param curseur permet d'affecter la lettre correspondante à la salle
*/
void init_salles(salle_t** pl, int n, char curseur);


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
  * \param niveau le nom du niveau à charger
  * \return Pointeur du tableau créé
*/
salle_t** charger_plateau(char* niveau);

/**
    * \brief Demande au joueur le niveau voulu
*/
char* preparation_niveau();

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

/**
  * \brief Affichage des lettres du plateau telles qu'elle sont dans le niveau
*/
void affichage_plateau_lettre(salle_t** pl);

/**
  * \brief Affichage des coordonnées de chaque salles
*/
void affichage_plateau_coordonnees(salle_t** pl);

/**
  * \brief Affichage des caractérisique de visibilité,
  * \ utilisabilité et presence de chaque salles
*/
void affichage_plateau_caracteristique(salle_t** pl); 

#endif
