################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ThirdParty/SEGGER/Config/%.obj: ../ThirdParty/SEGGER/Config/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/archivos de programa/ti/ccs1031/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CURSOS/freeRTOS/CODIGO/TIVA C/FreeRTOS" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="D:/CURSOS/freeRTOS/CODIGO/TIVA C/FreeRTOS/ThirdParty/SEGGER/Config" --include_path="D:/CURSOS/freeRTOS/CODIGO/TIVA C/FreeRTOS/ThirdParty/SEGGER/OS" --include_path="D:/CURSOS/freeRTOS/CODIGO/TIVA C/FreeRTOS/ThirdParty/SEGGER/SEGGER" --include_path="D:/CURSOS/freeRTOS/CODIGO/TIVA C/FreeRTOS/ThirdParty" --include_path="D:/CURSOS/freeRTOS/CODIGO/TIVA C/FreeRTOS/ThirdParty/FreeRTOS/include" --include_path="D:/CURSOS/freeRTOS/CODIGO/TIVA C/FreeRTOS/ThirdParty/FreeRTOS/portable/CCS/ARM_CM4F" --include_path="D:/CURSOS/freeRTOS/CODIGO/TIVA C/FreeRTOS/Core/Inc" --include_path="D:/archivos de programa/ti/ccs1031/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --c11 --gcc --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="ThirdParty/SEGGER/Config/$(basename $(<F)).d_raw" --obj_directory="ThirdParty/SEGGER/Config" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


