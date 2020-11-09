/**
	*\file fonctions_SDL.c
	*\author Chloe Mathias
*/
#include "fonctions_SDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>



SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer){

	// Chargement d' une image
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	surface = SDL_LoadBMP(nomfichier) ;
	if (surface == NULL){
		printf ("Erreur de chargement de l'image BMP : %s",SDL_GetError());
		return NULL;
	}
	// Conversion de la surface de l’image au format texture avant de l’appliquer
	texture = SDL_CreateTextureFromSurface(renderer,surface) ;
	SDL_FreeSurface(surface);

	if (texture == NULL){
		printf ("Erreur lors de la creation de la texture à partir d'une surface : %s",SDL_GetError());
		return NULL;
	}
	return texture;
}

SDL_Texture * charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b){
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;

	surface = SDL_LoadBMP(nomfichier) ;

	if (surface == NULL){
		printf ("Erreur de chargement de l'image BMP : %s\n",SDL_GetError());
		return NULL;
	}

	// Définition de la couleur transparente d'une surface
	if (0!=SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,r,g,b))){
		printf("Erreur de la transparence : %s\n",SDL_GetError());
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(renderer,surface) ;
	SDL_FreeSurface(surface);

	if (texture == NULL){
		printf ("Erreur lors de la creation de la texture à partir d'une surface : %s\n",SDL_GetError());
		return NULL;
	}
	return texture;


}

SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color)
{
	SDL_Surface * surface = NULL;
	SDL_Texture * text = NULL;

	surface = TTF_RenderText_Solid(font,message,color);

	if (surface == NULL){
		printf ("Erreur de chargement du texte : %s\n",SDL_GetError());
		return NULL;
	}
	text = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);

	if (text == NULL){
		printf ("Erreur d'affichage du texte : %s\n",SDL_GetError());
		return NULL;
	}
	return text;



}

void init_textures(ressources * textures,SDL_Renderer* renderer){


	textures->fond = charger_image("ressources/background.bmp", renderer );

 	textures->sprites = charger_image_transparente("ressources/sprites.bmp", renderer,255,0,255);

}

void liberer_textures(ressources * textures){
	liberer_texture(textures->fond);
	liberer_texture(textures->sprites);
}

void liberer_texture(SDL_Texture * texture){
	if (texture != NULL){
		SDL_DestroyTexture(texture);
	}
}


void affiche_joueur(SDL_Renderer* renderer,SDL_Texture * perso,persos_s donnees_perso,int i){

	int persoW;
	int persoH;

	//On demande la largeur et hauteur de l'image
	SDL_QueryTexture(perso, NULL, NULL, &persoW,&persoH);

	persoW = persoW/5;
	persoH = persoH/3;

	SDL_Rect SrcR = {(i+3)*120,240,persoW,persoH};
	//La généralisation se fera plus tard 
	SDL_Rect DestR = {105*donnees_perso.coord_x + i*55,119*donnees_perso.coord_y,persoW,persoH}; //105,55,119 sont des valeurs arbitraires seulement pour avoir un meilleur affichage

	SDL_RenderCopy(renderer,perso, &SrcR, &DestR);
}

int * texture_salle (salle_t salle){
	//Possibles modifications  entre affiche_salle et texture_salle


	int num_s; //numéro du sprite de la salle sur le fichier des sprites 
	if (salle.visible == 1)
    	{

        // Selon le char definissant le type de la salle, on associe la texture correspondante
    	
    	/////
    	///
        //Le switch va être enlevé lorsque le tableau de char des salles va être implanté en tant que constante
        ///
    	/////
        switch (salle.type)
        {
            
            case 'R':
            // Salle 25
                num_s = 0;
                break;
 
            case 'V':
            // Salle vision
                num_s = 1;
                break;

			case 'C':
            // Salle chute
                num_s = 2;
                break;

            case 'O':
            // Salle controle
                num_s = 3;
                break;

            case 'S':
            // Salle de départ
                num_s = 4;
                break;

            case 'E':
            // Salle vide
                num_s = 5;
                break;

            case 'F':
            // Salle froide
                num_s = 6;
                break;

            case 'M':
            // Salle mobile
                num_s = 7;
                break;

            case 'D':
            // Salle mortelle
                num_s = 8;
                break;
            case 'N':
            // Salle noire
                num_s = 9;
                break;

            case 'T':
            // Salle tunnel
                num_s = 10;
                break;

            case 'X':
            // Salle vortex
                num_s = 11;
                break;

        }

    }
    else
    {
        // La salle est cachée, on ne sait pas ce qu'il se trouve à cet endroit.
        num_s = 12;
   	}
   	int* coord = malloc(2* sizeof(int));
   	coord[0] = num_s%5;
   	coord[1] = num_s/5;
   	return coord;

}


void affiche_salle(SDL_Renderer* renderer, SDL_Texture * image_salles, salle_t salle){

	int salleW;
	int salleH;

	//On demande la largeur et hauteur de l'image
	SDL_QueryTexture(image_salles, NULL, NULL, &salleW, &salleH);

	salleW = salleW/5;
	salleH = salleH/3;

	int * coord = texture_salle(salle);
	SDL_Rect SrcR = {coord[0]*salleW, coord[1]*salleH, salleW, salleH};

	SDL_Rect DestR = {salle.x*salleW, salle.y*salleH, salleW, salleH};

	SDL_RenderCopy(renderer, image_salles, &SrcR, &DestR);
}

