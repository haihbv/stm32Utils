# variables
CC     = gcc
DEPS   = intel_hex.h
OBJ    = main.o intel_hex.o
BIN    = application.bin
TARGET = application.exe

# include path
INC := .

# resources path
SRC := main.c intel_hex.c

# file HEX
HEX ?= firmware.hex

%.o: %.c $(DEPS)
	$(CC) -I$(INC) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean build convert run read

# build exe
build: $(TARGET)

# convert .hex -> .bin
convert: $(TARGET)
	./$(TARGET) $(HEX) $(BIN)

run: 
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ) $(BIN)
	
read:
	hexdump -C $(BIN)