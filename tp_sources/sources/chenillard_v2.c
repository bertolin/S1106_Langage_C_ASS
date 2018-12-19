// Affiche un chenillard simple sur une ligne de shell
// l'etat des ampoules est memorisé dans un tableau
// Le chenillard est parametrable dans la ligne de commande
#include <stdio.h>
#include <stdlib.h> // pour atoi
#include <string.h>
#include <time.h>	// pour le timer

//------------------------------------------------------------------------------
void Temporisation(int n)
//------------------------------------------------------------------------------
// Fonction qui met n milli-secondes a s'executer
// C'est donc une temporisation  de n ms
{
	clock_t start, stop ;

	n = n*CLOCKS_PER_SEC/1000 ; // clock() ne fonctionne pas forcement en milli-secondes
	start = clock() ; // Top depart. start = l'heure de depart
	stop = start + n ; // stop = l'heure de fin

	while(clock() < stop) // On scrute l'heure tant qu'on n'a pas atteint la fin
	{
	} 
}

//------------------------------------------------------------------------------
void AfficheUsage() 
//------------------------------------------------------------------------------
{ // en ligne, c'est plus facilement maintenable...
	printf("Usage : chenillard_v2 ") ;
	printf("[-a <car_ampoule_allume>] ") ;
	printf("[-e <car_ampoule_etteinte>] ") ;
	printf("[-t <temporisation>] ") ;	
	printf("[-n <nombre_d_ampoules>] ") ;
	printf("\n") ;
}

//------------------------------------------------------------------------------
int main(int argc, char* argv[])
//------------------------------------------------------------------------------
{
#define LONGUEUR 30
#define TEMPO 200			// a peu près des ms
#define ALLUME '*'			// on manipule des caractères '
#define ETEINT '.'
#define AMPOULE_MAX 100 	// AMPOULE_MAX ampoules maxi,

// AMPOULE_MAX ampoules maxi => tableau de AMPOULE_MAX+1 caractères  
	char amp[AMPOULE_MAX+1] = {0} ; // rempli à 0 
	int i ;
	
// On utilise des variables maintenant 	
	char allume, eteint ;
	int tempo ;
	int longueur ;

// Chargement des valeurs par defaut
	allume = ALLUME ;
	eteint = ETEINT ;
	tempo = TEMPO ;
	longueur = LONGUEUR ;

// Nombre pair d'arguments -> erreur
	if ((argc %2) != 1)
	{
		printf("Nombre d'argument erroné\n") ;
		AfficheUsage() ;
		return EXIT_FAILURE ;
	}

// parcours des arguments 2 par 2
	for (i=1; i<argc; i+=2)
	{
		if ((argv[i][0] != '-') || // il n'ont pas encore vu strcmp 
		(argv[i][1] != 'a' &&      // mais comme cela c'est tres bien aussi
		 argv[i][1] != 'e' &&
		 argv[i][1] != 't' &&
		 argv[i][1] != 'n'))
		{
			printf("Argument %s erroné\n", argv[i]) ;
			AfficheUsage() ;
			return EXIT_FAILURE ;
		}

// eventuellement, on ecrase une ou plusieurs valeurs par defaut		
		if (argv[i][1] == 'a')
			allume = argv[i+1][0] ; 	// on recupere le caractere
		else if (argv[i][1] == 'e')
			eteint = argv[i+1][0] ; 	// idem
		else if (argv[i][1] == 't')		// c'est un entier rangé dans une chaine
			tempo = atoi(argv[i+1]) ;	// on devrait verifier la validite des valeurs 
		else if (argv[i][1] == 'n')		// idem
			longueur = atoi(argv[i+1]) ;

		if (longueur > AMPOULE_MAX)
		{
			printf("Nombre d'ampoules limite a %d\n", AMPOULE_MAX) ;
			AfficheUsage() ;
			return EXIT_FAILURE ;
		}
	}

// ci dessous, c'est idem version 1 sauf que les constantes sont remplacees par 
// des variables
	while (1) // toujours vrai, il faudra arreter le prog avec un "Controle C"
	{
		int t ;
// l'ampoule allumee prendra toute les positions t au fil du temps
		for (t=0; t<longueur; t++)
		{
// on remplit le tableau avant de l'afficher. t est l'ampoule allumée
			for (i=0 ; i<longueur ; i++) 	// on pourrait optimiser en memorisant
				amp[i] = eteint ;     		// la dernière allumee
			amp[t] = allume ;

// affichage des ampoules
			printf("%s\r", amp) ; 		// retour chariot sans passage a la ligne
			fflush(stdout) ;			// force l'ecriture des donnees mises en memoire tempon
			Temporisation(tempo) ; 		// sinon, on ne voit rien
		}
	}
}
