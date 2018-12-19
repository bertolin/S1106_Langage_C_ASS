#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "entree_sortie.h"

//---------------------------------------------------------------------------
void AfficherImage(char* nomFichier)
//---------------------------------------------------------------------------
{
    char commande[128] ;
//  sprintf(commande,"xv %s", nomFichier) ;
    sprintf(commande,"gwenview %s", nomFichier) ;
    system(commande) ;
    printf("Affichage %s\n", nomFichier) ;
}

//---------------------------------------------------------------------------
unsigned char* CreerImage(int largeur, int hauteur)
//---------------------------------------------------------------------------
{
    return malloc(largeur * hauteur * sizeof(char)) ; // * sizeof(char) pour prendre l'habitude
}

//---------------------------------------------------------------------------
void ImageBlanche(unsigned char* image, int largeur, int hauteur)
//---------------------------------------------------------------------------
{
    long int i ;
    long int taille = largeur * hauteur ;
    for (i=0; i<taille; i++)
        image[i] = 255 ; // un peu de notation tableau

    // ou bien :
    // memset(image, 255, taille) ; // memset est une fonction de string.h
}

//---------------------------------------------------------------------------
void Negatif(unsigned char* image, int largeur, int hauteur)
//---------------------------------------------------------------------------
{
    long int i ;
    long int taille = largeur * hauteur ;
    for (i=0; i<taille; i++)
        *(image+i) = 255 - *(image+i) ; // un peu de notation pointeur
}

#ifdef POUR_NE_GARDER_Q_UN_SEUL_MAIN
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
//---------------------------------------------------------------------------
// lit un fichier image
// en crée une copie
{
    int largeur, hauteur ;
    unsigned char* image ;

    image = LireImagePGM("guadalest.pgm" , &largeur, &hauteur) ;
    if (image)
    {
        EcrireImagePGM("guadalest_copie.pgm", image, largeur, hauteur) ;
        AfficherImage("guadalest_copie.pgm") ;
        free(image) ;
        return EXIT_SUCCESS ;
    }
    else
        return EXIT_FAILURE ;
}
#endif

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
//---------------------------------------------------------------------------
// crée une image blanche, la passe en négatif
{
    unsigned char* image ;
    int largeur = 800 ;
    int hauteur = 50 ;

    image = CreerImage(largeur, hauteur);
    ImageBlanche(image, largeur, hauteur) ;
    EcrireImagePGM("image_blanche.pgm", image, largeur, hauteur) ;
    Negatif(image, largeur, hauteur) ;
    EcrireImagePGM("negatif.pgm", image, largeur, hauteur) ;
    AfficherImage("image_blanche.pgm") ;
    AfficherImage("negatif.pgm") ;

    free(image) ;
    return EXIT_SUCCESS ;
}
