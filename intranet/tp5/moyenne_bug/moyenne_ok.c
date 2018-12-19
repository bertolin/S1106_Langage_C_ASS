#include <stdio.h>
#include <stdlib.h>

float Moyenne(int* tab, int nb)
// parametres d'entree :
// un tableau d'entiers
// le nombre d'elements dans le tableau
// retourne la moyenne des elements du tableau
{
	int i=0 ;
	float moy = 0 ;
	while (i<nb)
	{
		moy += tab[i] ;
		i++ ;
	}
	return moy / nb ;
}

int main()
// affiche la moyenne des elements d'un tableau d'entiers
{
#define NB	4
	int val[NB] = {3, 5, 9, 10} ;
	printf("Moyenne = %f\n", Moyenne(val, NB)) ;	// le bon resultat est 6.75
	return EXIT_SUCCESS ;
}
