// fonctions qui convertissent base 2 <--> base 10
// attention : en entree et en sortie les nombres
// sont stockes en ASCII dans des chaines
// auteur : Pascal Bertolino, 2006
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------------
void Bin2Dec(char bin[], char dec[]) 
//---------------------------------------------------------------------
{
	int i ;
	int n ;
	long int valDec = 0 ;

	n = strlen(bin) ; // n = combien de bits a traiter ?

// schema de Horner. Du poids fort au poids faible
	for (i=0; i<n; i++) 
		valDec = 2*valDec + (bin[i] == '1') ;

// transforme l'entier en chaine
	sprintf(dec, "%ld", valDec) ;
}

//---------------------------------------------------------------------
void Dec2Bin(char dec[], char bin[]) 
//---------------------------------------------------------------------
{
	long int valDec ;
	int i, n ;
	valDec = atoi(dec) ; // recupere la valeur decimale numerique
	
	// n = combien de bits a generer ?
	// (ou utilisation du log2)
	n = 0 ;
	while (valDec)
	{
		valDec >>= 1 ; // division par 2 rapide
		n++ ;
	}

	bin[n] = '\0' ; // terminer la chaine

	valDec = atoi(dec) ;
	for (i=n-1; i>=0; i--) // divisions succesives par 2
	{
		if (valDec % 2) // recuperation du reste
			bin[i] = '1' ;
		else
			bin[i] = '0' ;

		valDec >>= 1 ; // division par 2 rapide
	}
}

//---------------------------------------------------------------------
int main(int argc, char* argv[])
//---------------------------------------------------------------------
{
	char dec[64] ; // on prevoit large
	char bin[64] ;

	printf("Donner un nombre en binaire : ") ;
	scanf("%s", bin) ;
	Bin2Dec(bin, dec) ;
	printf("<%s>2 = <%s>10\n", bin, dec) ;

	printf("Donner un nombre en decimal : ") ;
	scanf("%s", dec) ;
	Dec2Bin(dec, bin) ;
	printf("<%s>10 = <%s>2\n", dec, bin) ;
	
	return EXIT_SUCCESS ;	
}
