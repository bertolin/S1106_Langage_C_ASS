#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "images.h"
#include "entree_sortie.h"
#include "traitement.h"
#include "negatif.h"

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

	clock_t t1, t2 ;

	t1 = clock() ;

//for (int i=0; i<50;i++)
{
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

	Negatif2(image) ;		// test de negatif.o du voisin (on devrait revenir sur l'image originale)
	EcrireImagePGM("negatif_du_voisin.pgm", *image) ;

// Mirroir	
	Mirroir(image, MIRROIR_VERTICAL) ;
	EcrireImagePGM("mirroir.pgm", *image) ;

// Rotation
	imageRot = Rotation(image, ROTATION_90) ;
	EcrireImagePGM("rotation.pgm", *imageRot) ;   

// Seuillage
	Seuillage(image, 128) ;
	EcrireImagePGM("seuillage.pgm", *image) ;

	LibererImage(image) ;
	LibererImage(imageRot) ;
	LibererImage(imageHistogramme) ;
}
	t2 = clock() ;
	printf("Temps total = %f\n", difftime(t1, t2)) ;

	return EXIT_SUCCESS ;
}	