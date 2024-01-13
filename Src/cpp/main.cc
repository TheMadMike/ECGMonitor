extern "C" {
    #include "adc_buffer.h"
    #include "serial/print.h"
    #include "usart.h"
    #include "fir.h"
    #include "fir_coeffs.h"
};

#include "ring_buffer.hh"
#include <cstring>

static constexpr uint32_t MAVG_WINDOW_SIZE = 5U;

extern "C"
{
    #include <stdbool.h>
    extern volatile _Bool leads_off;
}

extern "C" void cpp_main() 
{
    auto buffer = ring_buffer<uint16_t, ADC_BUF_LEN>(
            adc_buffer, 
            &adc_buffer_curr_index, 
            &adc_buffer_last_index
        );

    uint8_t uart_buffer[2] = { 0x00, 0x00 };

    struct fir_t fir0 = {
        .coeffs = fir0_coeffs,
        .coeffs_len = (sizeof(fir0_coeffs) / sizeof(fp32_t)),
        .buf = adc_buffer,
        .buf_len = ADC_BUF_LEN
    };  

    buffer.set_fir(&fir0);

    while(1) 
    {
        if((!leads_off) && buffer.readable_count() > 0)
        {
            *((uint16_t*)uart_buffer) = buffer.read();
            HAL_UART_Transmit(&huart2, uart_buffer, 2, 0xFF);
        }
    }

}

