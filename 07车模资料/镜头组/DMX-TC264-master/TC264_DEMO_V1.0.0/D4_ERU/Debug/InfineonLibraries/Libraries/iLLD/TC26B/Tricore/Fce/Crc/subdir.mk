################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Fce/Crc/IfxFce_Crc.c 

OBJS += \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Fce/Crc/IfxFce_Crc.o 

COMPILED_SRCS += \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Fce/Crc/IfxFce_Crc.src 

C_DEPS += \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Fce/Crc/IfxFce_Crc.d 


# Each subdirectory must supply rules for building sources it contributes
InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Fce/Crc/%.src: ../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Fce/Crc/%.c InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Fce/Crc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/DmxWorkSpace/D4_ERU/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Fce/Crc/%.o: ./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Fce/Crc/%.src InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Fce/Crc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


