################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../include/ \
../include/libraries/ \
../include/libraries/FreeRTOS/ \
../include/libraries/FreeRTOS/src/ \
../include/supportpackage \
../src/ \
../src/libraries/ \
../src/libraries/FreeRTOS/ \
../src/libraries/FreeRTOS/src/ \
../src/OledDisplay/ \
../src/packages/ \
../src/packages/ \
../src/packages/arduino/ \
../src/packages/arduino/ \
../src/packages/arduino/hardware/ \
../src/packages/arduino/hardware/ \
../src/packages/arduino/hardware/avr/ \
../src/packages/arduino/hardware/avr/ \
../src/packages/arduino/hardware/avr/1.8.1/ \
../src/packages/arduino/hardware/avr/1.8.1/ \
../src/packages/arduino/hardware/avr/1.8.1/cores/ \
../src/packages/arduino/hardware/avr/1.8.1/cores/arduino/ \
../src/packages/arduino/hardware/avr/1.8.1/variants/ \
../src/packages/arduino/hardware/avr/1.8.1/variants/mega/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../src/libraries/FreeRTOS/src/croutine.c \
../src/libraries/FreeRTOS/src/event_groups.c \
../src/libraries/FreeRTOS/src/heap_3.c \
../src/libraries/FreeRTOS/src/list.c \
../src/libraries/FreeRTOS/src/port.c \
../src/libraries/FreeRTOS/src/queue.c \
../src/libraries/FreeRTOS/src/stream_buffer.c \
../src/libraries/FreeRTOS/src/tasks.c \
../src/libraries/FreeRTOS/src/timers.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
src/libraries/FreeRTOS/src/croutine.o \
src/libraries/FreeRTOS/src/event_groups.o \
src/libraries/FreeRTOS/src/heap_3.o \
src/libraries/FreeRTOS/src/list.o \
src/libraries/FreeRTOS/src/port.o \
src/libraries/FreeRTOS/src/queue.o \
src/libraries/FreeRTOS/src/stream_buffer.o \
src/libraries/FreeRTOS/src/tasks.o \
src/libraries/FreeRTOS/src/timers.o

OBJS_AS_ARGS +=  \
src/libraries/FreeRTOS/src/croutine.o \
src/libraries/FreeRTOS/src/event_groups.o \
src/libraries/FreeRTOS/src/heap_3.o \
src/libraries/FreeRTOS/src/list.o \
src/libraries/FreeRTOS/src/port.o \
src/libraries/FreeRTOS/src/queue.o \
src/libraries/FreeRTOS/src/stream_buffer.o \
src/libraries/FreeRTOS/src/tasks.o \
src/libraries/FreeRTOS/src/timers.o

C_DEPS +=  \
src/libraries/FreeRTOS/src/croutine.d \
src/libraries/FreeRTOS/src/event_groups.d \
src/libraries/FreeRTOS/src/heap_3.d \
src/libraries/FreeRTOS/src/list.d \
src/libraries/FreeRTOS/src/port.d \
src/libraries/FreeRTOS/src/queue.d \
src/libraries/FreeRTOS/src/stream_buffer.d \
src/libraries/FreeRTOS/src/tasks.d \
src/libraries/FreeRTOS/src/timers.d

C_DEPS_AS_ARGS +=  \
src/libraries/FreeRTOS/src/croutine.d \
src/libraries/FreeRTOS/src/event_groups.d \
src/libraries/FreeRTOS/src/heap_3.d \
src/libraries/FreeRTOS/src/list.d \
src/libraries/FreeRTOS/src/port.d \
src/libraries/FreeRTOS/src/queue.d \
src/libraries/FreeRTOS/src/stream_buffer.d \
src/libraries/FreeRTOS/src/tasks.d \
src/libraries/FreeRTOS/src/timers.d

OUTPUT_FILE_PATH +=SmartCar.elf

