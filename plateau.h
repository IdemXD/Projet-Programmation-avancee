/**
  * \file plateau.c
  * \author Trunkenwald Marie
  * \brief Création du plateau de jeu
*/

#ifndef PLATEAU_H
#define PLATEAU_H

#include "salle.h"
#include "constantes.h"

/**
  * \brief Parcours d'un tableau d'elements
  * \param element que l'on cherche
  * \param tab Tableau que l'on parcourt
  * \param tab_length longueur du tableau
  * \return 1 si l'element est dans le tableau, 0 sinon
*/
int is_in(char element,const char* tab, int tab_length);

/**
  *\brief Initialise les caractéristique des salles
  *\param plateau fichier de lecture du plateau
  *\param pl plateau considéré
  *\param n indice du parcours du fichier niveau
  *\param curseur permet d'affecter la lettre correspondante à la salle
*/
void init_salles(char salle[5], salle_t** pl, int n);

/**
    * \brief Demande au joueur le niveau voulu
    * \return nom du niveau choisi par le joueur
*/
char* preparation_chemin();

/**
    * \brief Demande au joueur le niveau voulu
    * \param plateau Numéro du plateau dans le menu
    * \return nom du niveau choisi par le joueur
*/

char * nom_du_plateau(int plateau);
/**
  * \brief Verifie qu'un paquet de caractère d'une salle est valide
  * \param paquet char sensé contenir lettre, boolean, boolean, boolean
  * \return 1 si le paquet de char est valide, 0 sinon
*/
int chars_valide(char paquet[5]);

/**
  * \brief Verifie que le plateau respecte les configurations de départ
  * \param pl Plateau chargés
  * \return 1 si le plateau ne respecte pas le format de départ
*/
int verif_emplacements(salle_t** pl);

/**
  * \brief Creation et allocation d'un tableau de structures 2D
  * \return Pointeur du tableau créé
*/
salle_t** creer_plateau();

/**
  * \brief Creation et remplissage d'un plateau en tableau 2D
  * \param niveau le nom du niveau à charger
  * \return Tableau 2D representant le plateau
*/
salle_t** charger_plateau(char* niveau);

/**
    * \brief Demande au joueur s'il veut sauvegarder, si oui on le fait
    * \param pl le plateau actuel que l'on veut sauvegarder
*/
void proposition_sauvegarde(salle_t** pl);

/**
    * \brief Sauvegarde le plateau dans un fichier
    * \param pl Tableau 2D representant le plateau
*/
void sauvegarder_plateau(salle_t** pl);

/**
    * \brief Verifie que le fichier de sauvegarde existe
    * \return 1 si une sauvegarde existe, 0 sinon
*/
int existence_sauvegarde();

/**
  * \brief Libère l'espace alloué au tableau
  * \param pl Tableau 2D representant le plateau
*/
void free_plateau(salle_t** pl);

/**
  * \brief Affichage des lettres du plateau telles qu'elle sont dans le niveau
  * \param pl Tableau 2D representant le plateau
*/
void affichage_plateau_lettre(salle_t** pl);

/**
  * \brief Affichage des coordonnées de chaque salles
  * \param pl Tableau 2D representant le plateau
*/
void affichage_plateau_coordonnees(salle_t** pl);

/**
  * \brief Affichage des caractérisique de chaque salle (vis, etat, pres)
  * \param pl Tableau 2D representant le plateau
*/
void affichage_plateau_caracteristique(salle_t** pl);

/**
  * \brief Renvoie un int égal à 1 si le plateau est entièrement visible, 0 sinon
  * \param pl Tableau 2D representant le plateau
  * \return 1 si le plateau est entièrement visible, 0 sinon
*/
int plateau_est_visible(salle_t** pl);

/**
  * \brief Renvoie les coordonnées d'une salle dont on donne le type
  * \param lettre Type de la salle
  * \param abs Abscisse de la salle
  * \param ord Ordonnée de la salle
  * \param pl Tableau 2D representant le plateau
*/

void lettreToCoords(char lettre,int* abs,int* ord, salle_t** pl);

#endif
