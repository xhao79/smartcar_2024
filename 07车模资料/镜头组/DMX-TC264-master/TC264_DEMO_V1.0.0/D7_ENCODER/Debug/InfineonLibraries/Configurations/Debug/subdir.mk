################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../InfineonLibraries/Configurations/Debug/sync_on_halt.c 

OBJS += \
./InfineonLibraries/Configurations/Debug/sync_on_halt.o 

COMPILED_SRCS += \
./InfineonLibraries/Configurations/Debug/sync_on_halt.src 

C_DEPS += \
./InfineonLibraries/Configurations/Debug/sync_on_halt.d 


# Each subdirectory must supply rules for building sources it contributes
InfineonLibraries/Configurations/Debug/%.src: ../InfineonLibraries/Configurations/Debug/%.c InfineonLibraries/Configurations/Debug/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/DmxWorkSpace/D7_ENCODER/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

InfineonLibraries/Configurations/Debug/%.o: ./InfineonLibraries/Configurations/Debug/%.src InfineonLibraries/Configurations/Debug/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


