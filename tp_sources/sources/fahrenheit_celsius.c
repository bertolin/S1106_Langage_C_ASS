#include <stdio.h>
#include <stdlib.h>
// Conversion de temperatures en degres Fahrenheit  vers degres Celsius.

float celsius(float); // necessaire car celsius definie apres son appel

//----------------------------------------------------------------------------
int main()
//----------------------------------------------------------------------------
{
 /* Programme qui affiche la conversion des degres
  * Fahrenheit (de 0 a 300 par pas de 20) en Celcius
  */

	int bas, haut, pas ;
	float fahr, c ;
	bas = 0 ;
	haut = 300 ;
	pas = 20 ;

	fahr = bas ; 
	printf("----------------------\nFahrenheit  Celsius\n----------------------\n") ;
	while(fahr <= haut)
	{
		c = celsius(fahr) ;
		printf("%8.0f %8.1f \n", fahr, c) ; // encore mieux que \t pour le cadrage
		fahr += pas ;
	}
	return EXIT_SUCCESS ;
}

//----------------------------------------------------------------------------
float celsius(float x)
//----------------------------------------------------------------------------
{
	return (5.0/9.0)*(x-32.0) ; // attention, les constantes sont des reels
}