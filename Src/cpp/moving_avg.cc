#include "moving_avg.hh"

template <typename sample_t, uint32_t buffer_size, uint32_t window_size>
moving_avg<sample_t, buffer_size, window_size>::moving_avg(sample_buffer<sample_t, buffer_size>& buffer) 
:buffer(buffer)
{
    static_assert(buffer_size != 0, "Buffer size cannot be equal to 0!");
    static_assert(window_size % 2U == 1U, "Window size must be an odd number!");
}

template <typename sample_t, uint32_t buffer_size, uint32_t window_size>
sample_t moving_avg<sample_t, buffer_size, window_size>::next_sample() const
{
    while(buffer.readable_count() >= window_size) 
    { 
        asm volatile ("nop"); 
    }

    for(uint32_t i = 0; i < (window_size / 2); ++i) {
        buffer.prev();
    }

    sample_t avg = 0;
    for(uint32_t i = 0; i < window_size; ++i) {
        avg += buffer.read();
        buffer.next();
    }

    for(uint32_t i = 0; i < (window_size / 2) - 1; ++i) {
        buffer.prev();
    }

    return avg / (sample_t) window_size;
}