OUTPUT_FILE_PATH_AS_ARGS +=SmartCar.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+=  \
R:/arduino/custom_projects/21_SmartCar/10_SmartCarCode/SmartCar/SupportPackage/Debug/libSupportPackage.a

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
src/libraries/FreeRTOS/src/croutine.o: ../src/libraries/FreeRTOS/src/croutine.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../include/libraries/FreeRTOS/src" -I"../include" -I"../src/packages/arduino/hardware/avr/1.8.1/cores/arduino" -I"../src/packages/arduino/hardware/avr/1.8.1/variants/mega" -I"../src/OledDisplay" -I"../include/supportpackage"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega2560" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/libraries/FreeRTOS/src/event_groups.o: ../src/libraries/FreeRTOS/src/event_groups.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../include/libraries/FreeRTOS/src" -I"../include" -I"../src/packages/arduino/hardware/avr/1.8.1/cores/arduino" -I"../src/packages/arduino/hardware/avr/1.8.1/variants/mega" -I"../src/OledDisplay" -I"../include/supportpackage"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega2560" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/libraries/FreeRTOS/src/heap_3.o: ../src/libraries/FreeRTOS/src/heap_3.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../include/libraries/FreeRTOS/src" -I"../include" -I"../src/packages/arduino/hardware/avr/1.8.1/cores/arduino" -I"../src/packages/arduino/hardware/avr/1.8.1/variants/mega" -I"../src/OledDisplay" -I"../include/supportpackage"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega2560" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/libraries/FreeRTOS/src/list.o: ../src/libraries/FreeRTOS/src/list.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../include/libraries/FreeRTOS/src" -I"../include" -I"../src/packages/arduino/hardware/avr/1.8.1/cores/arduino" -I"../src/packages/arduino/hardware/avr/1.8.1/variants/mega" -I"../src/OledDisplay" -I"../include/supportpackage"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega2560" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/libraries/FreeRTOS/src/port.o: ../src/libraries/FreeRTOS/src/port.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../include/libraries/FreeRTOS/src" -I"../include" -I"../src/packages/arduino/hardware/avr/1.8.1/cores/arduino" -I"../src/packages/arduino/hardware/avr/1.8.1/variants/mega" -I"../src/OledDisplay" -I"../include/supportpackage"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega2560" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/libraries/FreeRTOS/src/queue.o: ../src/libraries/FreeRTOS/src/queue.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../include/libraries/FreeRTOS/src" -I"../include" -I"../src/packages/arduino/hardware/avr/1.8.1/cores/arduino" -I"../src/packages/arduino/hardware/avr/1.8.1/variants/mega" -I"../src/OledDisplay" -I"../include/supportpackage"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega2560" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/libraries/FreeRTOS/src/stream_buffer.o: ../src/libraries/FreeRTOS/src/stream_buffer.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../include/libraries/FreeRTOS/src" -I"../include" -I"../src/packages/arduino/hardware/avr/1.8.1/cores/arduino" -I"../src/packages/arduino/hardware/avr/1.8.1/variants/mega" -I"../src/OledDisplay" -I"../include/supportpackage"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega2560" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/libraries/FreeRTOS/src/tasks.o: ../src/libraries/FreeRTOS/src/tasks.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../include/libraries/FreeRTOS/src" -I"../include" -I"../src/packages/arduino/hardware/avr/1.8.1/cores/arduino" -I"../src/packages/arduino/hardware/avr/1.8.1/variants/mega" -I"../src/OledDisplay" -I"../include/supportpackage"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega2560" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/libraries/FreeRTOS/src/timers.o: ../src/libraries/FreeRTOS/src/timers.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../include/libraries/FreeRTOS/src" -I"../include" -I"../src/packages/arduino/hardware/avr/1.8.1/cores/arduino" -I"../src/packages/arduino/hardware/avr/1.8.1/variants/mega" -I"../src/OledDisplay" -I"../include/supportpackage"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega2560" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="SmartCar.map" -Wl,--start-group -Wl,-lm -Wl,-lSupportPackage  -Wl,--end-group -Wl,-L"R:\arduino\custom_projects\21_SmartCar\10_SmartCarCode\SmartCar\SupportPackage\Debug"  -Wl,--gc-sections -mrelax -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega2560"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "SmartCar.elf" "SmartCar.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "SmartCar.elf" "SmartCar.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "SmartCar.elf" > "SmartCar.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "SmartCar.elf" "SmartCar.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "SmartCar.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "SmartCar.elf" "SmartCar.a" "SmartCar.hex" "SmartCar.lss" "SmartCar.eep" "SmartCar.map" "SmartCar.srec" "SmartCar.usersignatures"
	