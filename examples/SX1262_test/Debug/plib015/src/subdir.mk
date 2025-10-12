################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../plib015/src/plib015_gpio.c \
../plib015/src/plib015_i2c.c \
../plib015/src/plib015_rcu.c \
../plib015/src/plib015_spi.c \
../plib015/src/plib015_uart.c 

C_DEPS += \
./plib015/src/plib015_gpio.d \
./plib015/src/plib015_i2c.d \
./plib015/src/plib015_rcu.d \
./plib015/src/plib015_spi.d \
./plib015/src/plib015_uart.d 

OBJS += \
./plib015/src/plib015_gpio.o \
./plib015/src/plib015_i2c.o \
./plib015/src/plib015_rcu.o \
./plib015/src/plib015_spi.o \
./plib015/src/plib015_uart.o 


# Each subdirectory must supply rules for building sources it contributes
plib015/src/%.o: ../plib015/src/%.c plib015/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc  -march=rv32imfc -mabi=ilp32f  -msmall-data-limit=8 -mstrict-align -mno-save-restore  -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fno-builtin -flto -DSELF_TIMED=1 -Wall -Wextra -g3 -ggdb -DHSECLK_VAL=12000000 -DRETARGET -DSYSCLK_PLL -DCKO_PLL0 -I"D:\workspace\NIIET\SX1262_test\platform\include" -I"D:\workspace\NIIET\SX1262_test\Inc" -I"D:\workspace\NIIET\SX1262_test\plib015\inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-plib015-2f-src

clean-plib015-2f-src:
	-$(RM) ./plib015/src/plib015_gpio.d ./plib015/src/plib015_gpio.o ./plib015/src/plib015_i2c.d ./plib015/src/plib015_i2c.o ./plib015/src/plib015_rcu.d ./plib015/src/plib015_rcu.o ./plib015/src/plib015_spi.d ./plib015/src/plib015_spi.o ./plib015/src/plib015_uart.d ./plib015/src/plib015_uart.o

.PHONY: clean-plib015-2f-src

