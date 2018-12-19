/*
 * inner.c
 *
 * Simple program for debugging practicals.
 *
 * authors: Raphaël Bleuse <raphael.bleuse@imag.fr> @ IUT2, Univ. Grenoble Alpes
 *          Cheng Liu <liu105@purdue.edu> @ Purdue University
 *
 * source: http://www.stat.purdue.edu/~liu105/STAT598G_lab.html
 *
 * date: 2017-01-05
 */

#include <stdio.h>
#include <stdlib.h>

#define VEC_SIZE 2

/* For 2 given vectors a and b of size n, compute the inner product. */
double inner(double a[], double b[], int size)
{
//	int i, res;
	int i ; double res = 0 ;

	for (i = 0; i < size; i++)
		res += a[i] * b[i];

	return res;
}

int main(void)
{
	int i,j=0; // j ;
	double res;
	double v[] = {1,2,3,4} ; // ajouté
	double a[2][VEC_SIZE];

	for (i = 0; i < VEC_SIZE; i++) {
		a[i][0] = v[j++];
		a[i][1] = v[j++];
	}

	res = inner(a[0], a[1], VEC_SIZE);

	printf("The inner product is %f\n", res);

	return EXIT_SUCCESS;
}
