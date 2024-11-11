################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.c \
../InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.c \
../InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.c \
../InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.c 

OBJS += \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.o \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.o \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.o \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.o 

COMPILED_SRCS += \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.src \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.src \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.src \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.src 

C_DEPS += \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.d \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.d \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.d \
./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.d 


# Each subdirectory must supply rules for building sources it contributes
InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/%.src: ../InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/%.c InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/DmxWorkSpace/D9_CPU1/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/%.o: ./InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/%.src InfineonLibraries/Libraries/Infra/Platform/Tricore/Compilers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


