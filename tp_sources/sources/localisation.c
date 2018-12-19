#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x, y ;
	printf("Entrez X: ") ;
	scanf("%d", &x) ;
	printf("Entrez Y: ") ;
	scanf("%d", &y) ;
	printf("Position : ") ;

	if (x==0 && y==0)
		printf("centre") ;
	else
	{
		if (y>0)
			printf("nord") ;
		else if (y<0)
			printf("sud") ;

		if (x!=0 && y!=0)
			printf("-") ;

		if (x>0)
			printf("est") ;
		else if (x<0)
			printf("ouest") ;
	}
	printf("\n") ;
	return EXIT_SUCCESS ; 
}
