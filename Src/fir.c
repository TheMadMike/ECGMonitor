#include "fir.h"

uint16_t fir_convolve(struct fir_t* fir, uint32_t pos)
{ 
    uint32_t buf_idx = pos; 
    fp32_t result = 0.0f;

    for(uint32_t c_idx = fir->coeffs_len; c_idx != 0 ; --c_idx) {
        result += (fir->buf[buf_idx] * fir->coeffs[c_idx - 1]);
        buf_idx = (buf_idx + 1) % fir->buf_len;
    }   

    return (uint16_t) result;
}
