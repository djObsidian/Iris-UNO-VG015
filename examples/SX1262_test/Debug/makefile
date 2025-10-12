################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include plib015/src/subdir.mk
-include platform/source/subdir.mk
-include Src/subdir.mk
-include subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C++M_DEPS)),)
-include $(C++M_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CCM_DEPS)),)
-include $(CCM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXXM_DEPS)),)
-include $(CXXM_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := SX1262_test
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
SX1262_test.bin \

SECONDARY_LIST += \
SX1262_test.lst \

SECONDARY_SIZE += \
SX1262_test.siz \


# All Target
all: main-build

# Main-build Target
main-build: SX1262_test.elf secondary-outputs

# Tool invocations
SX1262_test.elf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C++ Linker'
	riscv64-unknown-elf-g++  -march=rv32imfc -mabi=ilp32f  -msmall-data-limit=8 -mstrict-align -mno-save-restore  -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fno-builtin -flto -DSELF_TIMED=1 -Wall -Wextra -g3 -ggdb -T "D:\workspace\NIIET\SX1262_test\platform\ldscripts\k1921vg015_flash.ld" -nostartfiles -Xlinker --gc-sections -L"D:\workspace\NIIET\SX1262_test\platform\ldscripts" -Wl,-Map,"SX1262_test.map" -o "SX1262_test.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lgcc -lc
	@echo 'Finished building target: $@'
	@echo ' '

SX1262_test.bin: SX1262_test.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv64-unknown-elf-objcopy -O binary -j .text -j.text.startup -j.text.crt -j.rodata "SX1262_test.elf"  "SX1262_test.bin"
	@echo 'Finished building: $@'
	@echo ' '

SX1262_test.lst: SX1262_test.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv64-unknown-elf-objdump --source --all-headers --demangle --line-numbers --wide "SX1262_test.elf" > "SX1262_test.lst"
	@echo 'Finished building: $@'
	@echo ' '

SX1262_test.siz: SX1262_test.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv64-unknown-elf-size --format=berkeley -x --totals "SX1262_test.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SX1262_test.bin SX1262_test.elf SX1262_test.lst SX1262_test.siz
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents main-build

-include ../makefile.targets
