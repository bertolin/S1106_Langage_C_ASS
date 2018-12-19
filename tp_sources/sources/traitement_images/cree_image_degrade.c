#include <stdio.h>
#include <stdlib.h>

#define LARGEUR 256
#define HAUTEUR 200

//----------------------------------------------------------------------------
int main(int argc, char* argv[])
//----------------------------------------------------------------------------
// argv[1] récupère le nom du fichier à traiter
{
	FILE* f ;
	int ligne, col ;
	
// test du nombre d'arguments
	if (argc != 2)
	{
		printf("\nusage : cree_image_degrade <fichier_image.pgm>\n") ;
		return(EXIT_FAILURE) ;
	}
			
// ouverture de l'image en écriture (marche indifferamment en "wb" ou "w")
	f = fopen(argv[1], "w") ;
	if (!f)
	{
		printf("Erreur ouverture de fichier\n") ;
		return(EXIT_FAILURE) ;
	}
		
//  ecriture de l'entete de l'image à creer
	fprintf(f, "P5\n") ;
	fprintf(f, "# CREATOR: Dept Info, IUT2 Grenoble\n") ;
	fprintf(f, "%d %d\n", LARGEUR, HAUTEUR) ;
	fprintf(f, "255\n") ;

// ecriture des pixels
	for (ligne = 0; ligne < HAUTEUR; ligne++)
	{
		for (col = 0; col < LARGEUR; col++)
			fputc(col, f) ; // col est justement la couleur voulue !
	}

// fermeture fichier	
	fclose(f) ;
	return EXIT_SUCCESS ;
}
