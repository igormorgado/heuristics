#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

struct matrix {
    size_t order;
    int *data;
};

struct matrix * matrix_new          (size_t               order);

void            matrix_free         (struct matrix      * matrix);

struct matrix * matrix_from_vector  (int                * vector, 
                                     size_t               order
                                    );

struct matrix * matrix_random		(size_t               order,
									 int                  lower, 
									 int                  upper, 
									 double               connectivity);

int             matrix_get          (struct matrix      * matrix, 
                                     size_t               i,
                                     size_t               j
                                    );

int  *          matrix_getp         (struct matrix *matrix,
                                     size_t               i, 
                                     size_t               j);

void            matrix_set          (struct matrix      * matrix,
                                     size_t               i,
                                     size_t               j, 
                                     int                  e
                                    );

void            matrix_print        (struct matrix      * matrix);



#endif /* __MATRIX_H__ */

