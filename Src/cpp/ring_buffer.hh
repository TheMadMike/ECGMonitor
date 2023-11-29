#pragma once

#include <stdint.h>

template<typename data_t, uint32_t size>
class ring_buffer
{
public:
    explicit ring_buffer(volatile data_t* buffer, volatile uint32_t* read_pos, volatile uint32_t* write_pos);
    virtual ~ring_buffer() = default;

    data_t read() const;

    void next();

    void prev();
    
    uint32_t readable_count() const;

private:
    volatile data_t* buffer;
    volatile uint32_t* read_pos = 0;
    volatile uint32_t* write_pos = 0;
};
