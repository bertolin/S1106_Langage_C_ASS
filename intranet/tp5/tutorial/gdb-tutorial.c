/*
 * gdb-tutorial.c
 *
 * Simple program for debugging practicals.
 *
 * authors: Raphael Bleuse <raphael.bleuse@imag.fr> @ IUT2, Univ. Grenoble Alpes
 *          Matthieu Moy <Matthieu.Moy@imag.fr> @ Ensimag, Grenoble INP
 *
 * date: 2017-01-20
 */

#include <stdio.h>
#include <unistd.h>

void f(void);

/*
 * Ce fichier est un tutoriel pas a pas pour utiliser le debogueur cgdb. Un
 * debogueur est un outil precieux pour comprendre ce qui ne va pas dans vos
 * programmes. Les quelques minutes que vous allez passer a apprendre a
 * l'utiliser seront largement rentabilisees par la suite !
 *
 * Commencez par compiler le programme. Pour pouvoir utiliser gdb, il faut
 * utiliser l'option -g de gcc a la compilation :
 *
 * $ gcc -std=gnu11 -Wall -g -O0 gdb-tutorial.c -o gdb-tutorial
 *
 * Vous pouvez lancer l'executable gdb-tutorial dans cgdb en ligne de commande
 * comme ceci :
 *
 * $ cgdb ./gdb-tutorial
 *
 * Commencons par quelque chose de simple : demarrer le programme. Saisissez
 * "run", ou simplement la lettre "r" dans la ligne de commande gdb.
 */

