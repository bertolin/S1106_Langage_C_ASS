#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "entree_sortie.h"
//---------------------------------------------------------------------------
unsigned char* LireImagePGM(const char* nomFichier, int* largeur, int* hauteur) 
//---------------------------------------------------------------------------
// remplit les pixels à partir du fichier nomFichier et retourne le buffer
// si problème, im.buffer = NULL
// renseigne width et height
{
	FILE* f ;
	char s[256] ;
	char* c_res ;
	int i ;
	unsigned char* buffer ;

// ouverture de l'image en lecture  
	f = fopen(nomFichier, "rb") ;
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
			fscanf(f, "%d %d\n", largeur, hauteur) ;
#if DEBUG
			printf("Largeur=%d ; hauteur=%d\n", *largeur, *hauteur) ;
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
	buffer = (unsigned char*) malloc(*largeur* *hauteur*sizeof(unsigned char)) ; 
	if (buffer == NULL)
	{
		printf("Erreur d'allocation mémoire\n") ;
		fclose(f) ;
		return(NULL) ;
	}

// lecture des pixels de l'image
	fread(buffer, *largeur, *hauteur, f) ;
	
// fermeture fichier	
	fclose(f) ;
	return (buffer) ;
}

//---------------------------------------------------------------------------
int EcrireImagePGM(const char* nomFichier, const unsigned char* buffer, const int largeur, const int hauteur) 
//---------------------------------------------------------------------------
// crée (ou écrase) un fichier image avec l'image passée en paramètre
{
	FILE* f ;

// ouverture de l'image à creer en écriture binaire	
	f = fopen(nomFichier, "wb") ;
	if (!f)
	{
		printf("Erreur ouverture de fichier en écriture\n") ;
		return ERREUR ;
	}
	
//  écriture de l'entete de l'image à creer
	fprintf(f, "P5\n") ;
//	fprintf(f, "# CREATOR: Dept Info, IUT2 Grenoble\n") ;
	fprintf(f, "%d %d\n", largeur, hauteur) ;
	fprintf(f, "255\n") ;

	fwrite(buffer, largeur, hauteur, f) ;
	fclose(f) ;

	return OK ;
}	

