#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
// compte le nombre d'occurrences d'une sous-chaine s dans une chaine S
// dans cette version, la sous-chaine doit etre non vide
// cette version est compliquee. On peut certainement faire mieux
// je suis preneur...
{
	int i, j, l, L ;
	char nb ; 		// compteur d'occurrences
	int trouve ; 	// utilise' ici comme un bool?en
	
	char S[] = "un mmur mura murat et murat murmura" ;
	char s[] = "mur" ;
//	le cas particulier (piege) est "mmur"
	
//	autre jeu de test
//	char S[] = "ccc" ;
//	char s[] = "c" ;

	L = strlen(S) ;
	l = strlen(s) ;
	nb = 0 ;
	i = 0 ;

// Parcours unique de la chaine principale
	while (i<L-l+1) // on s'arrete a temps
	{
		trouve = 1 ;
		j = 0 ;
		while (trouve && j<l) // parcours de la sous-chaine
		{
			if (s[j] != S[i]) 	// on ne trouve pas a cette position
			{
				trouve = 0 ;	// on veut sortir de la boucle
				if (j==0)			// attention, gestion d'un cas bien particulier !	
					i++ ;				// s[j] (!= S[i]) est peut etre = S[0]
			}
			else
			{
				i++ ; // i indice dans chaine principale
				j++ ; // j indice dans sous-chaine
			}
		}
		
		if (j == l) // la sous-chaine entière a ete trouvee
			nb++ ;
	}

	printf ("%d occurrences\n", nb) ;
	return EXIT_SUCCESS ;
}
	
