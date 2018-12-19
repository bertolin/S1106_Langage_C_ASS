// affiche une pyramide de hauteur donnee avec un caractere donne'
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------------------
void AfficheCar(int n, char ch)
//---------------------------------------------------------------------
{
	int i ;
	for (i=0; i<n; i++)
		putchar(ch) ;
}

// Pour une hauteur h, combien de caracteres c comporte la base ? 
//   2h - 1
// Pour un niveau n, combien de caracteres c sont-ils affiches ? 
//   2n - 1
// Pour un niveau n, combien d'espaces sont-ils affiches avant le premier caractere ? 
//   (2h-1-(2n-1))/2 = h-n

/* main qui recupere h et c avec scanf */
//---------------------------------------------------------------------
int main(int argc, char* argv[])
//---------------------------------------------------------------------
{
	char c ;
	int n, h ;
	
	printf("hauteur : ") ;
	sscanf("%d", &h) ;
	getchar() ;
	printf("caractere : ") ;
	c = getchar() ;
	
	for (n=1; n<=h; n++) // n = etage courant  
	{
		AfficheCar(h-n, ' ') ;  
		AfficheCar(2*n-1, c) ;  
		printf("\n") ;
	}
	
	return EXIT_SUCCESS ;	
}

/* main qui recupere h et c dans la ligne de commande 
//---------------------------------------------------------------------
int main(int argc, char* argv[])
//---------------------------------------------------------------------
{
	char c ;
	int n, h ;

	if (argc == 1)
	{
		printf("Usage : pyramide <hauteur> <caractere>\n") ;
		return EXIT_FAILURE ;
	}

	h = atoi(argv[1]) ;
	c = argv[2][0] ;		// le premier caractere de la chaine argv[2]
	
	for (n=1; n<=h; n++) // n = etage courant  
	{
		AfficheCar(h-n, ' ') ;  
		AfficheCar(2*n-1, c) ;  
		printf("\n") ;
	}
	
	return EXIT_SUCCESS ;	
}
*/
