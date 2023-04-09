#pragma once

#include <stdint.h>
#include "sample_buffer.hh"

/**
 * @brief Simple moving average filter
 */ 
template <typename sample_t, uint32_t buffer_size, uint32_t window_size>
class moving_avg
{
public:
    explicit moving_avg(sample_buffer<sample_t, buffer_size>& buffer);
    
    virtual ~moving_avg() = default;
    
    /**
     * @brief get the next filetered sample from the buffer
     * 
     * @return sample_t next filtered sample
     */
    sample_t next_sample() const; 

private:
    sample_buffer<sample_t, buffer_size>& buffer;
};
