################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c \
../retarget.c 

C_DEPS += \
./main.d \
./retarget.d 

OBJS += \
./main.o \
./retarget.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc  -march=rv32imfc -mabi=ilp32f  -msmall-data-limit=8 -mstrict-align -mno-save-restore  -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fno-builtin -flto -DSELF_TIMED=1 -Wall -Wextra -g3 -ggdb -DHSECLK_VAL=12000000 -DRETARGET -DSYSCLK_PLL -DCKO_PLL0 -I"D:\workspace\NIIET\SX1262_test\platform\include" -I"D:\workspace\NIIET\SX1262_test\Inc" -I"D:\workspace\NIIET\SX1262_test\plib015\inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./main.d ./main.o ./retarget.d ./retarget.o

.PHONY: clean--2e-

