#include "matrix.h"

struct matrix * 
matrix_from_vector(int *vector, size_t order)
{
    struct matrix *matrix = malloc(sizeof *matrix);
    matrix->order = order;
    matrix->data = malloc(order * order * sizeof *(matrix->data));
    for (size_t i = 0; i < order*order; i++) {
        matrix->data[i] = vector[i];
    }
    return matrix;
}

struct matrix *
matrix_new(size_t order)
{
    struct matrix *matrix = malloc(sizeof *matrix);
    matrix->order = order;
    matrix->data = malloc(order * order * sizeof *(matrix->data));
    return matrix;
}

struct matrix * 
matrix_random(size_t order, int lower, int upper, double connectivity)
{
	int val;
	struct matrix *M = matrix_new(order);
	for(size_t i = 0; i < order; i++) {
		for(size_t j = 0; j < order; j++) {
			if (i == j) {
				matrix_set(M, i, j, 0);
				continue;
			}
			if ( (((double)rand())/RAND_MAX) < connectivity )
				val = (rand() % (upper - lower + 1)) + lower; 
			else
				val = 0;
			matrix_set(M, i, j, val);
		}
	}
    // Set direct conection from first tto last very expensive
    //matrix_set(M, 0, order-1, (order/2)*upper);

	return M;
}

void
matrix_free(struct matrix *matrix)
{
    if(matrix != NULL) {
        if(matrix->data != NULL) {
            free(matrix->data);
        free(matrix);
        }
    }
}

void
matrix_print(struct matrix *matrix)
{
	printf("\t");
	for(size_t i =0; i < matrix->order; i++)
		printf("%6d\t", i);
	printf("\n");

    for(size_t i = 0; i < matrix->order; i++) {
		printf("%6d\t", i);
        for(size_t j = 0; j < matrix->order; j++) {
            printf("%6d\t", matrix->data[i * (matrix->order) + j]);
        }
        printf("\n");
    }
}

int
matrix_get(struct matrix *matrix, size_t i, size_t j)
{
    return matrix->data[i * (matrix->order) + j];
}

void
matrix_set(struct matrix * matrix, size_t i, size_t j, int e)
{
    matrix->data[i * (matrix->order) + j] = e;
}

int *
matrix_getp(struct matrix *matrix, size_t i, size_t j)
{
    return &(matrix->data[i * (matrix->order) + j]);
}


