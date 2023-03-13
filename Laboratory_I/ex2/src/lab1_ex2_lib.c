#include "../include/lab1_ex2_lib.h"

// Put here the implementation of mu_fn and sigma_fn

dtype mu_fn(dtype* a, int len) {
  dtype sum = 0;
  for (int i = 0; i < len; ++i) sum += a[i];
  return sum / len;
}

dtype sigma_fn(dtype* a, dtype mu, int len) {
  dtype sum = 0, tmp;
  for (int i = 0; i < len; ++i) {
    tmp = a[i] - mu;
    sum += tmp * tmp;
  }
  return sum / len;
}
