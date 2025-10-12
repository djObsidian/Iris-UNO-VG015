################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/lr_fhss_mac.c \
../Src/sx126x.c \
../Src/sx126x_driver_version.c \
../Src/sx126x_hal.c \
../Src/sx126x_lr_fhss.c 

C_DEPS += \
./Src/lr_fhss_mac.d \
./Src/sx126x.d \
./Src/sx126x_driver_version.d \
./Src/sx126x_hal.d \
./Src/sx126x_lr_fhss.d 

OBJS += \
./Src/lr_fhss_mac.o \
./Src/sx126x.o \
./Src/sx126x_driver_version.o \
./Src/sx126x_hal.o \
./Src/sx126x_lr_fhss.o 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc  -march=rv32imfc -mabi=ilp32f  -msmall-data-limit=8 -mstrict-align -mno-save-restore  -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fno-builtin -flto -DSELF_TIMED=1 -Wall -Wextra -g3 -ggdb -DHSECLK_VAL=12000000 -DRETARGET -DSYSCLK_PLL -DCKO_PLL0 -I"D:\workspace\NIIET\SX1262_test\platform\include" -I"D:\workspace\NIIET\SX1262_test\Inc" -I"D:\workspace\NIIET\SX1262_test\plib015\inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Src

clean-Src:
	-$(RM) ./Src/lr_fhss_mac.d ./Src/lr_fhss_mac.o ./Src/sx126x.d ./Src/sx126x.o ./Src/sx126x_driver_version.d ./Src/sx126x_driver_version.o ./Src/sx126x_hal.d ./Src/sx126x_hal.o ./Src/sx126x_lr_fhss.d ./Src/sx126x_lr_fhss.o

.PHONY: clean-Src

