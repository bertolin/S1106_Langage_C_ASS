#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "images.h"

//---------------------------------------------------------------------------
t_image* CreerImage(int largeur, int hauteur)
//---------------------------------------------------------------------------
{
	t_image* image ;
	image = malloc(sizeof(t_image)) ;
	if (image)
	{
		image->pixels = malloc(largeur * hauteur * sizeof(char)) ; // * sizeof(char) pour prendre l'habitude
		if (!image->pixels)
		{
			free(image) ;
			image = NULL ;
		}
		else
		{
			image->largeur = largeur ;
			image->hauteur = hauteur ;
		}
	}
	return image ;
}

//---------------------------------------------------------------------------
t_image* LireImagePGM(char* nomFichier)
//---------------------------------------------------------------------------
// crée dynamiquement une structure image
// retourne la structure image remplie à partir du fichier nomFichier
// si problème, retourne NULL
{
	FILE* f ;
	char s[256] ;
	char s2[256] ;
	char* c_res ;
	int i, largeur, hauteur ;
	t_image* im ; // la structure qui sera renvoyée

// ouverture de l'image en lecture  
	f = fopen(nomFichier, "rb") ;	// b non necessaire sou Linux
	if (!f)
	{
		printf("Erreur ouverture de fichier\n") ;
		return(NULL) ;
	}
	
// lecture des 3 premières lignes et récupération dimensions de l'image	
	fscanf(f, "%s\n%d %d\n%s\n", s, &largeur, &hauteur, s2) ;
#if DEBUG
	printf("Largeur=%d ; hauteur=%d\n", largeur, hauteur) ;
#endif
 
// allocation mémoire pour les pixels de l'image
	im = CreerImage(largeur, hauteur) ;
	if (!im)
	{
		fclose(f) ;
		return(im) ;
	}

// lecture des pixels de l'image
	im->largeur = largeur ;
	im->hauteur = hauteur ;
	fread(im->pixels, im->largeur,im->hauteur, f) ;
	
// fermeture fichier	
	fclose(f) ;
	return (im) ;
}

//---------------------------------------------------------------------------
int EcrireImagePGM(char* nomFichier, t_image im) 
//---------------------------------------------------------------------------
// crée (ou écrase) un fichier image avec les informations de la structure
{
	FILE* f ;

// ouverture de l'image à creer en écriture binaire	
	f = fopen(nomFichier, "wb") ;	// b non necessaire sou Linux
	if (!f)
	{
		printf("Erreur ouverture de fichier en écriture\n") ;
		return ERREUR ;
	}
	
//  écriture de l'entete de l'image à creer
	fprintf(f, "P5\n") ;
	fprintf(f, "%d %d\n", im.largeur, im.hauteur) ;
	fprintf(f, "255\n") ;

	fwrite(im.pixels, im.largeur, im.hauteur, f) ;
	fclose(f) ;

	return OK ;
}	

