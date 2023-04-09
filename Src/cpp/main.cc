extern "C" {
    #include "adc_buffer.h"
    #include "serial/print.h"
};

#include "moving_avg.hh"
#include "moving_avg.cc"
#include "sample_buffer.cc"

static constexpr uint32_t MAVG_WINDOW_SIZE = 5U;

extern "C"
{
    #include <stdbool.h>
    extern volatile _Bool leads_off;
}

extern "C" void cpp_main() 
{
    auto buffer = sample_buffer<uint16_t, ADC_BUF_LEN>(
            adc_buffer, 
            &adc_buffer_curr_index, 
            &adc_buffer_last_index
        );

    auto filter = moving_avg<uint16_t, ADC_BUF_LEN, MAVG_WINDOW_SIZE>(buffer);

    while(true) 
    {
        if(!leads_off) {
            serial_printf("%d \r\n", filter.next_sample());    
        }
    }
}
