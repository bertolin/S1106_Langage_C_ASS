#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------------
void Carre(int* adr_x)
//------------------------------------------------------------------------------
{
	*adr_x *= *adr_x ; // ou *adr_x = *adr_x * *adr_x
}


//------------------------------------------------------------------------------
int main()
//------------------------------------------------------------------------------
{
	int x = 4 ;

	printf("avant : x=%d\n", x) ;
	Carre(&x) ;
	printf("apres : x=%d\n", x) ;

	return EXIT_SUCCESS ;
}
