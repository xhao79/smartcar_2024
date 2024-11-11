################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DmxLibraries/DmxCommon/dmx_common.c \
../DmxLibraries/DmxCommon/dmx_font.c \
../DmxLibraries/DmxCommon/dmx_function.c 

OBJS += \
./DmxLibraries/DmxCommon/dmx_common.o \
./DmxLibraries/DmxCommon/dmx_font.o \
./DmxLibraries/DmxCommon/dmx_function.o 

COMPILED_SRCS += \
./DmxLibraries/DmxCommon/dmx_common.src \
./DmxLibraries/DmxCommon/dmx_font.src \
./DmxLibraries/DmxCommon/dmx_function.src 

C_DEPS += \
./DmxLibraries/DmxCommon/dmx_common.d \
./DmxLibraries/DmxCommon/dmx_font.d \
./DmxLibraries/DmxCommon/dmx_function.d 


# Each subdirectory must supply rules for building sources it contributes
DmxLibraries/DmxCommon/%.src: ../DmxLibraries/DmxCommon/%.c DmxLibraries/DmxCommon/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/DmxWorkSpace/D5_UART/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

DmxLibraries/DmxCommon/%.o: ./DmxLibraries/DmxCommon/%.src DmxLibraries/DmxCommon/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


