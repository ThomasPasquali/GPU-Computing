#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#include "include/lab1_ex2_lib.h"
// NOTE: dtype is a macro type defined in 'include/lab1_ex2_lib.h'
//          also, the functions mu_fn and sigma_fn are defined in 'include/lab1_ex2_lib.h'


// -------- uncomment these seven lines when solutions are published --------
// #include "../../solutions/lab1_sol.cu"
// #define RESULTS
// #ifdef RESULTS
// #include "../../solutions/lab1_ex2_lib_sol.c"
//     MU_SOL
//     SIGMA_SOL
// #endif
// ------------------------------------------------------------------------

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: lab1_ex2 n\n");
        return(1);
    }

    printf("argv[0] = %s\n", argv[1]);

    int n = atoi(argv[1]), len;
    dtype *a, *b, *c;

    printf("n = %d\n", n);
    printf("dtype = %s\n", XSTR(dtype));

    /* Generate now two vectors a and b of size (2^n) and fill them with random integers
     *  in the range [-(2^11), (2^11)]. After this, compute the vector sum c = a + b (for
     *  all i in [0, (2^n)-1] c[i] = a[i] + b[i]).
     *
     * Other tasks:
     *      1) compute the CPU time
     *      2) change now the dtype form 'int' to 'double' (go in include/lab1_ex2.h)
     *          and observe how the computation time changes
     *
     * NOTE:
     * for random generation of integers in [-(2^11), (2^11)] use: "rand()/(1<<11)"
     * for random generation of doubles use: "(double)rand()/((double)RAND_MAX)"
     */

#ifdef RESULTS
    EX2_SOLUTION
#else
    //len = (int)pow(2.0, (double)n);
    len = 1; for (int i = 0; i < n; ++i) len *= 2;
    printf("len: %d\n", len);
    a = malloc(len * sizeof(dtype));
    b = malloc(len * sizeof(dtype));
    c = malloc(len * sizeof(dtype));

    srand(time(NULL));
    for(int i = 0; i < len; ++i) {
        a[i] = rand()/(1<<11);
        b[i] = rand()/(1<<11);
    }

    struct timeval stop, start;
    gettimeofday(&start, NULL);
    
    for(int i = 0; i < len; ++i) {
        c[i] = a[i] + b[i];
    }

#endif

    /*  Here we compute the vectors' mean and variance; these functions must be implemented inside
     *   of the library "src/lab1_ex2.c" (and their headers in "include/lab1_ex2.h").
     *
     * Given a vector v := [v_1, ... v_n] his mean mu(v) is defined as: (v_1 + ... + v_n)/n
     *   his variance sigma(v) as: ( (v_1 - mu(v))^2 + ... + (v_n - mu(v))^2 ) / (n)
     */
    double mu_a = 0.0, mu_b = 0.0, mu_c = 0.0, sigma_a = 0.0, sigma_b = 0.0, sigma_c = 0.0;

#ifdef RESULTS
    mu_a = mu_fn_sol(a, len);
    mu_b = mu_fn_sol(b, len);
    mu_c = mu_fn_sol(c, len);
    sigma_a = sigma_fn_sol(a, mu_a, len);
    sigma_b = sigma_fn_sol(b, mu_b, len);
    sigma_c = sigma_fn_sol(c, mu_c, len);
#else
    mu_a = mu_fn(a, len);
    mu_b = mu_fn(b, len);
    mu_c = mu_fn(c, len);
    sigma_a = sigma_fn(a, mu_a, len);
    sigma_b = sigma_fn(b, mu_b, len);
    sigma_c = sigma_fn(c, mu_c, len);
    
    gettimeofday(&stop, NULL);
    printf("Time elapsed: %lu us\n", ((stop.tv_sec - start.tv_sec) * 1e6 + stop.tv_usec - start.tv_usec));

#endif

    printf(" %10s | %10s | %10s |\n", "v name", "mu(v)", "sigma(v)");
    printf(" %10s | %10f | %10f |\n", "a", mu_a, sigma_a);
    printf(" %10s | %10f | %10f |\n", "b", mu_b, sigma_b);
    printf(" %10s | %10f | %10f |\n", "c", mu_c, sigma_c);

    char* mu_test = ((fabs(mu_a + mu_b - mu_c) < 0.001) && mu_c != 0.0)? "\x1B[32mDONE!\x1B[37m" : "\x1B[31mERROR!\x1B[37m";
    printf("\nMEAN TEST (|mu(c) - (mu(a) + mu(b))| < 0.001?): \t %s\n", mu_test);

    free(a);
    free(b);
    free(c);

    return(0);
}
