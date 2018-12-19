#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Image
{
  unsigned char* pixels ;
  unsigned int largeur ;
  unsigned int hauteur ;
} t_image ;

#define DEBUG 	0	// utilis� en interne dans le module entree_sortie.c
#define OK 	0		// les 2 codes retour possibles ...
#define ERREUR 	1	// ... de EcrireImagePGM

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
// cr�e dynamiquement une structure image
// retourne la structure image remplie � partir du fichier nomFichier
// si probl�me, retourne NULL
{
	FILE* f ;
	char s[256] ;
	char* c_res ;
	int i, largeur, hauteur ;
	t_image* im ; // la structure qui sera renvoy�e

// ouverture de l'image en lecture
	f = fopen(nomFichier, "rb") ;	// b non necessaire sou Linux
	if (!f)
	{
		printf("*** Erreur ouverture de fichier ***\n") ;
		return(NULL) ;
	}

// lecture des 3 premi�res lignes et r�cup�ration dimensions de l'image
	for (i=1; i<4; i++)
	{
		if (i == 2)
		{
			fscanf(f, "%d %d\n", &largeur, &hauteur) ;
		}
		else
		{
			c_res = fgets(s, 255, f) ;
			if (c_res == NULL)
			{
				printf("*** Erreur lecture ligne %d ***\n", i) ;
				fclose(f) ;
				return(NULL) ;
			}
		}
	}

// allocation m�moire pour les pixels de l'image
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
// cr�e (ou �crase) un fichier image avec les informations de la structure
{
	FILE* f ;

// ouverture de l'image � creer en �criture binaire
	f = fopen(nomFichier, "wb") ;	// b non necessaire sous Linux
	if (!f)
	{
		printf("*** Erreur ouverture de fichier en �criture ***\n") ;
		return ERREUR ;
	}

//  �criture de l'entete de l'image � creer
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
		*(image->pixels+i) = (*(image->pixels+i) < seuil) ? 0 : 255 ; // version compacte que l'on peut �ventuellement montrer
}

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
//---------------------------------------------------------------------------
// version minimaliste
// appelle les fonctions d�finies ci-dessus
{
	t_image* image ;

// Lecture image
    image = LireImagePGM("voiron.pgm") ;
	if (!image)
	{
		printf("*** Lecture image impossible ***\n") ;
		return EXIT_FAILURE ;
	}

// N�gatif
	Negatif(image) ;
	EcrireImagePGM("negatif.pgm", *image) ;

// Seuillage
	Seuillage(image, 128) ;
	EcrireImagePGM("seuillage.pgm", *image) ;

	LibererImage(image) ;
	return EXIT_SUCCESS ;
}
