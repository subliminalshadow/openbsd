# Project: SDLPoP
# OpenBSD Makefile edit by subliminal

CC   = gcc
OBJ  = main.o data.o seg000.o seg001.o seg002.o seg003.o seg004.o seg005.o seg006.o seg007.o seg008.o seg009.o
LIBS =  `sdl-config --libs` -l"SDL_image"
INCS = -I/usr/local/include 
BIN  = prince
CFLAGS = $(INCS) -Wall -pedantic -std=gnu99
RM = rm -f
HFILES   = common.h config.h data.h proto.h types.h

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LIBS)

%.o: %.c $(HFILES)
	$(CC) -c $< $(CFLAGS)
