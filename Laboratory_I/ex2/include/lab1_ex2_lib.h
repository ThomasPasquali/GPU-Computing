#ifndef LAB1_EX2_LIB
#define LAB1_EX2_LIB

#define STR(s) #s
#define XSTR(s) STR(s)
#define dtype double

// Put here the declaration of mu_fn and sigma_fn
dtype mu_fn(dtype* a, int len);
dtype sigma_fn(dtype* a, dtype mu, int len);

#endif
