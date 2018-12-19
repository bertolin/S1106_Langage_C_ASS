#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------------
void Permut(int* adr_a, int* adr_b)
//------------------------------------------------------------------------------
// pour cette fois, on nomme les parametres adr_x au lieu de x pour
// eviter de perdre les etudiants
{
	int inter ;

	printf("Permutation...\n") ;

	inter = *adr_a ;
	*adr_a = *adr_b ;
	*adr_b = inter ;
}

//------------------------------------------------------------------------------
int main()
//------------------------------------------------------------------------------
{
	int a = 1 ;
	int b = 2 ;

	printf("avant : a=%d, b=%d\n", a, b) ;
	Permut(&a, &b) ;
	printf("apres : a=%d, b=%d\n", a, b) ;

	return EXIT_SUCCESS ;
}
