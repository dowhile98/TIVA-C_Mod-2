################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/archivos de programa/ti/ccs1031/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Core/Scr/main.obj" \
"./Core/Scr/tm4c123gh6pm_startup_ccs.obj" \
"./ThirdParty/FreeRTOS/croutine.obj" \
"./ThirdParty/FreeRTOS/event_groups.obj" \
"./ThirdParty/FreeRTOS/list.obj" \
"./ThirdParty/FreeRTOS/queue.obj" \
"./ThirdParty/FreeRTOS/stream_buffer.obj" \
"./ThirdParty/FreeRTOS/tasks.obj" \
"./ThirdParty/FreeRTOS/timers.obj" \
"./ThirdParty/FreeRTOS/portable/CCS/ARM_CM4F/port.obj" \
"./ThirdParty/FreeRTOS/portable/CCS/ARM_CM4F/portasm.obj" \
"./ThirdParty/FreeRTOS/portable/MemMang/heap_4.obj" \
"./ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.obj" \
"./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.obj" \
"./ThirdParty/SEGGER/SEGGER/SEGGER_RTT.obj" \
"./ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.obj" \
"./ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.obj" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Core/Scr/subdir_vars.mk
-include ThirdParty/FreeRTOS/subdir_vars.mk
-include ThirdParty/FreeRTOS/portable/CCS/ARM_CM4F/subdir_vars.mk
-include ThirdParty/FreeRTOS/portable/MemMang/subdir_vars.mk
-include ThirdParty/SEGGER/Config/subdir_vars.mk
-include ThirdParty/SEGGER/OS/subdir_vars.mk
-include ThirdParty/SEGGER/SEGGER/subdir_vars.mk
-include subdir_rules.mk
-include Core/Scr/subdir_rules.mk
-include ThirdParty/FreeRTOS/subdir_rules.mk
-include ThirdParty/FreeRTOS/portable/CCS/ARM_CM4F/subdir_rules.mk
-include ThirdParty/FreeRTOS/portable/MemMang/subdir_rules.mk
-include ThirdParty/SEGGER/Config/subdir_rules.mk
-include ThirdParty/SEGGER/OS/subdir_rules.mk
-include ThirdParty/SEGGER/SEGGER/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
FreeRTOS.out \

EXE_OUTPUTS__QUOTED += \
"FreeRTOS.out" \

BIN_OUTPUTS += \
FreeRTOS.hex \

BIN_OUTPUTS__QUOTED += \
"FreeRTOS.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "FreeRTOS.out" secondary-outputs

# Tool invocations
FreeRTOS.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"D:/archivos de programa/ti/ccs1031/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --c11 --gcc --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"FreeRTOS.map" --heap_size=0 --stack_size=512 -i"D:/archivos de programa/ti/ccs1031/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/lib" -i"D:/archivos de programa/ti/ccs1031/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="FreeRTOS_linkInfo.xml" --rom_model -o "FreeRTOS.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

FreeRTOS.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: Arm Hex Utility'
	"D:/archivos de programa/ti/ccs1031/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armhex" --diag_wrap=off --binary -o "FreeRTOS.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Core\Scr\main.obj" "Core\Scr\tm4c123gh6pm_startup_ccs.obj" "ThirdParty\FreeRTOS\croutine.obj" "ThirdParty\FreeRTOS\event_groups.obj" "ThirdParty\FreeRTOS\list.obj" "ThirdParty\FreeRTOS\queue.obj" "ThirdParty\FreeRTOS\stream_buffer.obj" "ThirdParty\FreeRTOS\tasks.obj" "ThirdParty\FreeRTOS\timers.obj" "ThirdParty\FreeRTOS\portable\CCS\ARM_CM4F\port.obj" "ThirdParty\FreeRTOS\portable\CCS\ARM_CM4F\portasm.obj" "ThirdParty\FreeRTOS\portable\MemMang\heap_4.obj" "ThirdParty\SEGGER\Config\SEGGER_SYSVIEW_Config_FreeRTOS.obj" "ThirdParty\SEGGER\OS\SEGGER_SYSVIEW_FreeRTOS.obj" "ThirdParty\SEGGER\SEGGER\SEGGER_RTT.obj" "ThirdParty\SEGGER\SEGGER\SEGGER_RTT_printf.obj" "ThirdParty\SEGGER\SEGGER\SEGGER_SYSVIEW.obj" 
	-$(RM) "Core\Scr\main.d" "Core\Scr\tm4c123gh6pm_startup_ccs.d" "ThirdParty\FreeRTOS\croutine.d" "ThirdParty\FreeRTOS\event_groups.d" "ThirdParty\FreeRTOS\list.d" "ThirdParty\FreeRTOS\queue.d" "ThirdParty\FreeRTOS\stream_buffer.d" "ThirdParty\FreeRTOS\tasks.d" "ThirdParty\FreeRTOS\timers.d" "ThirdParty\FreeRTOS\portable\CCS\ARM_CM4F\port.d" "ThirdParty\FreeRTOS\portable\MemMang\heap_4.d" "ThirdParty\SEGGER\Config\SEGGER_SYSVIEW_Config_FreeRTOS.d" "ThirdParty\SEGGER\OS\SEGGER_SYSVIEW_FreeRTOS.d" "ThirdParty\SEGGER\SEGGER\SEGGER_RTT.d" "ThirdParty\SEGGER\SEGGER\SEGGER_RTT_printf.d" "ThirdParty\SEGGER\SEGGER\SEGGER_SYSVIEW.d" 
	-$(RM) "ThirdParty\FreeRTOS\portable\CCS\ARM_CM4F\portasm.d" 
	-@echo 'Finished clean'
	-@echo ' '

secondary-outputs: $(BIN_OUTPUTS)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

