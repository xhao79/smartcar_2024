################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm.c \
../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Atom.c \
../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Cmu.c \
../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Dpll.c \
../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tbu.c \
../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tim.c \
../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tom.c 

OBJS += \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm.o \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Atom.o \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Cmu.o \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Dpll.o \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tbu.o \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tim.o \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tom.o 

COMPILED_SRCS += \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm.src \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Atom.src \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Cmu.src \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Dpll.src \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tbu.src \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tim.src \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tom.src 

C_DEPS += \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm.d \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Atom.d \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Cmu.d \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Dpll.d \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tbu.d \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tim.d \
./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tom.d 


# Each subdirectory must supply rules for building sources it contributes
InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/%.src: ../InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/%.c InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/DmxWorkSpace/D3_PIT/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/%.o: ./InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/%.src InfineonLibraries/Libraries/iLLD/TC26B/Tricore/Gtm/Std/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


