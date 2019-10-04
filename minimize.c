#include "main.h"

void
check_args(int argc, char *argv[])
{
    if ((argc < 2) || (argc > 4)) {
        printf("Usage: %s filename [seed] [order]\n", argv[0]);
        exit(0);
    }
}

void
init_seed(int argc, char *argv[])
{
    int seed = 0;               // Initial seed
    if (argc == 3)
        seed = atoi(argv[2]);
	if (seed < 0) 
		seed = time(0);
	srand(seed);
}

struct matrix *
init_cost_matrix(int argc, char *argv[])
{
    struct matrix *M;
    int order; 
    if(strcmp(argv[1], "random") == 0) {
        if(argc == 4) {
            order = atoi(argv[3]);
        } else {
            order = 10;
        }
        fprintf(stderr,"Creatin matrix order %d ", order);
        fflush(stderr);
        M = matrix_random(order, -10, 200, 1);
    } else {
        int *pvec = malloc(sizeof *pvec);
        order = read_matrix_file(argv[1], &pvec);
        M = matrix_from_vector(pvec, order);
        free(pvec); 
    }

    return M;
}


int
main(int   argc,
     char *argv[])
{

    double time;

    check_args(argc,argv);
    init_seed(argc, argv);
    struct matrix *M = init_cost_matrix(argc, argv);
    struct solution *S = solution_new(M->order);
		
	struct simulated_annealing_state sa = { .T = 0.0, 
                                            .t0 = 0.0,
                                            .a = 0.8, 
                                            .max_iter = 1000,
                                            .eps = 0.001,
                                          };

    sa.t0 = sa_initial_temperature(M, M->order);      // Initial temp

    solution_init(S);



    fprintf(stdout, "order, alpha, iter, eps, cost, time\n");
    fflush(stdout);




    for(size_t i = 0; i<30; i++) { 
        fprintf(stderr,".");
        fflush(stderr);
        solution_shuffle(S, S->order);
        solution_update(S, M);
        tic(&time, TIME_ms);
        sa_minimize(sa, S, M);
        tac(&time, TIME_ms);
        fprintf(stdout, "%d,%f,%d,%f,%d,%f\n",
                S->order+1, 
                sa.a, 
                sa.max_iter, 
                sa.eps, 
                solution_cost(S), 
                time);
        fflush(stdout);
        if(S->order < 53) {
            solution_print(S);
            fflush(stdout);
        }
    }
    fprintf(stderr,"\n");
    fflush(stderr);


    /*
     * Closing
     */
	solution_free(S);
    matrix_free(M);
    return 0;
}
