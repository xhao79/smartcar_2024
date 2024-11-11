################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DmxLibraries/DmxDevice/dmx_icm20602.c \
../DmxLibraries/DmxDevice/dmx_icm42688.c \
../DmxLibraries/DmxDevice/dmx_ips.c \
../DmxLibraries/DmxDevice/dmx_mpu.c \
../DmxLibraries/DmxDevice/dmx_mt9v034.c \
../DmxLibraries/DmxDevice/dmx_oled.c \
../DmxLibraries/DmxDevice/dmx_tft180.c 

OBJS += \
./DmxLibraries/DmxDevice/dmx_icm20602.o \
./DmxLibraries/DmxDevice/dmx_icm42688.o \
./DmxLibraries/DmxDevice/dmx_ips.o \
./DmxLibraries/DmxDevice/dmx_mpu.o \
./DmxLibraries/DmxDevice/dmx_mt9v034.o \
./DmxLibraries/DmxDevice/dmx_oled.o \
./DmxLibraries/DmxDevice/dmx_tft180.o 

COMPILED_SRCS += \
./DmxLibraries/DmxDevice/dmx_icm20602.src \
./DmxLibraries/DmxDevice/dmx_icm42688.src \
./DmxLibraries/DmxDevice/dmx_ips.src \
./DmxLibraries/DmxDevice/dmx_mpu.src \
./DmxLibraries/DmxDevice/dmx_mt9v034.src \
./DmxLibraries/DmxDevice/dmx_oled.src \
./DmxLibraries/DmxDevice/dmx_tft180.src 

C_DEPS += \
./DmxLibraries/DmxDevice/dmx_icm20602.d \
./DmxLibraries/DmxDevice/dmx_icm42688.d \
./DmxLibraries/DmxDevice/dmx_ips.d \
./DmxLibraries/DmxDevice/dmx_mpu.d \
./DmxLibraries/DmxDevice/dmx_mt9v034.d \
./DmxLibraries/DmxDevice/dmx_oled.d \
./DmxLibraries/DmxDevice/dmx_tft180.d 


# Each subdirectory must supply rules for building sources it contributes
DmxLibraries/DmxDevice/%.src: ../DmxLibraries/DmxDevice/%.c DmxLibraries/DmxDevice/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/DmxWorkSpace/D3_PIT/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

DmxLibraries/DmxDevice/%.o: ./DmxLibraries/DmxDevice/%.src DmxLibraries/DmxDevice/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


