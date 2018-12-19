#include <stdlib.h>
#include <stdio.h>

struct cellule
{
	int donnee ;
	struct cellule* suivant ;
} ;

typedef  struct cellule cell_t ;

void InsereTete(cell_t** list, int val)
{
    cell_t* cell_nouv = (cell_t*)malloc(sizeof(cell_t)) ;
    cell_nouv->donnee = val ;
    cell_nouv->suivant = *list ;
    *list = cell_nouv ;
}

void InsereQueue(cell_t** list, int val)
{
	if (*list)
		InsereQueue(&(*list)->suivant, val) ;
	else
		InsereTete(list, val) ;
}

void InsereTri(cell_t** list, int val)
{
	cell_t** p = list ; // p contiendra l'adresse du pointeur sur la cellule courante
	while (*p && val > (*p)->donnee)
		p = &(*p)->suivant ;
	
	InsereTete(p, val) ;		
}

/*
void InsereTri(cell_t** list, int val)
{
	cell_t* p = *list; // on ne veut pas modifier *list
	cell_t* prec = NULL;
	while (p && val > p->donnee)
	{
		prec = p;	// prec est dans la cellule précédente et non pas un pointeur intermédiaire
		p = p->suivant;
	}
	if (p == *list) // on change l'adresse de la toute première cellule
		InsereTete(list, val);
	else
		InsereTete(&prec->suivant, val);
}
*/

void SuprimCell(cell_t** list)
{
    if (*list != NULL)
    {
        cell_t* cell_asup = *list ;
        *list = (*list)->suivant ;
		printf("Sup %d\n", cell_asup->donnee) ; 
        free(cell_asup) ;
    }
}

void SuprimList(cell_t** list)
{
    while (*list != NULL)
    {
        SuprimCell(list) ;
    }
}

void SuprimImpairs(cell_t** list)
{
	while (*list)
	{
		if ((*list)->donnee % 2)	 
			SuprimCell(list) ;
		else
			list = &(*list)->suivant ;
	}
}

void DisplayList(cell_t* list)
{
	while (list)
	{	// on peut modifier list, ce n'est pas l'original
		printf("%d -> ", list->donnee) ;
		list = list->suivant ; 
	}
	printf("NULL \n") ;
}

int CountList(cell_t* list)
{
	int count = 0 ;
	while (list)
	{   // on peut modifier list, ce n'est pas l'original
		count++ ;
		list = list->suivant ;
	}
	return count ;
}

int CountListRecursif(cell_t* list)
{
	if (list)
		return 1 + CountListRecursif(list->suivant) ;
	else 
		return 0 ;
}

void DisplayListRecursif(cell_t* list)
{
	if (list)
	{
		printf("%d -> ", list->donnee) ;
		DisplayListRecursif(list->suivant) ;
	}
	else
		printf("NULL \n") ;
}

int main()
{
	int val ;
	cell_t * list = NULL ;

	printf("Rentrer des entiers separes par des RC (0 pour terminer)\n") ;
	scanf("%d", &val) ;
	while (val !=0)
	{
		InsereTete(&list, val) ;
		scanf("%d", &val) ;
	}

	printf("\nListe des cellules :\n") ;
	printf("-------------------> ") ;
	DisplayList(list) ;

	printf("Insersion de la valeur 999 en queue de liste \n") ;
	InsereQueue(&list, 999) ;
	printf("\nListe des cellules :\n") ;
	printf("-------------------> ") ;
	DisplayList(list) ;

	printf("\nSuppression toute la liste.\n") ;
	SuprimList(&list) ;

	printf("\n Liste des cellules :\n") ;
	printf("-------------------> ") ;
	DisplayList(list) ;

	printf("\nMaintenant, on va creer une liste trie'e\n") ;
	printf("Rentrer des entiers separes par des RC (0 pour terminer)\n") ;
	scanf("%d", &val) ;
	while (val !=0)
	{
		InsereTri(&list, val) ;
		scanf("%d", &val) ;
	}

	printf("\nListe triee des cellules :\n") ;
	printf("-------------------> ") ;
	DisplayList(list) ;

	printf("\nListe triee des cellules (recursif) :\n") ;
	printf("-------------------> ") ;
	DisplayListRecursif(list) ;

	printf("\nTaille de la liste : %d\n", CountList(list)) ;

	printf("\nTaille de la liste (recursif) : %d\n", CountListRecursif(list)) ;

	printf("\nSuppression elements impairs.\n") ;
	SuprimImpairs(&list) ;

	printf("\nListe triee des cellules :\n") ;
	printf("-------------------> ") ;
	DisplayList(list) ;

	printf("\nSuppression toute la liste.\n") ;
	SuprimList(&list) ;

	printf("\nListe triee des cellules :\n") ;
	printf("-------------------> ") ;
	DisplayList(list) ;

	getchar() ;
	getchar() ;

	return EXIT_SUCCESS ;
}
