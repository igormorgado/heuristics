#ifndef __DEFS_H__
#define __DEFS_H__

#include <limits.h>

#ifndef PROBLEM
#define PROBLEM 0
#endif

/*
 * Problem 0 == Minimization problem
 * Problem 1 == Maximization problem
 */
#if PROBLEM == 0 
#define WORSE_SOLUTION INT_MAX
#else
#define WORSE_SOLUTION INT_MIN
#endif


#endif /* __DEFS_H__ */
