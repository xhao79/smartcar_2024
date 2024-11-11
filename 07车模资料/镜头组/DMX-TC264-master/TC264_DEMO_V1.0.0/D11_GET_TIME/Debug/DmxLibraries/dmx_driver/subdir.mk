################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DmxLibraries/dmx_driver/dmx_adc.c \
../DmxLibraries/dmx_driver/dmx_assert.c \
../DmxLibraries/dmx_driver/dmx_delay.c \
../DmxLibraries/dmx_driver/dmx_dma.c \
../DmxLibraries/dmx_driver/dmx_encoder.c \
../DmxLibraries/dmx_driver/dmx_eru.c \
../DmxLibraries/dmx_driver/dmx_flash.c \
../DmxLibraries/dmx_driver/dmx_gpio.c \
../DmxLibraries/dmx_driver/dmx_hard_iic.c \
../DmxLibraries/dmx_driver/dmx_hard_spi.c \
../DmxLibraries/dmx_driver/dmx_pit.c \
../DmxLibraries/dmx_driver/dmx_pwm.c \
../DmxLibraries/dmx_driver/dmx_soft_iic.c \
../DmxLibraries/dmx_driver/dmx_soft_spi.c \
../DmxLibraries/dmx_driver/dmx_uart.c 

OBJS += \
./DmxLibraries/dmx_driver/dmx_adc.o \
./DmxLibraries/dmx_driver/dmx_assert.o \
./DmxLibraries/dmx_driver/dmx_delay.o \
./DmxLibraries/dmx_driver/dmx_dma.o \
./DmxLibraries/dmx_driver/dmx_encoder.o \
./DmxLibraries/dmx_driver/dmx_eru.o \
./DmxLibraries/dmx_driver/dmx_flash.o \
./DmxLibraries/dmx_driver/dmx_gpio.o \
./DmxLibraries/dmx_driver/dmx_hard_iic.o \
./DmxLibraries/dmx_driver/dmx_hard_spi.o \
./DmxLibraries/dmx_driver/dmx_pit.o \
./DmxLibraries/dmx_driver/dmx_pwm.o \
./DmxLibraries/dmx_driver/dmx_soft_iic.o \
./DmxLibraries/dmx_driver/dmx_soft_spi.o \
./DmxLibraries/dmx_driver/dmx_uart.o 

COMPILED_SRCS += \
./DmxLibraries/dmx_driver/dmx_adc.src \
./DmxLibraries/dmx_driver/dmx_assert.src \
./DmxLibraries/dmx_driver/dmx_delay.src \
./DmxLibraries/dmx_driver/dmx_dma.src \
./DmxLibraries/dmx_driver/dmx_encoder.src \
./DmxLibraries/dmx_driver/dmx_eru.src \
./DmxLibraries/dmx_driver/dmx_flash.src \
./DmxLibraries/dmx_driver/dmx_gpio.src \
./DmxLibraries/dmx_driver/dmx_hard_iic.src \
./DmxLibraries/dmx_driver/dmx_hard_spi.src \
./DmxLibraries/dmx_driver/dmx_pit.src \
./DmxLibraries/dmx_driver/dmx_pwm.src \
./DmxLibraries/dmx_driver/dmx_soft_iic.src \
./DmxLibraries/dmx_driver/dmx_soft_spi.src \
./DmxLibraries/dmx_driver/dmx_uart.src 

C_DEPS += \
./DmxLibraries/dmx_driver/dmx_adc.d \
./DmxLibraries/dmx_driver/dmx_assert.d \
./DmxLibraries/dmx_driver/dmx_delay.d \
./DmxLibraries/dmx_driver/dmx_dma.d \
./DmxLibraries/dmx_driver/dmx_encoder.d \
./DmxLibraries/dmx_driver/dmx_eru.d \
./DmxLibraries/dmx_driver/dmx_flash.d \
./DmxLibraries/dmx_driver/dmx_gpio.d \
./DmxLibraries/dmx_driver/dmx_hard_iic.d \
./DmxLibraries/dmx_driver/dmx_hard_spi.d \
./DmxLibraries/dmx_driver/dmx_pit.d \
./DmxLibraries/dmx_driver/dmx_pwm.d \
./DmxLibraries/dmx_driver/dmx_soft_iic.d \
./DmxLibraries/dmx_driver/dmx_soft_spi.d \
./DmxLibraries/dmx_driver/dmx_uart.d 


# Each subdirectory must supply rules for building sources it contributes
DmxLibraries/dmx_driver/%.src: ../DmxLibraries/dmx_driver/%.c DmxLibraries/dmx_driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/WorkSpace/Dmx_TC264D_DA_LibraryV4.1/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

DmxLibraries/dmx_driver/%.o: ./DmxLibraries/dmx_driver/%.src DmxLibraries/dmx_driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


