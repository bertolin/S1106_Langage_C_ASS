#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define ON '*'
#define OFF '.'
#define TEMPORISATION 300
//typedef unsigned int interrupteurs_t ;

//------------------------------------------------------------------------------
void Temporisation(int n)

// Fonction qui met n milli-secondes a s'executer
// C'est donc une temporisation de n ms
// necessite <stdio.h>
{
	clock_t start, stop ;

	n = n*CLOCKS_PER_SEC/1000 ; // clock() ne fonctionne pas forcement en milli-secondes
	start = clock() ;           // Top depart. start = l'heure de depart
	stop = start + n ;          // stop = l'heure de fin

	while(clock() < stop)       // On scrute l'heure tant qu'on n'a pas atteint la fin
	{
	}
}

//------------------------------------------------------------------------------
int ValeurAmpoule(interrupteurs_t chen, int i)
//------------------------------------------------------------------------------
{ // sizeof(interrupteurs_t)*8 est le nombre d'ampoules
  // les bits sont numérotés de droite à gauche contrairement aux ampoules (d'où le -i)
  // -1 car le premier bit pondère la puissance 0
	interrupteurs_t mask = 1 ;
	interrupteurs_t res ;
	mask = mask << (sizeof(interrupteurs_t)*8-i-1) ;
	res = chen & mask ;
	res = res >> (sizeof(interrupteurs_t)*8-i-1) ;	// pour directement renvoyer 1 si res est non nul
//  autre solution : plus courte mais sans doute plus couteuse :
//	res = chen & (interrupteurs_t)powl((long double)2,(long double)(sizeof(interrupteurs_t)*8-i-1)) ;
	return (int)res ;
}

//------------------------------------------------------------------------------
interrupteurs_t Inversion(interrupteurs_t chen)
//------------------------------------------------------------------------------
{
	return ~chen ;
}

//------------------------------------------------------------------------------
interrupteurs_t Compteur(interrupteurs_t chen)
//------------------------------------------------------------------------------
{
	return chen + 1 ;
}

//------------------------------------------------------------------------------
interrupteurs_t RotationGauche(interrupteurs_t chen)
//------------------------------------------------------------------------------
{
	interrupteurs_t chen2 = chen << 1 ; // 1 décalage à gauche
	if (chen2 < chen) // l'ampoule de gauche doit se rallumer à droite
		chen2 += 1 ;
	return chen2 ;
}

//------------------------------------------------------------------------------
interrupteurs_t RotationDroite(interrupteurs_t chen)
//------------------------------------------------------------------------------
{
	interrupteurs_t chen2 = chen >> 1 ; // 1 décalage à droite
	if (chen2 << 1 != chen) // l'ampoule de droite doit se rallumer à gauche
		chen2 +=(interrupteurs_t)powl((long double)2,(long double)(sizeof(interrupteurs_t)*8-1)) ;
	return chen2 ;
}

//------------------------------------------------------------------------------
int main(int argc, char*argv[])
//------------------------------------------------------------------------------
{
	char on=ON;				
	char off=OFF;
	char nb_ampoule=8*sizeof(interrupteurs_t) ;
	int temporisation=TEMPORISATION;
	interrupteurs_t chenillard ;
	int i ;
	int y;
	unsigned char rampe[8*sizeof(interrupteurs_t)+1]={0};

	for (y=1; y<argc; y+=2)
	{
		if (argv[y][1]=='e')
			off=argv[y+1][0];
		else if (argv[y][1]=='a')
			on=argv[y+1][0];
		else if (argv[y][1]=='t')
			temporisation=atoi(argv[y+1]);
		else
		{
			printf("Argument incorrect\nUsage : chenillard_v2 -a <car_ampoule_allumee> -e <car_ampoule_eteinte> -t <temporisation>\n");
			return EXIT_FAILURE;
		}
	}

	printf("%d ampoules\n", nb_ampoule) ;
	chenillard = 0x07 ;	// exemple d'initialisation : .....***

	while (1)
	{
	  // remplit le chenillard
		for (i=0; i<nb_ampoule; i++)
		{
			if (ValeurAmpoule(chenillard, i) == 0)
				rampe[i] = OFF ;
			else
				rampe[i] = ON ;Â´
		}
		printf("%s\r", rampe);
		fflush(stdout);
		Temporisation(temporisation);
		// met à jour le chenillard
//		chenillard = Inversion(chenillard) ;
//		chenillard = Compteur(chenillard) ;		
//		chenillard = RotationGauche(chenillard) ;
		chenillard = RotationDroite(chenillard) ;
	}
}
