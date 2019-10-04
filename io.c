#include "io.h"

/*
 * Read the matrix file as specified and store all distances in
 * a vector of ints.
 *
 * Returns the order of matrix as an integer, 0 on failure.
 *
 */
size_t 
read_matrix_file(char    *fname, 
                 int **p_vector_addr)
{
    /* Check if file exists */
    if(access(fname, F_OK) == -1) {
        
        perror(fname);
        return(0);
    }

    /* Try to open file */
    FILE *fd = fopen(fname, "r");
    if (fd == NULL) {
        perror(fname);
        return(0);
    }

    /* Read the first line as a string*/
    char line[BUFSIZ];
    if (fgets(line, sizeof line, fd) == NULL) {
        perror("fgets");
        return(0);
    }

    /* Find the order of matrix */
    size_t order;
    if (sscanf(line, "%zu", &order) != 1) {
        perror("sscanf");
        return(0);
    }

    /* Check for valid matrix ranks */
    if (order <= 0) {
        fprintf(stderr, "Error: Invalid matrix size %zu\n", order);
        return(0);
    }

    /* Allocates the array */
    int * t_vector = realloc(*p_vector_addr, order * order * sizeof *t_vector);
    if (t_vector == NULL) {
        perror("realloc");
        return(0);
    }
    *p_vector_addr = t_vector;

    int *vector = *p_vector_addr;

    /* Reads the elements */
    int b;
    for(size_t i=0; i < order; i++) {
        // Read the i-th line into line
        if (fgets(line, sizeof line, fd) == NULL) {
            perror("fgets");
            return(0);
        }

        /* Reads th j-th element of i-th line into the vector */
        char *elem_ptr = line;
        int elem;
        for (size_t j=0; j < order; j++) {
            if(sscanf(elem_ptr, "%d%n", &elem, &b) != 1) {
                perror("sscanf");
                return(0);
                break;
            }
            vector[order*i+j] = elem;
            elem_ptr += b;
        }
    }
    fclose(fd);
    
    return order;
}
