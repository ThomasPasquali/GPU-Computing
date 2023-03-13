#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define NPROBS 8

#define LEN 15
#define N 5
#define M 5


#define PRINT_RESULT_VECTOR( V, NAME ) {    \
    printf("%2s: ", NAME);                  \
    for (int i=0; i<LEN; i++)               \
        printf("%4d ", V[i]);               \
    printf("\n");                           \
}

#define PRINT_RESULT_MATRIX(MAT, NAME) {    \
    printf("%2s matrix:\n\t", NAME);        \
    for (int i=0; i<N; i++) {               \
        for (int j=0; j<M; j++)             \
            printf("%4d ", MAT[i*M+j]);     \
        printf("\n\t");                     \
    }                                       \
    printf("\n");                           \
}

// -------- uncomment these two lines when solutions are published --------
// #include "../../solutions/lab1_sol.cu"
// #define RESULTS
// ------------------------------------------------------------------------

#ifndef SOLUTION_STACKVEC_1
#define SOLUTION_STACKVEC_1 { }
#endif

#ifndef SOLUTION_HEAPVEC_1
#define SOLUTION_HEAPVEC_1 { }
#endif

#ifndef SOLUTION_HEAPVEC_2
#define SOLUTION_HEAPVEC_2 { }
#endif

#ifndef SOLUTION_STACKVEC_2
#define SOLUTION_STACKVEC_2 { }
#endif

#ifndef SOLUTION_STACKMAT_1
#define SOLUTION_STACKMAT_1 { }
#endif

#ifndef SOLUTION_HEAPMAT_1
#define SOLUTION_HEAPMAT_1 { }
#endif

#ifndef SOLUTION_HEAPMAT_2
#define SOLUTION_HEAPMAT_2 { }
#endif

#ifndef SOLUTION_STACKMAT_2
#define SOLUTION_STACKMAT_2 { }
#endif

void computec1(int* c1, int* a, int* b, int len) {
    for (int i = 0; i < len; ++i) {
        c1[i] = a[i] + b[i];
    }
}

int* computec2(int* a, int* b, int len) {
    int* c2 = (int*)malloc(len * sizeof(int));
    for (int i = 0; i < len; ++i) {
        c2[i] = a[i] + b[i];
    }
    return c2;
}

/* int* computeCstack(int* a, int* b, int len) {
    int c[len];
    for (int i = 0; i < len; ++i) {
        c[i] = a[i] + b[i];
    }
    return c;
} */

void computeC1(int* C1, int* A, int* B) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            int ij = i * M + j;
            C1[ij] = A[ij] + B[ij];
        }
}

int* computeC2(int* A, int* B) {
    int* C2 = (int*)malloc(N * M * sizeof(int));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            int ij = i * M + j;
            C2[ij] = A[ij] + B[ij];
        }
    return C2;
}

int main(void) {
    // ---------- for timing ----------
    float CPU_times[NPROBS];
    for (int i=0; i<NPROBS; i++)
        CPU_times[i] = 0.0;
    struct timeval temp_1, temp_2;
    // --------------------------------

#ifdef RESULTS
    printf("You are now running the \x1B[31mSOLUTION CODE\x1B[37m:\n");
#else
    printf("You are now running \x1B[31mYOUR CODE\x1B[37m:\n");
#endif
    // ---------------------- Stack vectors 1 ----------------------
    /* Generate three stack vectors a, and b of length "LEN" such
     * that for each i in {0, 1, ... LEN-1} a[i] = i, b[i] = 100 * i.
     * Then compute the vector c = a + b.
     */

#ifdef RESULTS
        SOLUTION_STACKVEC_1
        PRINT_RESULT_VECTOR(c, "c")
#else
    int a[LEN];
    int b[LEN];
    int c[LEN];
    for (int i = 0; i < LEN; ++i) {
        a[i] = i;
        b[i] = 100 * i;
        c[i] = a[i] + b[i];
    }
    PRINT_RESULT_VECTOR(c, "c");
#endif
    // ---------------------- Heap vectors 1 -----------------------
    /* Compute the same result as c but in a heap vector c1 allocated
     * in the main but computed in an extern function.
     */
#ifdef RESULTS
    SOLUTION_HEAPVEC_1
    PRINT_RESULT_VECTOR(c1, "c1")
#else
    int* c1 = (int*)malloc(LEN * sizeof(int));
    computec1(c1, a, b, LEN);
    PRINT_RESULT_VECTOR(c1, "c1");
    free(c1);

#endif
    // ---------------------- Heap vectors 2 -----------------------
    /* Compute the same result as c and c1 in a heap vector c2
     * also allocated in the extern function
     */
#ifdef RESULTS
    SOLUTION_HEAPVEC_2
    PRINT_RESULT_VECTOR(c2, "c2")
#else
    int* c2 = computec2(a, b, LEN);
    PRINT_RESULT_VECTOR(c2, "c2");
    free(c2);


#endif
    // ---------------------- Stack vectors 2 ----------------------
    /* Is it possible to compute the c vector as a stack vector of
     * the extern function and then return it to the main?
     */
#ifdef RESULTS
    SOLUTION_STACKVEC_2
#else
    // int* cStack = computeCstack(a, b, LEN);
    // PRINT_RESULT_VECTOR(c2, "cStack");

#endif


    /* Do now the same 4 previous exercises but with the three
     * matrices A, B, C of N rows and M columns where:
     *   1) A[i][j] = i + j
     *   2) B[i][j] = (i + j) * 100
     *   3) C = A + B
     *
     * What are the differences when you change from vectors to
     * matrices?
     */
    // --------------------- Stack matrices ----------------------
#ifdef RESULTS
        SOLUTION_STACKMAT_1
        PRINT_RESULT_MATRIX(((int*)C), "C")
#else
    int A[N * M];
    int B[N * M];
    int C[N * M];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            int ij = i * M + j;
            A[ij] = i + j;
            B[ij] = (i + j) * 100;
            C[ij] = A[ij] + B[ij];
        }
    PRINT_RESULT_MATRIX(((int*)C), "C")

#endif

    // --------------------- Heap matrices -----------------------
#ifdef RESULTS
        SOLUTION_HEAPMAT_1
        PRINT_RESULT_MATRIX(C1, "C1")
#else
    int* C1 = (int*)malloc(N * M * sizeof(int));
    computeC1(C1, A, B);
    PRINT_RESULT_MATRIX(C1, "C1");
    free(C1);

#endif

    // --------------------- Heap matrices -----------------------
#ifdef RESULTS
        SOLUTION_HEAPMAT_2
        PRINT_RESULT_MATRIX(C2, "C2")
#else
    int* C2 = computeC2(A, B);
    PRINT_RESULT_MATRIX(C2, "C2");
    free(C2);

#endif

    // --------------------- Stack matrices ----------------------
#ifdef RESULTS
        SOLUTION_STACKMAT_2
#else
   


#endif

    for (int i=0; i<NPROBS; i++) {
        printf("Problem %d runs in %9.8f CPU time\n", i, CPU_times[i]);
    }
    printf("\n");

    return(0);
}
