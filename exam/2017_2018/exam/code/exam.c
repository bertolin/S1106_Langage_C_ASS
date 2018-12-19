#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LONG_CHAINE	32
struct vetement
{
    char nom[LONG_CHAINE] ; 	// nom du produit
	unsigned int ref ;		// référence du produit 
    float prix ;    // prix du produit en euros,centimes
// a enlever sur le sujet	
	struct vetement* suivant ;

} ;
typedef struct vetement vet_t ; //vet_t : nom de type utilisé par la suite

void AfficherListe(vet_t* list) ;


//***1
void AfficherVetement(vet_t vet)
//------------------------------
{
    printf("%s %u %.2f\n", vet.nom, vet.ref, vet.prix);
}

//***3
#define AFFICHER_VETEMENT(vet) printf("%s %u %.2f\n", vet.nom, vet.ref, vet.prix)

//***5
void PrixSolde(vet_t *vet)
//------------------------------
{
    vet->prix = vet->prix/2;
}

//***7
vet_t* NouveauVetement(char* nom, unsigned int ref, float prix)
//------------------------------
{
	vet_t* v = malloc(sizeof(vet_t)) ;
	if (v)
	{
		strcpy(v->nom, nom) ;
		v->ref = ref ;
		v->prix = prix ;
	}
	return v ;
}

//***9
int CompterInferieurDixEuros(vet_t tabVet[], int nb)
//------------------------------
{
    int i ;
    int total = 0 ;
    for (i=0; i<nb; i++) // ou un while correct bien sûr
    {
        if( tabVet[i].prix < 10 )
            total ++ ;
    }
    return total ;
}

//***11
void SupprimeHorsMajuscules(char* nom)
//------------------------------
{
	int i = 0 ;
	while (nom[i] != '\0')
	{
		if (nom[i] < 'A' || nom[i] > 'Z')
			nom[i] = '.' ;
		i++ ;
	}
}

//***13
bool PasSoldable(vet_t v)
//------------------------------
{
	unsigned int mask = 1 << (8*sizeof(int)-1) ;
	printf("sizeof(unsigned int)=%lu\n", sizeof(int)) ;
	printf("mask=%u\n", mask) ;
	return (mask & v.ref) ;	
}

//***15
void EcrireUnVetement(vet_t v, char* nomFichier)
//------------------------------
{
	FILE* f = fopen(nomFichier, "a") ;
	fwrite(&v, sizeof(vet_t), 1, f) ;
	fclose(f) ;
}

//***17
bool LireUnVetement(FILE* f, vet_t* v)
//------------------------------
{
	if (fread(v, sizeof(vet_t), 1, f))
		return true ;
	else
		return false ;
}

#ifdef MAIN1
int main (int argc, char* argv[])
//------------------------------
{
//***2
	vet_t v1={"chemise", 1234, 20.99};
	AfficherVetement(v1) ;
	
//***4	
	vet_t v2 ;
	strcpy(v2.nom, "short") ;
	strncpy(v2.nom, "short tres tres long 1234567880122345678901234567890", LONG_CHAINE-1) ;
	v2.ref = 456 ;
	v2.prix = 12.90 ;
	AFFICHER_VETEMENT(v2) ;

//***6	
	PrixSolde(&v2) ;
	AFFICHER_VETEMENT(v2) ;

//***8	
	vet_t* v3 = NouveauVetement("chaussettes", 432, 5.95) ;
	if (v3)
	{
		AfficherVetement(*v3) ;
		free(v3) ;
	}
	else
		printf("Creation vetement impossible\n") ;
	
//***10
	vet_t tab[]={{"aaa", 1024, 11.3}, {"bbb", 2028, 7.1}} ;
	int nb10 = CompterInferieurDixEuros(tab, 2) ;
	printf("%d vetements < 10 euros\n", nb10) ;

//***12
	char nom[] = "CHEMISETTE d'4t5 !" ;
	SupprimeHorsMajuscules(nom) ;
	printf("%s\n",nom) ;
	
//***14
	vet_t v={"test", 0x70000000, 123} ;
	if (PasSoldable(v))
	{
		AfficherVetement(v) ;
		printf("n'est pas soldable\n") ;
	}
		
//***16
	vet_t v4={"cravatte", 789, 21.30} ;
	vet_t v5={"noeud papillon", 333, 15.20} ;
	
	EcrireUnVetement(v4, "fich_vetement.txt") ;
	EcrireUnVetement(v5, "fich_vetement.txt") ;
	
//***18
	vet_t vetf ;
	FILE* f = fopen("fich_vetement.txt", "r") ;
	printf("Contenue du fichier :\n") ;
	while (LireUnVetement(f, &vetf))
		AfficherVetement(vetf) ;
	fclose(f) ;
	
	return EXIT_SUCCESS ;
}
#endif

#ifdef MAIN2
//***19
int main (int argc, char* argv[])
{
// exemple d'appel :
// prog vetements.txt chaussettes 1234 7.90  
    vet_t vet ;
    FILE* f ;
    if (argc != 5)
    {
        printf("pas le bon nombre d'arguments\n") ;
        return EXIT_FAILURE ;
    }
    f = fopen(argv[1], "a") ;
    if (!f)
    {
        printf("pb a l'ouverture\n") ;
        return EXIT_FAILURE ;
    }
	fclose(f) ;	
	strncpy(vet.nom, argv[2], LONG_CHAINE-1) ;
	vet.ref = atoi(argv[3]) ;
	vet.prix = atof(argv[4]) ;
	EcrireUnVetement(vet, argv[1]) ;
// juste pour tester si ça marche bien ---------
	f = fopen("fich_vetement.txt", "r") ;
	printf("Contenu du fichier :\n") ;
	while (LireUnVetement(f, &vet))
		AfficherVetement(vet) ;
	fclose(f) ;	
//----------------------------------------------	
    return EXIT_SUCCESS ;
}
#endif
//***21
void InsertTete(vet_t** list, char* nom, unsigned int ref, float prix)
{
	vet_t* v = malloc(sizeof(vet_t)) ;
	strncpy(v->nom, nom, LONG_CHAINE-1) ;
	v->ref = ref ;
	v->prix = prix ;
	v->suivant = *list ;
	*list = v ;
}

//***23
void AfficherListe(vet_t* list)
{
	if (list)
	{
		printf("%s %u %.2f\n", list->nom, list->ref, list->prix);
		AfficherListelist->suivant ;
	}
}

#define MAIN3
#ifdef MAIN3
//***20
int main (int argc, char* argv[])
{
/*	struct vetement
	{
		char nom[LONG_CHAINE] ; 	// nom du produit
		unsigned int ref ;		// référence du produit 
		float prix ;    // prix du produit en euros,centimes
		struct vetement* suivant ;
	} ;
	typedef struct vetement vet_t ; //vet_t : nom de type utilisé par la suite
*/
	//***22	
	vet_t* list = NULL ;
	InsertTete(&list, "pull", 34, 11.22) ;
	InsertTete(&list, "jupe", 45, 15.33) ;
	printf("Liste :\n") ;
	AfficherListe(list) ;
}
#endif

