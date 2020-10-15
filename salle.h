#ifndef SALLE_H
#define SALLE_H

/**
	*\file salle.h
	*\author Boudhane Medi
	*\version 1.0
*/

#include "plateau.h"

struct salle_s
{
    int x;      /*!< Tableau contenant la coordonnée x de la salle */
    int y;      /*!< Tableau contenant la coordonnée y de la salle */
    int state;   /*!< Etat de la salle(1 si la salle est utilisable )*/
    int visible;    /*!< Etat de la salle (1 si la salle est visible)*/
    char type;      /*!< Char représentant la salle*/
};
typedef struct salle_s salle_t;




void Salle_mortelle(salle_t** , persos_s* player);



void Salle_vide(salle_t** , persos_s* player,salle_t* salle);



void Salle_chute();





void Salle_vision(salle_t** , persos_s* perso, salle_t* salle);



void Salle_controle();



void Salle_vortex(salle_t** pl, persos_s* perso, salle_t* salle);

void Salle_tunnel();

void Salle_25();

void Salle_froide();

void  Salle_mobile();

void Salle_depart();

#endif


