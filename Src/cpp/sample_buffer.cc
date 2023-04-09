#include "sample_buffer.hh"

template<typename data_t, uint32_t size>
sample_buffer<data_t, size>::sample_buffer(volatile data_t* buffer, volatile uint32_t* read_pos, volatile uint32_t* write_pos)
:buffer(buffer), read_pos(read_pos), write_pos(write_pos)
{
    static_assert(size != 0, "The sample buffer's size must not be equal 0");    
}


template<typename data_t, uint32_t size>
data_t sample_buffer<data_t, size>::read() const 
{  
    if(*read_pos == *write_pos)
        return 0;

    return buffer[*read_pos];
}


template<typename data_t, uint32_t size>
void sample_buffer<data_t, size>::next()
{
    *read_pos = (*read_pos + 1U) % size; 
}

template<typename data_t, uint32_t size>
void sample_buffer<data_t, size>::prev()
{
    if(*read_pos == 0)
    {
        *read_pos = size - 1U;
        return;
    }

    *read_pos -= 1U;
}

template<typename data_t, uint32_t size>
uint32_t sample_buffer<data_t, size>::readable_count() const
{
    if(*read_pos == *write_pos)
        return 0;

    if(*read_pos < *write_pos)
        return *write_pos - *read_pos;
    
    /* if(*write_pos > *read_pos) */
    return *write_pos + (size - *read_pos);  
}
