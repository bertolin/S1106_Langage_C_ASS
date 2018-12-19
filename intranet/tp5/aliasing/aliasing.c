/*
 * aliasing.c
 *
 * Simple program for debugging practicals.
 *
 * authors: Raphaël Bleuse <raphael.bleuse@imag.fr> @ IUT2, Univ. Grenoble Alpes
 *          John Donners <john.donners@sara.nl>
 *
 * source: http://www.training.prace-ri.eu/training_material/
 *
 * date: 2017-01-05
 */

#include <stdio.h>
#include <stdlib.h>

#define NELEM 10

void init_array(int array_size, int array[]);
void print_array(int array_size, int array[]);
void square_array(int array_size, int array[]);

int main(void)
{
	int indx;
	int *array1, *array2, *diff;

	/* allocate memory for each array */
	array1 = (int *) malloc(NELEM * sizeof(int));
	array2 = (int *) malloc(NELEM * sizeof(int));
	diff = (int *) malloc(NELEM * sizeof(int));

	/* initialize array1 */
	init_array(NELEM, array1);
	for (indx = 0; indx < NELEM; indx++)
		array1[indx] = indx + 2;

	/* print the elements of array1 */
	printf("The content of array1 is:\n");
	print_array(NELEM, array1);

	/* copy array1 to array2 */
	array2 = array1;

	/* square all elements of array2 */
	square_array(NELEM, array2);

	/* compute differences between elements of array2 and array1 */
	for (indx = 0; indx < NELEM; indx++)
		diff[indx] = array2[indx] - array1[indx];

	/* print the computed differences */
	printf("The differences in the elements of array2 and array1 are:\n");
	print_array(NELEM, diff);

	/* release memory for each array */
	free(array1);
	free(array2);
	free(diff);

	return EXIT_SUCCESS;
}

void init_array(int array_size, int array[])
{
	int indx;

	for (indx = 0; indx < array_size; indx++)
		array[indx] = indx + 1;
}

void print_array(int array_size, int array[])
{
	int indx;

	printf("[  ");
	for (indx = 0; indx < array_size; indx++) {
		printf("%d  ", array[indx]);
	}
	printf("]\n\n");
}

void square_array(int array_size, int array[])
{
	int indx;

	for (indx = 0; indx < array_size; indx++)
		array[indx] *= array[indx];
}
