################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Cpu0_Main.c \
../Source/Cpu1_Main.c \
../Source/Dmx_Isr.c 

OBJS += \
./Source/Cpu0_Main.o \
./Source/Cpu1_Main.o \
./Source/Dmx_Isr.o 

COMPILED_SRCS += \
./Source/Cpu0_Main.src \
./Source/Cpu1_Main.src \
./Source/Dmx_Isr.src 

C_DEPS += \
./Source/Cpu0_Main.d \
./Source/Cpu1_Main.d \
./Source/Dmx_Isr.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.src: ../Source/%.c Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/WorkSpace/ceshi/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Source/%.o: ./Source/%.src Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


