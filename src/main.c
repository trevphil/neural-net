#include <stdio.h>
#include "matrix.h"
#include "vector.h"

int main(int argc, char **argv) {
	Matrix *m = identity_matrix(5);
	printf("%s\n\n", "An example of a matrix...");
	print_matrix(m);
	free_matrix(m);
	
	Vector *v = make_vector(5);
	for (int i = 0; i < 5; i++) vector_set(v, i, i);
	printf("\n\n%s\n\n", "An example of a vector...");
	print_vector(v);
	free_vector(v);
	return 0;
}
