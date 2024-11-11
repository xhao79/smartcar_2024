################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DmxLibraries/dmx_common/dmx_common.c \
../DmxLibraries/dmx_common/dmx_font.c \
../DmxLibraries/dmx_common/dmx_function.c 

OBJS += \
./DmxLibraries/dmx_common/dmx_common.o \
./DmxLibraries/dmx_common/dmx_font.o \
./DmxLibraries/dmx_common/dmx_function.o 

COMPILED_SRCS += \
./DmxLibraries/dmx_common/dmx_common.src \
./DmxLibraries/dmx_common/dmx_font.src \
./DmxLibraries/dmx_common/dmx_function.src 

C_DEPS += \
./DmxLibraries/dmx_common/dmx_common.d \
./DmxLibraries/dmx_common/dmx_font.d \
./DmxLibraries/dmx_common/dmx_function.d 


# Each subdirectory must supply rules for building sources it contributes
DmxLibraries/dmx_common/%.src: ../DmxLibraries/dmx_common/%.c DmxLibraries/dmx_common/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/WorkSpace/Dmx_TC264D_DA_LibraryV4.1/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

DmxLibraries/dmx_common/%.o: ./DmxLibraries/dmx_common/%.src DmxLibraries/dmx_common/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


