################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.c \
../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.c \
../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_Fifo.c 

OBJS += \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.o \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.o \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_Fifo.o 

COMPILED_SRCS += \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.src \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.src \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_Fifo.src 

C_DEPS += \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.d \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.d \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/Ifx_Fifo.d 


# Each subdirectory must supply rules for building sources it contributes
InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/%.src: ../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/%.c InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/DmxWorkSpace/D3_PIT/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/%.o: ./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/%.src InfineonLibraries/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


