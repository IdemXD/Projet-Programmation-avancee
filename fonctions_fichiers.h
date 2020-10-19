#ifndef FONCTIONS_FICHIERS_H
#define FONCTIONS_FICHIERS_H



char** allouer_tab_2D(int n, int m);

void desallouer_tab_2D(char** tab, int n);

void afficher_tab_2D(char** tab, int n, int m);

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);

char** lire_fichier(const char* nomFichier);







#endif