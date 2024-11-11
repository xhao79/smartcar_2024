################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DmxLibraries/Dmx_ADC.c \
../DmxLibraries/Dmx_DELAY.c \
../DmxLibraries/Dmx_FLASH.c \
../DmxLibraries/Dmx_GPIO.c \
../DmxLibraries/Dmx_Hard_IIC.c \
../DmxLibraries/Dmx_PIT.c \
../DmxLibraries/Dmx_PWM.c \
../DmxLibraries/Dmx_Soft_IIC.c \
../DmxLibraries/Dmx_UART.c 

OBJS += \
./DmxLibraries/Dmx_ADC.o \
./DmxLibraries/Dmx_DELAY.o \
./DmxLibraries/Dmx_FLASH.o \
./DmxLibraries/Dmx_GPIO.o \
./DmxLibraries/Dmx_Hard_IIC.o \
./DmxLibraries/Dmx_PIT.o \
./DmxLibraries/Dmx_PWM.o \
./DmxLibraries/Dmx_Soft_IIC.o \
./DmxLibraries/Dmx_UART.o 

COMPILED_SRCS += \
./DmxLibraries/Dmx_ADC.src \
./DmxLibraries/Dmx_DELAY.src \
./DmxLibraries/Dmx_FLASH.src \
./DmxLibraries/Dmx_GPIO.src \
./DmxLibraries/Dmx_Hard_IIC.src \
./DmxLibraries/Dmx_PIT.src \
./DmxLibraries/Dmx_PWM.src \
./DmxLibraries/Dmx_Soft_IIC.src \
./DmxLibraries/Dmx_UART.src 

C_DEPS += \
./DmxLibraries/Dmx_ADC.d \
./DmxLibraries/Dmx_DELAY.d \
./DmxLibraries/Dmx_FLASH.d \
./DmxLibraries/Dmx_GPIO.d \
./DmxLibraries/Dmx_Hard_IIC.d \
./DmxLibraries/Dmx_PIT.d \
./DmxLibraries/Dmx_PWM.d \
./DmxLibraries/Dmx_Soft_IIC.d \
./DmxLibraries/Dmx_UART.d 


# Each subdirectory must supply rules for building sources it contributes
DmxLibraries/%.src: ../DmxLibraries/%.c DmxLibraries/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/ADS1.8.0/WorkSpace/Dmx_TC264DA_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

DmxLibraries/%.o: ./DmxLibraries/%.src DmxLibraries/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


