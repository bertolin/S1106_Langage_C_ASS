#include "negatif.h"
//---------------------------------------------------------------------------
void Negatif2(t_image* image)
//---------------------------------------------------------------------------
{
	long int i ;
	long int taille = image->largeur * image->hauteur ;

	for (i=0; i<taille; i++)
		*(image->pixels+i) = 255 - *(image->pixels+i) ; // un peu de notation pointeur
}
