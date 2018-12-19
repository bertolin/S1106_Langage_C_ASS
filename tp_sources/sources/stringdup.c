#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h> (si on n'inclut pas stdlib.h)
// #include <string.h> si utilisation strlen et strcpy

// Version facile avec strlen et strcpy (pour info)
/*
//------------------------------------------------------------------------------
char *StringDupFacile(const char *string)
//------------------------------------------------------------------------------
{
	char *newString;

	if (string != NULL)
	{
		newString = malloc(strlen(string) + 1) ; 
		if (newString != NULL)
			strcpy(newString, string) ;
		return newString ;
	}
	else  return NULL ;
}
*/

// Version qui n'utilise que malloc
//------------------------------------------------------------------------------
char *StringDup(const char *string)
//------------------------------------------------------------------------------
{
	char *newString;
	
	if (string != NULL)
	{
		int len ;
		int i = 0 ;
// recherche i, la longueur de la chaine a dupliquer (sans le \0 final bien-sur)
		while (string[i] != '\0') // un peu de notation tableau
			i++ ;
		printf("strlen = %d\n", i) ; // trace
		len = i ;

		newString = (char*)malloc(len + 1) ; // ici, pas la peine d'utiliser sizeof
											                   //	car on calcule déja en octets
		if (newString != NULL)
		{
			for (i=0; i<= len; i++)				// = permet de copier le 0 terminal aussi
				*(newString+i) = *(string+i) ; 	// ou newString[i] = string[i] ; 	 
		}
		return newString ;
	}
	else return NULL ;
}

//------------------------------------------------------------------------------
int main()
//------------------------------------------------------------------------------
{
	char source[256] = "ceci est un test" ;
//  char source[256] = "" ;  // Tester que ca marche avec la chaine vide
	char* destination ; // juste un pointeur, la chaine est allouee dans strdup
	
	destination = StringDup(source) ;	
	printf("source \t\t***%s***\n", source) ;
	printf("destination\t***%s***\n", destination) ;
	free(destination) ; // nettoyage
	return EXIT_SUCCESS ;
}
