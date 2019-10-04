#ifndef __SA_H__
#define __SA_H__

#include <math.h>

#include "heur.h"

struct simulated_annealing_state
{
    double T;       // Temperatura
    double t0;      // Initial temperature
    double a;       // Coef de resfriamento
    double eps;     // Epsilon checks
    size_t max_iter; // max iterations
};

double              sa_randf                (void);

double              sa_prob                 (struct simulated_annealing_state     sa, 
                                             double                               delta);

double              sa_acceptable           (struct simulated_annealing_state     sa, 
                                             double                               delta);

double              sa_initial_temperature  (struct matrix                      * M, 
                                             size_t                               evals);


struct solution *   sa_minimize             (struct simulated_annealing_state     sa,
                                             struct solution                    * S,
                                             struct matrix                      * M);

struct solution *   sa_maximize             (struct simulated_annealing_state     sa,
                                             struct solution                    * S,
                                             struct matrix                      * M);
#endif /* __SA_H__ */
