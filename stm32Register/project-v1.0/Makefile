vpath %.c $(SRC_DIRS)

GCC_DIR   :=  C:/Tools/arm-gcc
OBJ_COPY  := $(GCC_DIR)/bin/arm-none-eabi-objcopy
CC        := $(GCC_DIR)/bin/arm-none-eabi-gcc
OUTPUT_DIR := ./Output
LINKER_DIR := ./Linker

# Include files
INC_DIRS  := ./Drivers/inc ./System ./Module/rgb ./Module/ds3231 ./Module/ring_buffer
INC_FILES  := $(foreach INC_DIR, $(INC_DIRS), $(wildcard $(INC_DIR)/*))


# Source files
SRC_DIRS  := ./Drivers/src ./Core ./Startup ./Module/rgb ./Module/ds3231 ./Module/ring_buffer 
SRC_FILES := $(foreach SRC_DIR, $(SRC_DIRS), $(wildcard $(SRC_DIR)/*.c))

# Object files
OBJ_FILES := $(patsubst %.c, %.o, $(notdir $(SRC_FILES)))
OBJ_PATHS := $(patsubst %.c, $(OUTPUT_DIR)/%.o, $(notdir $(SRC_FILES)))

# CC option for INC_DIRS
INC_DIRS_OPT := $(foreach INC_DIR, $(INC_DIRS), -I$(INC_DIR))

# Compiler 
CHIP       := cortex-m3
CCFLAGS    := -c -mcpu=$(CHIP) -mthumb -std=gnu11 -O0 $(INC_DIRS_OPT)

# Linker 
LDFLAGS    := -nostdlib -T $(LINKER_DIR)/stm32_ls.ld -Wl,-Map=Output/makefile.map
vpath %.c $(SRC_DIRS)

build: makefile.hex
	@echo "                                            "	
	@echo "********************************************"
	@echo "*               Build Done!                *"
	@echo "********************************************"

print-%:
	@echo $($(subst print-,,$@))

clean:
	rm -f Clean Output/*
	@echo "                                            "	
	@echo "********************************************"
	@echo "*                 Clean Done               *"
	@echo "********************************************"


# Compile all .c files to Output/*.o
$(OUTPUT_DIR)/%.o: %.c
	$(CC) $(CCFLAGS) -o $@ $<

makefile.elf: $(OBJ_PATHS)
	$(CC) $(LDFLAGS) -o $(OUTPUT_DIR)/$@ $(OBJ_PATHS)

makefile.hex: makefile.elf
	$(OBJ_COPY) -O ihex $(OUTPUT_DIR)/$^ $(OUTPUT_DIR)/$@

flash: makefile.hex
	"C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe" -c port=SWD -d Output/makefile.hex 0x08000000 -rst
upload: flash
	@echo "                                            "
	@echo "********************************************"
	@echo "*                 Upload Done              *"
	@echo "********************************************"

erase:
	"C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe" -c port=SWD -e all
	@echo "                                            "	
	@echo "********************************************"
	@echo "*                 Chip Erase               *"
	@echo "********************************************"

reset:
	"C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe" -c port=SWD -rst
	@echo "                                            "
	@echo "********************************************"
	@echo "*                 Chip Reset               *"
	@echo "********************************************"

# file tree
.PHONY: tree

tree:
	@tree /F .
	@echo "                                            "
	@echo "********************************************"
	@echo "*                 Directory                *"
	@echo "********************************************"

.PHONY: build clean flash upload erase reset
# End of Makefile
