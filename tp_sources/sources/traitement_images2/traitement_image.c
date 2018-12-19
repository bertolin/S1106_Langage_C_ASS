#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Image 
{ 
  unsigned char* pixels ; 
  unsigned int largeur ; 
  unsigned int hauteur ; 
} t_image ; 

#define DEBUG 	0	// utilisé en interne dans le module entree_sortie.c 
#define OK 	0		// les 2 codes retour possibles ...
#define ERREUR 	1	// ... de EcrireImagePGM

#define MIROIR_HORIZONTAL	0
#define MIROIR_VERTICAL	1
#define ROTATION_90	0
#define ROTATION_180 1

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
	for (i=1; i<4; i++)
	{
		if (i == 2)
		{
			fscanf(f, "%d %d\n", &largeur, &hauteur) ;
#if DEBUG
			printf("Largeur=%d ; hauteur=%d\n", largeur, hauteur) ;
#endif
		}
		else
		{
			c_res = fgets(s, 255, f) ;
			if (c_res == NULL)
			{
				printf("Erreur lecture ligne %d\n", i) ;
				fclose(f) ;
				return(NULL) ;
			}
#if DEBUG
			printf("ligne %d : %s", i, s) ;
#endif
		}
	}
 
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

//---------------------------------------------------------------------------
void AfficherImage(char* nomFichier)
//---------------------------------------------------------------------------
{
	char commande[128] ;
//	sprintf(commande,"xv %s", nomFichier) ;
	sprintf(commande,"gwenview %s", nomFichier) ;
	system(commande) ;
	printf("Affichage %s\n", nomFichier) ;
}

//---------------------------------------------------------------------------
void LibererImage(t_image* image)
//---------------------------------------------------------------------------
{
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
	for (i=0; i<taille; i++)
		*(image->pixels+i) = 255 - *(image->pixels+i) ; // un peu de notation pointeur
}

//---------------------------------------------------------------------------
void Seuillage(t_image* image, unsigned char seuil)
//---------------------------------------------------------------------------
{
	long int i ;
	long int taille = image->largeur * image->hauteur ;
	for (i=0; i<taille; i++)
		*(image->pixels+i) = (*(image->pixels+i) < seuil) ? 0 : 255 ; // version compacte que l'on peut éventuellement montrer
}

//------------------------------------------------------------------------
void Miroir(t_image* image, char type)
//------------------------------------------------------------------------
{
	unsigned char pixelTemporaire ;
	long int iSource, iDest ;

	if (type == MIROIR_HORIZONTAL)
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

//---------------------------------------------------------------------------
int main(int argc, char* argv[]) 
//---------------------------------------------------------------------------
// lit un fichier image
// on ne fait pas les contrôles de validité depointeur pour simplifier
// teste tous les traitements disponibles
{
	t_image* image ;
	t_image* imageRot ;
	t_image* imageHistogramme ;		 
	int* histogramme ;				// tableau histogramme


// Dégradé
	image = CreerImage(500, 100);
	Degrade(image) ;
	EcrireImagePGM("degrade.pgm", *image) ;
	LibererImage(image) ;

	image = LireImagePGM("guadalest.pgm") ; 

// Histogramme
	histogramme = Histogramme(image) ;
	imageHistogramme = HistogrammeImage(histogramme, 150) ; // toujours largeur = 256 pour l'histogramme
	EcrireImagePGM("histogramme.pgm", *imageHistogramme) ;  

// Négatif
	Negatif(image) ;
	EcrireImagePGM("negatif.pgm", *image) ;

// Miroir
	Miroir(image, MIROIR_VERTICAL) ;
	EcrireImagePGM("miroir.pgm", *image) ;

// Rotation
	imageRot = Rotation(image, ROTATION_90) ;
	EcrireImagePGM("rotation.pgm", *imageRot) ;   

// Seuillage
	Seuillage(image, 128) ;
	EcrireImagePGM("seuillage.pgm", *image) ;

	LibererImage(image) ;
	LibererImage(imageRot) ;
	LibererImage(imageHistogramme) ;
	return EXIT_SUCCESS ;
}	