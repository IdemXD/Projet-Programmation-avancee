/*
plateau.c
TRUNKENWALD Marie
*/
#include <stdio.h>

int** creer_plateau()
{
     // Creation d'un plateau à deux dimensions
     int** pl=malloc(sizeof(int*)*5);

     // Ouverture du fichier contenant une representation du plateau
     FILE* plateau = fopen("plateau1","r");

     // Curseur de lecture du fichier
     int char_curseur = 0;

     if (plateau != NULL)
     {
          do
          {
               for(int i=0; i<5; i++)
               {
                    pl[i]=malloc(sizeof(int)*5);
                    for(int j=0; j<5; j++)
                    {
                         char_curseur = fgetc(plateau); // Utilisation de fgetc avance le curseur
                         //pl[i][j] = char_curseur; // La lettre lu est rentré dans le tableau
                         salle_t->type = char_curseur; // Le charactère de la salle correspondate est affecté dans la struct
                    }
               }
          } while (char_curseur != EOF); // EOF est le character de fin de fichier
          fclose(plateau);
     }
     return pl;
}
