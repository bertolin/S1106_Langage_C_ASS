#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n1, n2 ;
	
	printf("programme qui multiplie 2 nombres\n") ;
	printf("Saisir un premier nombre :\n") ;
	scanf("%d", &n1) ;
	printf("Saisir un deuxième nombre :\n") ;
	scanf("%d", &n2) ;
	printf("%d x %d = %d\n", n1, n2, n1*n2) ;
	return EXIT_SUCCESS ; 
}
