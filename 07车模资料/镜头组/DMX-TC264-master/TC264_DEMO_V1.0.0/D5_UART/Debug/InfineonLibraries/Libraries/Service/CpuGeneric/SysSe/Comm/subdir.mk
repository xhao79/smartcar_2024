################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Console.c \
../InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Shell.c 

OBJS += \
./InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Console.o \
./InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Shell.o 

COMPILED_SRCS += \
./InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Console.src \
./InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Shell.src 

C_DEPS += \
./InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Console.d \
./InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Shell.d 


# Each subdirectory must supply rules for building sources it contributes
InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/%.src: ../InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/%.c InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/DmxWorkSpace/D5_UART/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/%.o: ./InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/%.src InfineonLibraries/Libraries/Service/CpuGeneric/SysSe/Comm/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


