#include "serial/print.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "usart.h"

#define OUTPUT_BUFFER_SIZE 256UL

static char output_buffer[256UL];

void serial_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(output_buffer, OUTPUT_BUFFER_SIZE, format, args);
    va_end(args);

    HAL_UART_Transmit(&huart2, (uint8_t*) output_buffer, strlen(output_buffer), 0xFFFF);
}