cmake_minimum_required(VERSION 3.10)

# Configure the project
project(ECGMonitor C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Specify the cross compiler
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(AS arm-none-eabi-as)
set(AR arm-none-eabi-ar)
set(OBJCOPY arm-none-eabi-objcopy)
set(OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F411CEUx_FLASH.ld)

#Uncomment for hardware floating point
set(FPU_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
add_definitions(-DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING)

#Uncomment for software floating point
#set(FPU_FLAGS "-mfloat-abi=soft")

set(COMMON_FLAGS "-mcpu=cortex-m4 ${FPU_FLAGS} -mthumb -mthumb-interwork -ffunction-sections -fdata-sections -g -fno-common -fmessage-length=0 -specs=nosys.specs -specs=nano.specs")

set(CMAKE_C_FLAGS "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,-gc-sections -T ${LINKER_SCRIPT}")

add_definitions(-D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\) -DUSE_HAL_DRIVER -DSTM32F411xE)

file(GLOB_RECURSE SOURCES "startup_stm32f411xe.s" 
Src/*.c
Src/cpp/*.cc
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
)

include_directories(Inc
    Drivers/STM32F4xx_HAL_Driver/Inc
    Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Include Inc)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
target_link_libraries(${PROJECT_NAME}.elf c m nosys)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
