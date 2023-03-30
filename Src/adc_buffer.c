#include "adc_buffer.h"

volatile uint16_t adc_buffer[ADC_BUF_LEN] = {};
volatile uint32_t adc_buffer_last_index = 0UL;
volatile uint32_t adc_buffer_curr_index = 0UL;

uint16_t adcbuf_get_next_blocking() {
    /* wait until new data arrives in the adc_buffer thru a DMA channel */
    while(adc_buffer_last_index == adc_buffer_curr_index) {
        asm volatile ("nop");
    }

    uint16_t value = adc_buffer[adc_buffer_curr_index]; 
    adc_buffer_curr_index = (adc_buffer_curr_index + 1) % ADC_BUF_LEN;

    return value;
}

_Bool adcbuf_try_push(uint16_t value) {
    if(adc_buffer_last_index == adc_buffer_curr_index)
        return false;
    
    adc_buffer[adc_buffer_last_index] = value;
    adc_buffer_last_index = (adc_buffer_last_index + 1) % ADC_BUF_LEN;

    return true;
}