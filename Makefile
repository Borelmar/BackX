TARGET = ./fgoogle
CC = gcc

HEADER_DIR = ./src/include/
SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC = $(wildcard $(SRC_DIR)*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CSTAND = gnu99
ARCH = ARCH64# ARCH32

#LDFLAGS = -nostartfiles -Wl,--entry=init
CFLAGS = -std=$(CSTAND) -D$(ARCH) -O0 -Wall -g -I$(HEADER_DIR)
CLIBS = -lcrypto -lssl -lreadline

# Use only this flags order : gcc <flags> <objs> < -l lib> -o <out>

$(TARGET) : $(OBJ)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJ) $(CLIBS) -o $(TARGET)
	md5sum -b $(TARGET)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(CLIBS) -c $< -o $@

install :
	sudo mv $(TARGET) /usr/local/bin/
	chmod +x $(TARGET)
clean :
	rm ./obj/*.o
	rm $(TARGET)
