#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "entree_sortie.h"
//---------------------------------------------------------------------------
unsigned char* LireImagePGM(const char* nomFichier, int* largeur, int* hauteur) 
//---------------------------------------------------------------------------
// remplit les pixels � partir du fichier nomFichier et retourne le buffer
// si probl�me, im.buffer = NULL
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
	
// lecture des 3 premi�res lignes et r�cup�ration dimensions de l'image	
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
 
// allocation m�moire pour les pixels de l'image
	buffer = (unsigned char*) malloc(*largeur* *hauteur*sizeof(unsigned char)) ; 
	if (buffer == NULL)
	{
		printf("Erreur d'allocation m�moire\n") ;
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
// cr�e (ou �crase) un fichier image avec l'image pass�e en param�tre
{
	FILE* f ;

// ouverture de l'image � creer en �criture binaire	
	f = fopen(nomFichier, "wb") ;
	if (!f)
	{
		printf("Erreur ouverture de fichier en �criture\n") ;
		return ERREUR ;
	}
	
//  �criture de l'entete de l'image � creer
	fprintf(f, "P5\n") ;
//	fprintf(f, "# CREATOR: Dept Info, IUT2 Grenoble\n") ;
	fprintf(f, "%d %d\n", largeur, hauteur) ;
	fprintf(f, "255\n") ;

	fwrite(buffer, largeur, hauteur, f) ;
	fclose(f) ;

	return OK ;
}	

