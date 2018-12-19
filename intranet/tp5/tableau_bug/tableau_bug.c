#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CreerTableau(char* tab)
// Cree et remplit un tableau dont l'adresse est passee en parametre
// retourne 1 si creation OK, 0 sinon
{
  int cr ;
  tab = malloc(8) ;
  if (tab)
  {
    strcpy(tab, "Gotcha!") ;
    cr = 1 ;
  }
  else
    cr = 0 ;
  free(tab) ;
  return cr ;
}

int main()
// Affiche le contenu d'un tableau cre'e' par l'appel d'une fonction
{
  char* chaine ;
  int ok = CreerTableau(chaine) ;
  if (ok)
    printf("%s\n", chaine) ;   // doit afficher "Gotcha!"
  else
    printf("Tableau non cre'e'") ;
  return EXIT_SUCCESS ;
}
