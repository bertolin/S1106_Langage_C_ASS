#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, n ;
	
	printf("Vous voulez la table de combien ? ") ;
	scanf("%d", &n) ;
	for (i=0; i<=10; i++)
	{
		printf("%d x %d = %d\n", i, n, i*n) ;	
	}
	return EXIT_SUCCESS ;
}