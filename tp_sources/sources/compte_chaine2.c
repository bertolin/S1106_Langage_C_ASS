#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
// compte le nombre d'occurrences d'une sous-chaine s dans une chaine S
// Version de Christophe Brouard - avril 2009

{
        int i,j,k,L,l,nb;
        char S[] = "ccc";
        char s[] = "cc";
        
        L=strlen(S);
        l=strlen(s);
        i=0;
        nb=0;

// Solution sans booléen
        while (i<L-l+1)
        {
                j=0;
                // on avance dans les deux chaines tant qu'il y a égalité
                k=i;
                while ((j<l) && (S[k]==s[j])) // le && est en fait un "et alors"
                {
                        j++;
                        k++;
                }
                // si on est à la fin de la sous-chaine on incremente le compteur
                if (j==l) nb++;
                i++; // on passe au caractere suivant
        }
        printf("%d occurrences\n",nb);
        return EXIT_SUCCESS ;
}

