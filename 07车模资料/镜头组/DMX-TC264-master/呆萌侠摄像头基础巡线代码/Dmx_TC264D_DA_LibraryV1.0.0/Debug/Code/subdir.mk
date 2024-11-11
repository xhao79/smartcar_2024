################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Code/dmx_image_deal.c \
../Code/dmx_motor.c \
../Code/dmx_servos.c 

OBJS += \
./Code/dmx_image_deal.o \
./Code/dmx_motor.o \
./Code/dmx_servos.o 

COMPILED_SRCS += \
./Code/dmx_image_deal.src \
./Code/dmx_motor.src \
./Code/dmx_servos.src 

C_DEPS += \
./Code/dmx_image_deal.d \
./Code/dmx_motor.d \
./Code/dmx_servos.d 


# Each subdirectory must supply rules for building sources it contributes
Code/%.src: ../Code/%.c Code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/DmxWorkSpace/Dmx_TC264D_DA_LibraryV1.0.1/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Code/%.o: ./Code/%.src Code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


