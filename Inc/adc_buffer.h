#ifndef __ADC_BUFFER_H
#define __ADC_BUFFER_H

#include <inttypes.h>
#include <stdbool.h>

#define ADC_BUF_LEN 512UL

extern volatile uint16_t adc_buffer[ADC_BUF_LEN];
extern volatile uint32_t adc_buffer_last_index;
extern volatile uint32_t adc_buffer_curr_index;

uint16_t adcbuf_get_next_blocking();
_Bool adcbuf_try_push(uint16_t value);

#endif /* __ADC_BUFFER_H */