################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DmxLibraries/DmxDriver/dmx_adc.c \
../DmxLibraries/DmxDriver/dmx_assert.c \
../DmxLibraries/DmxDriver/dmx_delay.c \
../DmxLibraries/DmxDriver/dmx_dma.c \
../DmxLibraries/DmxDriver/dmx_encoder.c \
../DmxLibraries/DmxDriver/dmx_eru.c \
../DmxLibraries/DmxDriver/dmx_flash.c \
../DmxLibraries/DmxDriver/dmx_gpio.c \
../DmxLibraries/DmxDriver/dmx_hard_spi.c \
../DmxLibraries/DmxDriver/dmx_pit.c \
../DmxLibraries/DmxDriver/dmx_pwm.c \
../DmxLibraries/DmxDriver/dmx_soft_iic.c \
../DmxLibraries/DmxDriver/dmx_soft_spi.c \
../DmxLibraries/DmxDriver/dmx_uart.c 

OBJS += \
./DmxLibraries/DmxDriver/dmx_adc.o \
./DmxLibraries/DmxDriver/dmx_assert.o \
./DmxLibraries/DmxDriver/dmx_delay.o \
./DmxLibraries/DmxDriver/dmx_dma.o \
./DmxLibraries/DmxDriver/dmx_encoder.o \
./DmxLibraries/DmxDriver/dmx_eru.o \
./DmxLibraries/DmxDriver/dmx_flash.o \
./DmxLibraries/DmxDriver/dmx_gpio.o \
./DmxLibraries/DmxDriver/dmx_hard_spi.o \
./DmxLibraries/DmxDriver/dmx_pit.o \
./DmxLibraries/DmxDriver/dmx_pwm.o \
./DmxLibraries/DmxDriver/dmx_soft_iic.o \
./DmxLibraries/DmxDriver/dmx_soft_spi.o \
./DmxLibraries/DmxDriver/dmx_uart.o 

COMPILED_SRCS += \
./DmxLibraries/DmxDriver/dmx_adc.src \
./DmxLibraries/DmxDriver/dmx_assert.src \
./DmxLibraries/DmxDriver/dmx_delay.src \
./DmxLibraries/DmxDriver/dmx_dma.src \
./DmxLibraries/DmxDriver/dmx_encoder.src \
./DmxLibraries/DmxDriver/dmx_eru.src \
./DmxLibraries/DmxDriver/dmx_flash.src \
./DmxLibraries/DmxDriver/dmx_gpio.src \
./DmxLibraries/DmxDriver/dmx_hard_spi.src \
./DmxLibraries/DmxDriver/dmx_pit.src \
./DmxLibraries/DmxDriver/dmx_pwm.src \
./DmxLibraries/DmxDriver/dmx_soft_iic.src \
./DmxLibraries/DmxDriver/dmx_soft_spi.src \
./DmxLibraries/DmxDriver/dmx_uart.src 

C_DEPS += \
./DmxLibraries/DmxDriver/dmx_adc.d \
./DmxLibraries/DmxDriver/dmx_assert.d \
./DmxLibraries/DmxDriver/dmx_delay.d \
./DmxLibraries/DmxDriver/dmx_dma.d \
./DmxLibraries/DmxDriver/dmx_encoder.d \
./DmxLibraries/DmxDriver/dmx_eru.d \
./DmxLibraries/DmxDriver/dmx_flash.d \
./DmxLibraries/DmxDriver/dmx_gpio.d \
./DmxLibraries/DmxDriver/dmx_hard_spi.d \
./DmxLibraries/DmxDriver/dmx_pit.d \
./DmxLibraries/DmxDriver/dmx_pwm.d \
./DmxLibraries/DmxDriver/dmx_soft_iic.d \
./DmxLibraries/DmxDriver/dmx_soft_spi.d \
./DmxLibraries/DmxDriver/dmx_uart.d 


# Each subdirectory must supply rules for building sources it contributes
DmxLibraries/DmxDriver/%.src: ../DmxLibraries/DmxDriver/%.c DmxLibraries/DmxDriver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/DmxWorkSpace/D9_CPU1/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

DmxLibraries/DmxDriver/%.o: ./DmxLibraries/DmxDriver/%.src DmxLibraries/DmxDriver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


