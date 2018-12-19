#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "images.h"
#include "entree_sortie.h"

#define SEUIL1_PIXEL(valeur, seuil) ((valeur) < (seuil) ? 0:255)	// macro sous forme de fonction
#define SEUIL2_PIXEL(valeur, seuil) if ((valeur) < (seuil)) (valeur) = 0 ; else (valeur) = 255 // macro sous forme de procédure

#if (DEBUG)
#define AFFICHER_FONCTION	printf("**********%s**********\n", __func__) // macro qui affiche le nom de la fonction courante
#else
#define AFFICHER_FONCTION		// macro vide ==> n'affiche rien
#endif

//---------------------------------------------------------------------------
void AfficherImage(char* nomFichier)
//---------------------------------------------------------------------------
{
	char commande[128] ;
	AFFICHER_FONCTION ;
//	sprintf(commande,"xv %s", nomFichier) ;
	sprintf(commande,"gwenview %s", nomFichier) ;	// sur ma machine virtuelle, je n'ai pas xv
	system(commande) ;
	printf("Affichage %s\n", nomFichier) ;
}

//---------------------------------------------------------------------------
void LibererImage(t_image* image)
//---------------------------------------------------------------------------
{
	AFFICHER_FONCTION ;
	if (image)
	{
		free(image->pixels) ;
		free(image) ;
	}
}

//---------------------------------------------------------------------------
void Degrade(t_image* image)
//---------------------------------------------------------------------------
{
	int x, y ;
	int debutLigne ;
	AFFICHER_FONCTION ;

	for (y=0 ; y<image->hauteur; y++)
	{
		debutLigne = y * image->largeur ;	// petite optimisation
		for (x=0 ; x<image->largeur; x++)
			image->pixels[debutLigne +x] = x*256/image->largeur ; // on adapte le dégradé à la largeur
	}
}

//---------------------------------------------------------------------------
void Negatif(t_image* image)
//---------------------------------------------------------------------------
{
	long int i ;
	long int taille = image->largeur * image->hauteur ;
	AFFICHER_FONCTION ;

	for (i=0; i<taille; i++)
		*(image->pixels+i) = 255 - *(image->pixels+i) ; // un peu de notation pointeur
}

//---------------------------------------------------------------------------
void Seuillage(t_image* image, unsigned char seuil)
//---------------------------------------------------------------------------
{
	long int i ;
	long int taille = image->largeur * image->hauteur ;
	AFFICHER_FONCTION ;
	for (i=0; i<taille; i++)
		//*(image->pixels+i) = SEUIL1_PIXEL(*(image->pixels+i), seuil) ;	// macro "fonction"
		SEUIL2_PIXEL(*(image->pixels+i), seuil) ;	// macro procédure
}

//------------------------------------------------------------------------
void Mirroir(t_image* image, char type) 
//------------------------------------------------------------------------
{
	unsigned char pixelTemporaire ;
	long int iSource, iDest ;

	AFFICHER_FONCTION ;
	if (type == MIRROIR_HORIZONTAL)
	{
		for (int y=0; y<=image->hauteur/2; y++)
			for (int x=0; x<image->largeur; x++)
			{
				iSource = y*image->largeur+x ;
				iDest = (image->hauteur-y-1)*image->largeur+x ;
				pixelTemporaire = image->pixels[iSource] ;
				image->pixels[iSource] = image->pixels[iDest] ;
				image->pixels[iDest] = pixelTemporaire ;
			}
	}
	else
	{
		for (int y=0; y<image->hauteur; y++)
			for (int x=0; x<=image->largeur/2; x++)
			{
				iSource = y*image->largeur+x ;
				iDest = y*image->largeur+(image->largeur-x-1) ;
				pixelTemporaire = image->pixels[iSource] ;
				image->pixels[iSource] = image->pixels[iDest] ;
				image->pixels[iDest] = pixelTemporaire ;
			}
	}
}

//------------------------------------------------------------------------
t_image* Rotation(t_image* image, int angle) 
//------------------------------------------------------------------------
{
	long int iSource, iDest ;
	t_image* image2 = CreerImage(image->largeur, image->hauteur) ;
	if (!image2)
		return NULL ;
	AFFICHER_FONCTION ;

	if (angle == ROTATION_90) // 90° clockwise
	{
		for (int y=0; y<image->hauteur; y++)
			for (int x=0; x<image->largeur; x++)
			{
				iSource = y*image->largeur+x ;
				iDest = x*image->hauteur+(image->hauteur-y-1) ;
				image2->pixels[iDest] = image->pixels[iSource] ;
			}
		image2->largeur = image->hauteur ;		// inversion largeur et hauteur
		image2->hauteur = image->largeur ;
	}
	else if (angle == ROTATION_180)
	{
		for (int y=0; y<image->hauteur; y++)
			for (int x=0; x<image->largeur; x++)
			{
				iSource = y*image->largeur+x ;
				iDest = (image->hauteur-y-1)*image->largeur+(image->largeur-x-1) ;
				image2->pixels[iDest] = image->pixels[iSource] ;
			}
	}
	return image2 ; 
}

//------------------------------------------------------------------------
int* Histogramme(t_image* image)
//------------------------------------------------------------------------
{
	long int taille = image->largeur * image->hauteur ;
	long int i ;
	int *histo = malloc(256*sizeof(int)) ;	// calloc serait mieux car initialise la mémoire à zéro mais on ne l'a pas vu en cours
	if (!histo)								// on peut en parler en TP
		return NULL ;

	AFFICHER_FONCTION ;
	for (i=0; i<256; i++)
		*(histo+i) = 0 ;

	for (i=0; i<taille; i++)
		histo[*(image->pixels+i)]++ ; 

	return histo ;
}

//------------------------------------------------------------------------
t_image* HistogrammeImage(int* histo, int hauteur)
//------------------------------------------------------------------------
{
	long int taille = 256 * hauteur ;
	long int i ;
	int col, ligne ;
	int maxBin = 0 ;
	int hauteurBinNormalise ;
	t_image* image = CreerImage(256, hauteur) ;

	AFFICHER_FONCTION ;
	for (col=0; col<256; col++)
	{
		if (histo[col] > maxBin)	// on cherche le bin ayant la fréquence d'apparition la plus grande
			maxBin = histo[col] ;
	}

	for (i=0; i<taille; i++)		// remplit l'image d'histogramme en blanc
		image->pixels[i] = 255 ;

	for (col=0; col<256; col++)
	{
		hauteurBinNormalise = histo[col]*hauteur/(float)maxBin + 0.5 ; // +0.5 fait un arrondi
		for (ligne=hauteur - hauteurBinNormalise; ligne<hauteur; ligne++)	 
			image->pixels[ligne*256+col] = 0 ;
	}

	return image ;
}