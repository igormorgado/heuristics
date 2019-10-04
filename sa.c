#include "sa.h"


double sa_randf(void)
{
    return (double)rand()/RAND_MAX;
}

double sa_prob(struct simulated_annealing_state sa, double delta)
{
	return exp((-delta)/sa.T);
}

double sa_acceptable(struct simulated_annealing_state sa, double delta)
{
    return (sa_randf() < sa_prob(sa, delta));
}

double
sa_initial_temperature(struct matrix *M, size_t evals)
{
    struct solution *S = solution_new(M->order);
    struct solution *S_prime = solution_new_like(S);  // Initialize only
	solution_init(S);
    solution_shuffle(S, S->order);
    solution_update(S, M);
    int T = solution_cost(S);
    for(size_t i = 0; i < evals; i++)
    {
        solution_random_neighbor(S_prime, S);
        solution_update(S_prime, M);
        if (solution_cost(S_prime) > T)
            T = solution_cost(S_prime);
    }

    solution_free(S);
    solution_free(S_prime);
    return (double)T;
}

struct solution * 
sa_minimize(struct simulated_annealing_state sa,
            struct solution * S,
            struct matrix *M)
{
    // SA assert
    if (sa.a >= 1) {
        perror("Resfriamento > = 1\n");
        return NULL;
    }

    struct solution *S_star = solution_dup(S);        // To start S is the best solution
    struct solution *S_prime = solution_new_like(S);  // Initialize only
    size_t iter_t = 0;                                // Temprature iteration counter
    sa.T = sa.t0;                                     // Initialize temperature as hothot

    double delta;

    while (sa.T > sa.eps) {
        while(iter_t < sa.max_iter) {
            iter_t++;
            solution_random_neighbor(S_prime, S);     // Generates a neighbor 
            solution_update(S_prime, M);              // Evaluate neighbor cost
            delta = (double)(solution_cost(S_prime) - solution_cost(S));
            if (delta < 0) {
                solution_copy(S, S_prime);
                if (solution_cost(S_prime) < solution_cost(S_star)) {
                    solution_copy(S_star, S_prime);
                }
            } else {
                if(sa_acceptable(sa, delta)) {
                    solution_copy(S, S_prime);
                } 
            }
        }
        sa.T *= sa.a;
        iter_t = 0;
    }

    solution_copy(S, S_star);
    solution_free(S_star);
    solution_free(S_prime);

    return S;
}

struct solution * 
sa_maximize(struct simulated_annealing_state sa,
            struct solution * S,
            struct matrix *M)
{
    // SA assert
    if (sa.a >= 1) {
        perror("Resfriamento > = 1\n");
        return NULL;
    }

    struct solution *S_star = solution_dup(S);        // To start S is the best solution
    struct solution *S_prime = solution_new_like(S);  // Initialize only
    size_t iter_t = 0;                                // Temprature iteration counter
    sa.T = sa.t0;                                     // Initialize temperature as hothot

    double delta;

    while (sa.T > sa.eps) {
        while(iter_t++ < sa.max_iter) {
            solution_random_neighbor(S_prime, S);     // Generates a neighbor 
            solution_update(S_prime, M);              // Evaluate neighbor cost
            delta = (double)(solution_cost(S_prime) - solution_cost(S));

            if (delta > 0) {
                solution_copy(S, S_prime);
                if (solution_cost(S_prime) > solution_cost(S_star)) {
                    solution_copy(S_star, S_prime);
                }
            } else {
                if(sa_acceptable(sa, delta)) {
                    solution_copy(S, S_prime);
                } 
            }
        }
        sa.T *= sa.a;                   // Cooldown sliglty
        iter_t = 0;
    }

    solution_copy(S, S_star);
    solution_free(S_star);
    solution_free(S_prime);

    return S;
}

