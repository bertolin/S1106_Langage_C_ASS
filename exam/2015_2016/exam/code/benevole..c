#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct benevole
{
    char email[64] ; // email du bénévole
    int dispo ;      // disponibilité du mois courant
} ;
typedef struct benevole t_benevole ; //t_benevole : nom de type utilisé par la suite

#define OK 0       // à utiliser
#define FIN -1     // dans certaines
#define ERREUR 1   // questions

void AfficherBenevole(t_benevole ben)
{
    printf("%s %d\n", ben.email, ben.dispo);
}

#define AFFICHER_BENEVOLE(ben) printf("%s %d\n", (ben).email, (ben).dispo)

void RAZDispo(t_benevole *ben)
{
    ben->dispo = 0;
}

int CompterDisponibleLePremier(t_benevole tabBen[], int nb)
{
    int i ;
    int total = 0 ;
    for (i=0; i<nb; i++) // ou un while correct bien sûr
    {
        if( (tabBen[i].dispo % 2) == 1 )
            total ++ ;
    }
    return total ;
}

t_benevole* CreerBenevole()
{
    t_benevole* ben ;
    ben = malloc(sizeof(t_benevole)) ;
    return ben ;
}
#ifdef MAIN1
int main()
{
    t_benevole* ben ;
    ben = CreerBenevole() ;
    if (ben)
    {
        strcpy(ben->email, "test@gmail.com") ;
        ben->dispo = 0 ;
        AfficherBenevole(*ben) ;
        AFFICHER_BENEVOLE(*ben) ;
        free(ben) ;
    }
    else
        printf(" création bénévole impossible\n ") ;
    return EXIT_SUCCESS ;
}
#endif // MAIN1

int VerifierArobase(char* email)
{
    int i = 0 ;
    int nb = 0 ;
    while (email[i] != '\0')
    {
        if (email[i] == '@')
            nb++ ;
        i++ ;
    }
    if (nb == 1)
        return OK ;
    else
        return ERREUR ;
}

void InitBenevole(t_benevole* ben, char* email, int dispo)
{
    strncpy(ben->email, email, 64) ;
    ben->dispo = dispo ;
    if (VerifierArobase(ben->email) == ERREUR)
        printf("email erroné : %s\n", ben->email) ;
}

int EstDisponibleCeJour(int dispo, int i)
{
    int masque = 0x01 ;
    masque = masque << i-1 ;
    if (dispo & masque)
        return 1 ;
    else
        return 0 ;
}
#ifdef MAIN2
int main()
{
    t_benevole ben ;
    int i ;
    int nb = 0 ;
    InitBenevole(&ben,"john@do@truc.com ",15);
    for (i=1; i<=31; i++)
        nb += EstDisponibleCeJour(ben.dispo, i) ;
    printf("%s est disponible %d jours ce mois-ci\n", ben.email, nb) ;
    return EXIT_SUCCESS ;
}
#endif // MAIN2

void EcrireBenevole(t_benevole ben, FILE* f)
{
    fwrite(&ben, sizeof(t_benevole), 1, f) ;
}

int LireBenevole(FILE* f, t_benevole* ben)
{
    int rep = fread(ben, sizeof(t_benevole), 1, f) ;
    if (rep == 0)
        return FIN ;
    else
        return OK ;
}

int main (
int argc, char* argv[]
)
{
    t_benevole ben ;
    int rep ;
    FILE* f ;
    if (argc != 2)
    {
        printf("pas le bon nombre d'arguments\n") ;
        return EXIT_FAILURE ;
    }
    f = fopen(argv[1], "r") ;
    if (!f)
    {
        printf("pb a l'ouverture\n") ;
        return EXIT_FAILURE ;
    }
    rep = OK ;
    while (rep == OK)
    {
        rep = LireBenevole(f, &ben) ; // ici on doit passer une adresse
        AfficherBenevole(ben) ; // ici on doit passer une structure
    }
    fclose(f) ;
    return EXIT_SUCCESS ;
}
