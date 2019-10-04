#include "heur.h"


struct solution *
solution_new (size_t order)
{
	struct solution *s = malloc(sizeof *s);
	// The first node (0) is implicitly the first element
	// hence the solution array is order-1 in size;
	s->order = order-1;
	s->data = malloc(order * sizeof *(s->data));
	s->cost = WORSE_SOLUTION;
	s->valid = false;
	s->updated = false;
	return s;
}

void 
solution_init (struct solution * solution)
{
	for(size_t i = 0; i < solution->order; i++)
		solution->data[i] = i+1;
}


void
solution_free (struct solution *solution)
{
    if(solution != NULL) {
        if(solution->data != NULL) {
            free(solution->data);
        free(solution);
        }
    }
}

struct solution *
solution_new_shuffle(struct matrix *matrix)
{
	struct solution *S = solution_new(matrix->order);
    solution_init(S);
    solution_shuffle(S, S->order);
    solution_update(S, matrix);
    return S;
}



void
solution_print (struct solution * solution)
{
	printf("(");
	printf("%c", solution->valid ? ' ':'!');
	printf("%c", solution->updated ? ' ':'!');
	printf("%10d):\t", solution->cost); 
	for(size_t i = 0; i < solution->order; i++)
		printf("%d ", solution->data[i]);
	printf("\n");
}

void
solution_path_print (struct solution * solution, struct matrix *matrix)
{
	int a, b, c, i, cost;

	i = 0;
	cost = 0;

	a = 0;
	b = solution_get(solution, i++);
	c = matrix_get(matrix, a, b);
	cost += c;
	fprintf(stdout,"Cost %d->%d = %d (%d)\n", a, b, c, cost);
    fflush(stdout);

	while(b != solution->order) {
		a = b;
		b = solution_get(solution, i++);
		c = matrix_get(matrix, a, b);
        cost += c;
		fprintf(stdout,"Cost %d->%d = %d (%d)\n", a, b, c, cost);
        fflush(stdout);
	}
}

void 
solution_shuffle (struct solution *solution, size_t n)
{
	if (n > 1) 
	{
		for (size_t i = 0; i < n - 1; i++) 
		{
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          	int t = solution->data[j];
          	solution->data[j] = solution->data[i];
          	solution->data[i] = t;
		}
	}
	solution->updated = false;
}

int
solution_get (struct solution *solution, size_t n)
{
	return solution->data[n];
}

int
solution_cost (struct solution *solution)
{
	return solution->cost;
}

void
solution_update (struct solution *solution, struct matrix *matrix)
{
	int a, b, c, i, cost;

	i = 0;
	cost = 0;

	a = 0;
	b = solution_get(solution, i++);
	c = matrix_get(matrix, a, b);
	solution->valid = true;
    if(c == 0)
        solution->valid = false;

	cost += c;

#ifdef DEBUG
	printf("Cost %d->%d = %d (%d)\n", a, b, c, cost);
#endif
	while(b != solution->order) {
		a = b;
		b = solution_get(solution, i++);
		c = matrix_get(matrix, a, b);
		if(c == 0) {
#ifdef DEBUG
			printf("SOLUTION INVALID\n");
#endif
		 	solution->valid = false;
		}
		cost += c;
#ifdef DEBUG
		printf("Cost %d->%d = %d (%d)\n", a, b, c, cost);
#endif
	}
	solution->cost = cost;
	solution->updated = true;
}

void
solution_swap (struct solution *solution, 
			  size_t 		   a,
			  size_t 		   b)
{
#ifdef DEBUG
		printf("Swap %d<->%d\n", a, b);
#endif
	int t = solution->data[a];
	solution->data[a] = solution->data[b];
	solution->data[b] = t;
}


void
solution_copy (struct solution    * dst,
			   struct solution    * src)
{
	dst->order = src->order;
	dst->cost = src->cost;
	dst->valid = src->valid;
	dst->updated = src->updated;
	for(size_t i = 0; i<dst->order; i++)
		dst->data[i] = src->data[i];
}

struct solution *
solution_dup (struct solution * src)
{
	struct solution *dst = solution_new(src->order);
	solution_copy(dst, src);
	return dst;
}

struct solution *
solution_new_like(struct solution *src)
{
	struct solution *S = solution_new(src->order);
    return S;
}

size_t
solution_pick_random_elem(struct solution *solution)
{
    return rand() % solution->order;
}

void
solution_random_neighbor (struct solution *dst, 
                          struct solution *src)
{
    size_t pos_a = 0;
    size_t pos_b = 0;

    while(pos_a == pos_b) {
        pos_a = solution_pick_random_elem(src);
        pos_b = solution_pick_random_elem(src);
    }
    solution_copy(dst, src);
    solution_swap(dst, pos_a, pos_b);
}

