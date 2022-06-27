# Tic Tac Toe

CC     = gcc
CFLAGS = -g -w -std=c99 -Iinc/

ifeq ($(OS),Windows_NT)
	LIBS   = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
else
	LIBS   = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
endif

SRCS   = $(wildcard src/*.c)
OBJS   = $(patsubst src/%.c,bin/%.o,$(SRCS))
DEPS   = $(OBJS:.o:=.d)
DIRS   = src inc bin
EXE    = Tic-tac-toe

all: $(DIRS) $(EXE)

$(DIRS):
	mkdir -p $@

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

bin/%.o : src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

bin/%.o : src/%.c inc/%.h
	$(CC) -o $@ $(CFLAGS) -c $<

run : all
	./$(EXE)

clean:
	rm -rf bin *~ $(EXE)
