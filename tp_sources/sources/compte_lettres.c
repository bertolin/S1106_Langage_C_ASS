#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define FIN 1

//----------------------------------------------------
int LireUneLigne(char*buf, int size, FILE* f)
// Pascal Bertolino 2005
// lit une ligne du fichier f
// met dans buf les size-1 premiers caracteres maxi
// jette les suivants s'ils existent
// enleve le '\n' de la fin s'il y est
// marche aussi avec les chaines vides
// retourne FIN si rien à lire, OK sinon
//----------------------------------------------------
{
	char trash[64] ;  // chaine poubelle
	char* res ;		// retour de la fonction fgets
		
	res = fgets(buf, size, f) ; // recupere le debut dans buf
	if (!res)
		return FIN ;

	if (strchr(buf, '\n') == NULL) 
	{		// on n'a pas lu le RC donc on n'a pas tout lu
		do // on jette la suite
		{
			res = fgets(trash, 64, f) ;
			if (res == NULL)
				return FIN ;
			//printf("*jette:%s*\n", trash) ;		
		}
		while (strchr(trash, '\n') == NULL) ;
	}
	else
	{
		*strchr(buf, '\n') = '\0' ; // remplace '\n' par '\0'
	}
		
	return OK ;	 	
}

//--------------------------------------------------------------------------------
int main()
//--------------------------------------------------------------------------------
{
	int i, l ;
	unsigned char s[256] ;	// unsigned pour traiter les car > 127
	int nb[256] ;			// unsigned provoque 2 warning si on ne cast pas 

	printf("Entrez une chaine quelconque : ") ;
	LireUneLigne(s, 256, stdin) ; // aujourd'hui on ne traite pas le code renvoye' par LireUneLigne

	l = strlen(s) ;
	
// Mise à zero des compteurs d'occurrence	
	for (i=0; i<256; i++)
		nb[i] = 0 ;

// Parcours de la chaine
	for (i=0; i<l; i++)
// Incremente le compteur du caractere courant
		// nb[s[i]]++ ;	// caster en int pour eviter le warning suivant
				// array subscript has type `char'
		nb[(int)s[i]]++ ;

// Affiche le nombre d'occurrence
	for (i=0; i<256; i++)
	{
		if (nb[i] != 0)
			printf("%c : %d \n", i, nb[i]) ;
	}

	return EXIT_SUCCESS ;
}