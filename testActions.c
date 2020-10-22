/**
	*\file testActions.c
	*\author Chloe Mathias
*/

#include <stdio.h>
#include <stdlib.h>

#include "actions.h"
#include "personnages.h"
#include "plateau.h"
#include "salle.h"

int main(int argc, char* argv[]) {

	salle_t ** pl;
	persos_s* p;

	pl = creer_plateau();
	p = creer_persos();

	

	return 0;
}