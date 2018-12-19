#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define ON '*'
#define OFF '.'
#define NB_AMPOULE 30
#define TEMPORISATION 600

//------------------------------------------------------------------------------
void Temporisation(int n)

// Fonction qui met n milli-secondes a s'executer
// C'est donc une temporisation  de n ms
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

int main(int argc, char*argv[])
{
	char on=ON;
	char off=OFF;
	char nb_ampoule=NB_AMPOULE;
	int temporisation=TEMPORISATION;

	int y;

	for (y=1; y<argc; y+=2)
	{
		if (argv[y][1]=='e')
			off=argv[y+1][0];
		else if (argv[y][1]=='a')
			on=argv[y+1][0];
		else if (argv[y][1]=='n')
			nb_ampoule=atoi(argv[y+1]);
		else if (argv[y][1]=='t')
			temporisation=atoi(argv[y+1]);
		else
		{
			printf("Argument incorrect\nUsage : chenillard_v2 -a <car_ampoule_allumee> -e <car_ampoule_eteinte> -n <nombre_ampoules> -t <temporisation>\n");
			return EXIT_FAILURE;
		}
	}

	unsigned char rampe[NB_AMPOULE+1]={0};
	int i;
	int j;

	while (1)
	{
		for (i=0; i<nb_ampoule; i++)
		{
			for (j=0; j<nb_ampoule; j++)
			{
				rampe[j]=off;
			}
			rampe[i]=on;
			printf("%s\r", rampe);
			fflush(stdout);
			Temporisation(temporisation);
		}
	}
}
