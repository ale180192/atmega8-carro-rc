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
../sdk_atmega8


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c \
../sdk_atmega8/ADC.c \
../sdk_atmega8/I2C.c \
../sdk_atmega8/INT_EXT.c \
../sdk_atmega8/LCD_4Bits_I2C.c \
../sdk_atmega8/RTC.c \
../sdk_atmega8/Servo.c \
../sdk_atmega8/Sleep.c \
../sdk_atmega8/teclado4x4.c \
../sdk_atmega8/Timers.c \
../sdk_atmega8/USART.c \
../sdk_atmega8/WDT.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o \
sdk_atmega8/ADC.o \
sdk_atmega8/I2C.o \
sdk_atmega8/INT_EXT.o \
sdk_atmega8/LCD_4Bits_I2C.o \
sdk_atmega8/RTC.o \
sdk_atmega8/Servo.o \
sdk_atmega8/Sleep.o \
sdk_atmega8/teclado4x4.o \
sdk_atmega8/Timers.o \
sdk_atmega8/USART.o \
sdk_atmega8/WDT.o

OBJS_AS_ARGS +=  \
main.o \
sdk_atmega8/ADC.o \
sdk_atmega8/I2C.o \
sdk_atmega8/INT_EXT.o \
sdk_atmega8/LCD_4Bits_I2C.o \
sdk_atmega8/RTC.o \
sdk_atmega8/Servo.o \
sdk_atmega8/Sleep.o \
sdk_atmega8/teclado4x4.o \
sdk_atmega8/Timers.o \
sdk_atmega8/USART.o \
sdk_atmega8/WDT.o

C_DEPS +=  \
main.d \
sdk_atmega8/ADC.d \
sdk_atmega8/I2C.d \
sdk_atmega8/INT_EXT.d \
sdk_atmega8/LCD_4Bits_I2C.d \
sdk_atmega8/RTC.d \
sdk_atmega8/Servo.d \
sdk_atmega8/Sleep.d \
sdk_atmega8/teclado4x4.d \
sdk_atmega8/Timers.d \
sdk_atmega8/USART.d \
sdk_atmega8/WDT.d

C_DEPS_AS_ARGS +=  \
main.d \
sdk_atmega8/ADC.d \
sdk_atmega8/I2C.d \
sdk_atmega8/INT_EXT.d \
sdk_atmega8/LCD_4Bits_I2C.d \
sdk_atmega8/RTC.d \
sdk_atmega8/Servo.d \
sdk_atmega8/Sleep.d \
sdk_atmega8/teclado4x4.d \
sdk_atmega8/Timers.d \
sdk_atmega8/USART.d \
sdk_atmega8/WDT.d

OUTPUT_FILE_PATH +=Carro.elf

OUTPUT_FILE_PATH_AS_ARGS +=Carro.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler

























./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.98\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega8 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.98\gcc\dev\atmega8" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

sdk_atmega8/%.o: ../sdk_atmega8/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.98\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega8 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.98\gcc\dev\atmega8" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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
	@echo Invoking: AVR/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Carro.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega8 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.98\gcc\dev\atmega8"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Carro.elf" "Carro.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Carro.elf" "Carro.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Carro.elf" > "Carro.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Carro.elf" "Carro.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "Carro.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Carro.elf" "Carro.a" "Carro.hex" "Carro.lss" "Carro.eep" "Carro.map" "Carro.srec" "Carro.usersignatures"
	