#ifndef FIR_H
#define FIR_H

#include <inttypes.h>

typedef float fp32_t;

struct fir_t
{
  const fp32_t* coeffs;
  uint32_t coeffs_len;
  volatile uint16_t* buf;
  uint32_t buf_len; 
};

uint16_t fir_convolve(struct fir_t* fir, uint32_t pos);

#endif /* FIR_H */