int main (void)
{
	unsigned i;
	short int j;
	int *ptr = NULL; /* NULL est une adresse invalide : il est interdit de
	                  * dereferencer (d'acceder a la variable pointee) un
	                  * pointeur NULL */

	nice(19); /* rend le programme moins prioritaire pour ne pas surcharger
	           * la machine pendant les tests sur les boucles infinies */

	printf("Bonjour !\n");
	printf("Je vais faire un acces memoire interdit.\n");

	/*
	 * La ligne suivante va engendrer un "Segmentation fault".
	 * Le debogueur va s'arreter sur cette ligne.
	 */

	*ptr = 0;

	/*
	 * Bien : le bogue etait facile a trouver.
	 * Commentez la ligne ci-dessus pour eliminer le probleme.
	 * Recompilez, et lisez la suite.
	 *
	 * Nous allons maintenant faire une execution pas a pas. Il faut
	 * commencer par donner a gdb un endroit du code ou nous voulons nous
	 * arreter : un point d'arret (break point).
	 *
	 * Dans la ligne de commande gdb, saisissez :
	 * "break gdb-tutorial.c:74"
	 * pour s'arreter a la ligne 74 de gdb-tutorial.c. Quand il n'y a qu'un
	 * fichier, il est possible d'omettre le nom du fichier :
	 * "b 74"
	 */

	printf ("On avance ...\n"); /* Ajoutez un point d'arret ici. */

	/*
	 * Maintenant, vous devriez avoir votre programme arrete sur la ligne
	 * qui precede. Tapez "next", ou simplement "n" pour avancer dans
	 * l'execution du programme, plusieurs fois.
	 * Le debogueur affiche la prochaine instruction qui sera executee.
	 * Petite astuce : apres avoir tape "n" une fois, il suffit d'appuyer
	 * sur Entree pour refaire un "next". Cela fonctionne pour toutes les
	 * commandes : appuyer sur Entree repete la derniere commande saisie.
	 */

	printf ("On avance encore ...\n");
	printf ("On avance encore un peu ...\n");
	printf ("On avance encore un peu ...\n");
	printf ("On avance une derniere fois ...\n");
	printf ("Et voila !\n");

	/*
	 * Il y a deux commandes pour executer un programme pas a pas :
	 * - "next", pour executer completement l'instruction suivante
	 * - "step", pour "rentrer" dans la fonction si l'instruction suivante
	 *   est un appel de fonction.
	 *
	 * Essayez successivement "step" et "next" sur les lignes suivantes.
	 */

	f();
	f();
	f();

	/*
	 * Bien. L'execution pas a pas est pratique, mais devient penible quand
	 * il y a beaucoup de code a executer. Par exemple, la boucle suivante
	 * prendrait trop de temps, on veut la sauter.

	 * Pour cela, ajoutez un point d'arret sur la ligne apres le corps de
	 * la boucle, puis faites "continue" (ou juste "c") dans gdb.
	 */

	j = 0;
	for (i = 0; i <= 1000; ++i) {
		j = j + i;
	}
	printf("Fin de la boucle\n"); /* Ajoutez le point d'arret ici. */

	/*
	 * Il est bien sur possible de visualiser le contenu d'une variable. La
	 * commande utilisee est "print", ou simplement "p". L'affichage d'une
	 * variable peut etre maintenu avec "display" (attention, "d" n'est pas
	 * un raccourci pour "display").
	 *
	 * Par exemple, faites maintenant "display i", puis executez la boucle
	 * suivante pas a pas. Faites "p j" pour connaitre la valeur de j.
	 *
	 * L'affichage maintenu d'une variable peut etre stoppe avec
	 * "undisplay".
	 */

	for (i = 1; i <= 1000; i = i * 2) {
		j = j + i;
	}

	/*
	 * Il est aussi possible d'afficher des expressions C un peu plus
	 * complexes. Essayez par exemple :

	 * (gdb) p i+j
	 * (gdb) p &i
	 * (gdb) p &j
	 * (gdb) p dire_bonjour("Monsieur")
	 * (gdb) p quarante_deux()
	 *
	 * (Dans les derniers cas, gdb va effectivement appeler les fonctions
	 * dire_bonjour et quarante_deux, definies plus bas.)
	 *
	 * Nous pouvons aussi nous amuser un peu avec les pointeurs. Essayez:
	 *
	 * (gdb) p &i
	 * $2 = (unsigned int *) 0xbf9bfde8
	 *
	 * La valeur 0xbf9bfde8, adresse de i, sera a priori differente chez
	 * vous. Affichez maintenant l'expression *(unsigned int *)0xbf9bfde8
	 * (en remplacant 0xbf9bfde8 par la valeur que vous avez eu ci-dessus).
	 * Vous devriez avoir 1024, qui est bien la valeur de i.
	 */

	printf ("i=%i\n", i);

	/*
	 * Une derniere chose : il arrive que le programme parte dans une
	 * boucle infinie, et nous voudrions savoir ou est cette boucle.
	 *
	 * Rien de plus simple : lancez le programme ("c" pour "continue"),
	 * puis tapez Control-C pour arreter son execution et reprendre la main
	 * dans gdb.
	 *
	 * Utilisez cette technique pour identifier laquelle de ces boucles est
	 * une boucle infinie.
	 */

	j = 1;
	while (j > 0) {
		++j;
	}

	i = 10;
	while (i >= 0) {
		--i;
	}

	i = 0; j = 0;
	while (i == j) {
		++i; ++j;
	}

	/*
	 * Voila, vous avez termine et vous savez a peu pres tout ce que vous
	 * devez savoir pour une utilisation courante.
	 *
	 * Les plus curieux pourront lire le manuel complet :
	 * http://sourceware.org/gdb/onlinedocs/
	 */
}

void f(void)
{
	/* Vous voila dans le corps de la fonction f. Vous pouvez executer les
	 * deux prochains printf avec "next", ou bien terminer l'appel de la
	 * fonction courante avec "finish".*/
	printf("Appel de f()\n");
	printf("Fin de f()\n");
}

void dire_bonjour(char *nom)
{
	printf("Bonjour, %s\n", nom);
}

int quarante_deux(void)
{
	return 42;
}
