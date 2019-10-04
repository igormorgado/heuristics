#ifndef __HEUR_H__
#define __HEUR_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "defs.h"
#include "matrix.h"

struct solution {
    size_t order;
    size_t pos;
    int cost;
    bool valid;
    bool updated;
    int *data;
};

struct solution *   solution_new             (size_t               order);

void                solution_init            (struct solution    * solution);

void                solution_free            (struct solution    * solution);


struct solution *   solution_new_shuffle     (struct matrix      * matrix);

void                solution_print           (struct solution    * solution);

void                solution_path_print      (struct solution    * solution,
                                              struct matrix      * matrix);

void                solution_shuffle         (struct solution    * solution, 
                                              size_t               n);

int                 solution_get             (struct solution    * solution, 
                                              size_t               n);

void                solution_update          (struct solution    * solution,
                                              struct matrix      * matrix);

int                 solution_cost            (struct solution    * solution);

void                solution_swap            (struct solution    * solution, 
                                              size_t               a,
                                              size_t               b);

void                solution_copy            (struct solution    * src,
                                              struct solution    * dst);

struct solution *   solution_dup             (struct solution    * src);

struct solution *   solution_new_like        (struct solution    * src);

void                solution_random_neighbor (struct solution   * dst,
                                              struct solution   * src);

#endif /* __HEUR_H__ */
