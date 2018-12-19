#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n1, n2, res ;
	char op ;
	
	printf("---------------------------\n") ;
	printf("programme calculette entier\n") ;
	printf("---------------------------\n") ;
	printf("operateur (+, -, *) : ") ;
	scanf("%c", &op) ;
	
	if (op != '+' && op != '-' && op != '*')
	{
		printf ("Operateur invalide\n") ;
		return EXIT_FAILURE ;
	}

	printf("premier entier : ") ;
	scanf("%d", &n1) ;
	
	printf("deuxieme entier : ") ;
	scanf("%d", &n2) ;
	
	if (op == '+')
		res = n1 + n2 ;
	else if (op == '-')
		res = n1 - n2 ;
	else // op == '*'
		res = n1 * n2 ;
	
	printf("%d %c %d = %d\n", n1, op, n2, res) ;
	return EXIT_SUCCESS ;
}