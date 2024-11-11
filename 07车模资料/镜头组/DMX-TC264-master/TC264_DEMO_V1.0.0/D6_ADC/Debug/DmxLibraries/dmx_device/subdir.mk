################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DmxLibraries/dmx_device/dmx_icm20602.c \
../DmxLibraries/dmx_device/dmx_ips.c \
../DmxLibraries/dmx_device/dmx_mpu.c \
../DmxLibraries/dmx_device/dmx_mt9v034.c \
../DmxLibraries/dmx_device/dmx_oled.c \
../DmxLibraries/dmx_device/dmx_tft180.c 

OBJS += \
./DmxLibraries/dmx_device/dmx_icm20602.o \
./DmxLibraries/dmx_device/dmx_ips.o \
./DmxLibraries/dmx_device/dmx_mpu.o \
./DmxLibraries/dmx_device/dmx_mt9v034.o \
./DmxLibraries/dmx_device/dmx_oled.o \
./DmxLibraries/dmx_device/dmx_tft180.o 

COMPILED_SRCS += \
./DmxLibraries/dmx_device/dmx_icm20602.src \
./DmxLibraries/dmx_device/dmx_ips.src \
./DmxLibraries/dmx_device/dmx_mpu.src \
./DmxLibraries/dmx_device/dmx_mt9v034.src \
./DmxLibraries/dmx_device/dmx_oled.src \
./DmxLibraries/dmx_device/dmx_tft180.src 

C_DEPS += \
./DmxLibraries/dmx_device/dmx_icm20602.d \
./DmxLibraries/dmx_device/dmx_ips.d \
./DmxLibraries/dmx_device/dmx_mpu.d \
./DmxLibraries/dmx_device/dmx_mt9v034.d \
./DmxLibraries/dmx_device/dmx_oled.d \
./DmxLibraries/dmx_device/dmx_tft180.d 


# Each subdirectory must supply rules for building sources it contributes
DmxLibraries/dmx_device/%.src: ../DmxLibraries/dmx_device/%.c DmxLibraries/dmx_device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ADS1.8.0/WorkSpace/Dmx_TC264D_DA_LibraryV4.1/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

DmxLibraries/dmx_device/%.o: ./DmxLibraries/dmx_device/%.src DmxLibraries/dmx_device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


