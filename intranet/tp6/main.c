#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "entree_sortie.h"

#define MIROIR_HORIZONTAL   0
#define MIROIR_VERTICAL         1
#define ROTATION_90 0
#define ROTATION_180    1

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
void Degrade(unsigned char* image, int largeur, int hauteur)
//---------------------------------------------------------------------------
{
    int x, y ;
    int debutLigne ;
    for (y=0 ; y<hauteur; y++)
    {
        debutLigne = y * largeur ;  // petite optimisation
        for (x=0 ; x<largeur; x++)
            image[debutLigne +x] = x*256/largeur ; // on adapte le dégradé à la largeur
    }
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
    // memset(image, 255, taille) ;
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

//---------------------------------------------------------------------------
void Seuillage(unsigned char* image, int largeur, int hauteur, unsigned char seuil)
//---------------------------------------------------------------------------
{
    long int i ;
    long int taille = largeur * hauteur ;
    for (i=0; i<taille; i++)
        *(image+i) = (*(image+i) < seuil) ? 0 : 255 ; // version compacte que l'on peu éventuellement montrer
}

//------------------------------------------------------------------------
void Miroir(unsigned char* image, int largeur, int hauteur, char type)
//------------------------------------------------------------------------
{
    unsigned char pixelTemporaire ;
    long int iSource, iDest ;

    if (type == MIROIR_HORIZONTAL)
    {
        for (int y=0; y<=hauteur/2; y++)
            for (int x=0; x<largeur; x++)
            {
                iSource = y*largeur+x ;
                iDest = (hauteur-y-1)*largeur+x ;
                pixelTemporaire = image[iSource] ;
                image[iSource] = image[iDest] ;
                image[iDest] = pixelTemporaire ;
            }
    }
    else
    {
        for (int y=0; y<hauteur; y++)
            for (int x=0; x<=largeur/2; x++)
            {
                iSource = y*largeur+x ;
                iDest = y*largeur+(largeur-x-1) ;
                pixelTemporaire = image[iSource] ;
                image[iSource] = image[iDest] ;
                image[iDest] = pixelTemporaire ;
            }
    }
}

//------------------------------------------------------------------------
unsigned char* Rotation(unsigned char* image, int largeur, int hauteur, int angle)
//------------------------------------------------------------------------
{
    long int iSource, iDest ;
    unsigned char* image2 = CreerImage(largeur, hauteur) ;
    if (!image2)
        return NULL ;

    if (angle == ROTATION_90) // 90° clockwise
    {
        for (int y=0; y<hauteur; y++)
            for (int x=0; x<largeur; x++)
            {
                iSource = y*largeur+x ;
                iDest = x*hauteur+(hauteur-y-1) ;
                image2[iDest] = image[iSource] ;
            }
    }
    else if (angle == ROTATION_180)        // 90° anti-clockwise
    {
        for (int y=0; y<hauteur; y++)
            for (int x=0; x<largeur; x++)
            {
                iSource = y*largeur+x ;
                iDest = (hauteur-y-1)*largeur+(largeur-x-1) ;
                image2[iDest] = image[iSource] ;
            }
    }
    return image2 ;
}

//------------------------------------------------------------------------
int* Histogramme(unsigned char* image, int largeur, int hauteur)
//------------------------------------------------------------------------
{
    long int taille = largeur * hauteur ;
    long int i ;
    int *histo = malloc(256*sizeof(int)) ;  // calloc serait mieux car initialise la mémoire à zéro mais on ne l'a pas vu en cours
    if (!histo)             // on peut en parler en TP
        return NULL ;

    for (i=0; i<256; i++)
        *(histo+i) = 0 ;

    for (i=0; i<taille; i++)
        histo[*(image+i)]++ ;

    return histo ;
}

//------------------------------------------------------------------------
unsigned char* HistogrammeImage(int* histo, int hauteur)
//------------------------------------------------------------------------
{
    long int taille = 256 * hauteur ;
    long int i ;
    int col, ligne ;
    int maxBin = 0 ;
    int hauteurBinNormalise ;
    unsigned char* image = CreerImage(256, hauteur) ;

    for (col=0; col<256; col++)
    {
        if (histo[col] > maxBin)    // on cherche le bin ayant la fréquence d'apparition la plus grande
            maxBin = histo[col] ;
    }

    for (i=0; i<taille; i++)        // remplit l'image d'histogramme en blanc
        image[i] = 255 ;

    for (col=0; col<256; col++)
    {
        hauteurBinNormalise = histo[col]*hauteur/(float)maxBin + 0.5 ; // +0.5 fait un arrondi
        for (ligne=hauteur - hauteurBinNormalise; ligne<hauteur; ligne++)
            image[ligne*256+col] = 0 ;
    }

    return image ;
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

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
//---------------------------------------------------------------------------
// crée une image dégradé, la passe en négatif et la seuille
{
    unsigned char* image ;
    int largeur = 800 ;
    int hauteur = 50 ;

    image = CreerImage(largeur, hauteur);
    ImageBlanche(image, largeur, hauteur) ;
    EcrireImagePGM("image_blanche.pgm", image, largeur, hauteur) ;
    Degrade(image, largeur, hauteur) ;
    Negatif(image, largeur, hauteur) ;
    Seuillage(image, largeur, hauteur, 128) ;
    EcrireImagePGM("degrade.pgm", image, largeur, hauteur) ;
    AfficherImage("image_blanche.pgm") ;
    AfficherImage("degrade.pgm") ;

    free(image) ;
    return EXIT_SUCCESS ;
}

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
//---------------------------------------------------------------------------
// ouvre une image, lui applique un effet miroir
{
    unsigned char* image ;
    int largeur ;
    int hauteur ;

    image = LireImagePGM("guadalest.pgm" , &largeur, &hauteur) ;
    Miroir(image, largeur, hauteur, MIROIR_VERTICAL) ;
    EcrireImagePGM("miroir.pgm", image, largeur, hauteur) ;
    AfficherImage("miroir.pgm") ;

    free(image) ;
    return EXIT_SUCCESS ;
}

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
//---------------------------------------------------------------------------
// ouvre une image, effectue une rotation
{
    unsigned char* image ;
    unsigned char* imageRot ;
    int largeur ;
    int hauteur ;

    image = LireImagePGM("voiron.pgm" , &largeur, &hauteur) ;
//  imageRot = Rotation(image, largeur, hauteur, ROTATION_90) ;
//  EcrireImagePGM("rotation.pgm", imageRot, hauteur, largeur) ;  // ici on inverse largeut et hauteur
    imageRot = Rotation(image, largeur, hauteur, ROTATION_180) ;
    EcrireImagePGM("rotation.pgm", imageRot, largeur, hauteur) ;  // même largeur et hauteur
    AfficherImage("rotation.pgm") ;

    free(image) ;
    free(imageRot) ;
    return EXIT_SUCCESS ;
}
#endif

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
//---------------------------------------------------------------------------
// ouvre une image, calcule son histogramme des niveaux de gris et crée l'image de l'histogramme
{
    unsigned char* image ;          // image traitée
    unsigned char* imageHistogramme ;   // image de l'histogramme

    int* histogramme ;          // tableau histogramme
    int largeur ;
    int hauteur ;

    image = LireImagePGM("voiron.pgm" , &largeur, &hauteur) ;
    histogramme = Histogramme(image, largeur, hauteur) ;
    imageHistogramme = HistogrammeImage(histogramme, 150) ;
    EcrireImagePGM("histogramme.pgm", imageHistogramme, 256, 150) ;  // toujours largeur 256 pour l'histogramme
    AfficherImage("histogramme.pgm") ;

    free(image) ;
    free(histogramme) ;
    free(imageHistogramme) ;
    return EXIT_SUCCESS ;
}