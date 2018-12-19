#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------
int main()
//--------------------------------------------------------------------------------
{
	char ch1[64] = "bonjour" ;
	char ch2[64] = "xxxxxxxxxxxxxxxxx" ; 
	int i ;
	int lg = strlen(ch1) ; // à n'exécuter qu'une fois.
	for (i=0; i<lg; i++)
	{
		ch2[i] = ch1[lg-i-1] ;
 	}
	ch2[i] = '\0' ;
	printf("ch2=***%s***\n", ch2) ;
	return EXIT_SUCCESS ;
}
