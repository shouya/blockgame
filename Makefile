CC = gcc
CFLAGS = -Wall -ansi
LIBS = -lSDLmain -lSDL

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

BIN_DIR = bin
SRC_DIR = src
INC_DIR = include

DEBUG = no
PROFILE = nox
OPTIMIZATION = -O3

ifeq ($(DEBUG), yes)
	OPTIMIZATION = -O0
	CFLAGS += -g
endif

ifeq ($(PROFILE), yes)
	CFLAGS += -pg
endif

CFLAGS += $(OPTIMIZATION)
CFLAGS += -I$(INC_DIR)

all: blockgame


blockgame: $(OBJECTS)
	gcc $(CFLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN_DIR)/*
	rm -f $(SRC_DIR)/*.o

rebuild: clean all


.PHONY : clean





