# Real-time ECG monitor

## **DISCLAIMER**: 

This project is mearly an academic attempt at recreating a device, that is **somewhat remeniscent** of an actual (IEC 62304 compliant) medical device. **This software should not serve as an actual diagnostic tool**. It is not compliant to any actual safety-critical standards (medical software must be compliant at least to IEC 62304 standard, please check this before using any software for your devices), **the author does not condone the use of this software in any way other than educational purposes**. The license in the *LICENSE* file states the legal limitation of author's liablity.

## Hardware:

* STLink V2

* [STM32F411CE](https://www.st.com/en/microcontrollers-microprocessors/stm32f411ce.html)

* [AD8232](https://cdn.sparkfun.com/datasheets/Sensors/Biometric/AD8232.pdf)

(the detailed schematic of the whole device will be provided soon)

## Dependencies:

* GNU ARM Embedded Toolchain 12.x (with newlib)

* CMake

* Make/Ninja

## Building


### GNU Make:

```bash
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake
make
```

### Ninja

```bash
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake -GNinja
ninja
```

## Flashing the device

```bash
st-flash write ECGMonitor.bin 0x8000000
```
