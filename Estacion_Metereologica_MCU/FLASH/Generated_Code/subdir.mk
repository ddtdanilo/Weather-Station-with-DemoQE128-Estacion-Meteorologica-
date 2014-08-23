################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/AD1.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/Entrada_Anemometro_1.c" \
"../Generated_Code/Entrada_Anemometro_2.c" \
"../Generated_Code/IO_Map.c" \
"../Generated_Code/PE_Timer.c" \
"../Generated_Code/S1.c" \
"../Generated_Code/S1_LED.c" \
"../Generated_Code/S2.c" \
"../Generated_Code/S2_LED.c" \
"../Generated_Code/Senal_25u.c" \
"../Generated_Code/Senal_25u_2.c" \
"../Generated_Code/Tiempo.c" \
"../Generated_Code/Tiempo_2.c" \
"../Generated_Code/Vectors.c" \

C_SRCS += \
../Generated_Code/AD1.c \
../Generated_Code/Cpu.c \
../Generated_Code/Entrada_Anemometro_1.c \
../Generated_Code/Entrada_Anemometro_2.c \
../Generated_Code/IO_Map.c \
../Generated_Code/PE_Timer.c \
../Generated_Code/S1.c \
../Generated_Code/S1_LED.c \
../Generated_Code/S2.c \
../Generated_Code/S2_LED.c \
../Generated_Code/Senal_25u.c \
../Generated_Code/Senal_25u_2.c \
../Generated_Code/Tiempo.c \
../Generated_Code/Tiempo_2.c \
../Generated_Code/Vectors.c \

OBJS += \
./Generated_Code/AD1_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/Entrada_Anemometro_1_c.obj \
./Generated_Code/Entrada_Anemometro_2_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/PE_Timer_c.obj \
./Generated_Code/S1_c.obj \
./Generated_Code/S1_LED_c.obj \
./Generated_Code/S2_c.obj \
./Generated_Code/S2_LED_c.obj \
./Generated_Code/Senal_25u_c.obj \
./Generated_Code/Senal_25u_2_c.obj \
./Generated_Code/Tiempo_c.obj \
./Generated_Code/Tiempo_2_c.obj \
./Generated_Code/Vectors_c.obj \

OBJS_QUOTED += \
"./Generated_Code/AD1_c.obj" \
"./Generated_Code/Cpu_c.obj" \
"./Generated_Code/Entrada_Anemometro_1_c.obj" \
"./Generated_Code/Entrada_Anemometro_2_c.obj" \
"./Generated_Code/IO_Map_c.obj" \
"./Generated_Code/PE_Timer_c.obj" \
"./Generated_Code/S1_c.obj" \
"./Generated_Code/S1_LED_c.obj" \
"./Generated_Code/S2_c.obj" \
"./Generated_Code/S2_LED_c.obj" \
"./Generated_Code/Senal_25u_c.obj" \
"./Generated_Code/Senal_25u_2_c.obj" \
"./Generated_Code/Tiempo_c.obj" \
"./Generated_Code/Tiempo_2_c.obj" \
"./Generated_Code/Vectors_c.obj" \

C_DEPS += \
./Generated_Code/AD1_c.d \
./Generated_Code/Cpu_c.d \
./Generated_Code/Entrada_Anemometro_1_c.d \
./Generated_Code/Entrada_Anemometro_2_c.d \
./Generated_Code/IO_Map_c.d \
./Generated_Code/PE_Timer_c.d \
./Generated_Code/S1_c.d \
./Generated_Code/S1_LED_c.d \
./Generated_Code/S2_c.d \
./Generated_Code/S2_LED_c.d \
./Generated_Code/Senal_25u_c.d \
./Generated_Code/Senal_25u_2_c.d \
./Generated_Code/Tiempo_c.d \
./Generated_Code/Tiempo_2_c.d \
./Generated_Code/Vectors_c.d \

C_DEPS_QUOTED += \
"./Generated_Code/AD1_c.d" \
"./Generated_Code/Cpu_c.d" \
"./Generated_Code/Entrada_Anemometro_1_c.d" \
"./Generated_Code/Entrada_Anemometro_2_c.d" \
"./Generated_Code/IO_Map_c.d" \
"./Generated_Code/PE_Timer_c.d" \
"./Generated_Code/S1_c.d" \
"./Generated_Code/S1_LED_c.d" \
"./Generated_Code/S2_c.d" \
"./Generated_Code/S2_LED_c.d" \
"./Generated_Code/Senal_25u_c.d" \
"./Generated_Code/Senal_25u_2_c.d" \
"./Generated_Code/Tiempo_c.d" \
"./Generated_Code/Tiempo_2_c.d" \
"./Generated_Code/Vectors_c.d" \

OBJS_OS_FORMAT += \
./Generated_Code/AD1_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/Entrada_Anemometro_1_c.obj \
./Generated_Code/Entrada_Anemometro_2_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/PE_Timer_c.obj \
./Generated_Code/S1_c.obj \
./Generated_Code/S1_LED_c.obj \
./Generated_Code/S2_c.obj \
./Generated_Code/S2_LED_c.obj \
./Generated_Code/Senal_25u_c.obj \
./Generated_Code/Senal_25u_2_c.obj \
./Generated_Code/Tiempo_c.obj \
./Generated_Code/Tiempo_2_c.obj \
./Generated_Code/Vectors_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/AD1_c.obj: ../Generated_Code/AD1.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/AD1.args" -ObjN="Generated_Code/AD1_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/%.d: ../Generated_Code/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Generated_Code/Cpu_c.obj: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Cpu.args" -ObjN="Generated_Code/Cpu_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Entrada_Anemometro_1_c.obj: ../Generated_Code/Entrada_Anemometro_1.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Entrada_Anemometro_1.args" -ObjN="Generated_Code/Entrada_Anemometro_1_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Entrada_Anemometro_2_c.obj: ../Generated_Code/Entrada_Anemometro_2.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Entrada_Anemometro_2.args" -ObjN="Generated_Code/Entrada_Anemometro_2_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_Map_c.obj: ../Generated_Code/IO_Map.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/IO_Map.args" -ObjN="Generated_Code/IO_Map_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_Timer_c.obj: ../Generated_Code/PE_Timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/PE_Timer.args" -ObjN="Generated_Code/PE_Timer_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/S1_c.obj: ../Generated_Code/S1.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/S1.args" -ObjN="Generated_Code/S1_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/S1_LED_c.obj: ../Generated_Code/S1_LED.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/S1_LED.args" -ObjN="Generated_Code/S1_LED_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/S2_c.obj: ../Generated_Code/S2.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/S2.args" -ObjN="Generated_Code/S2_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/S2_LED_c.obj: ../Generated_Code/S2_LED.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/S2_LED.args" -ObjN="Generated_Code/S2_LED_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Senal_25u_c.obj: ../Generated_Code/Senal_25u.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Senal_25u.args" -ObjN="Generated_Code/Senal_25u_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Senal_25u_2_c.obj: ../Generated_Code/Senal_25u_2.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Senal_25u_2.args" -ObjN="Generated_Code/Senal_25u_2_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Tiempo_c.obj: ../Generated_Code/Tiempo.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Tiempo.args" -ObjN="Generated_Code/Tiempo_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Tiempo_2_c.obj: ../Generated_Code/Tiempo_2.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Tiempo_2.args" -ObjN="Generated_Code/Tiempo_2_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors_c.obj: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Vectors.args" -ObjN="Generated_Code/Vectors_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


