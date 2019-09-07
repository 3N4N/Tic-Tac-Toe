# Tic Tac Toe

CC = gcc
CFLAGS = -g -w -std=c99
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

SRCS = main.c sdlshape.c sdlevent.c
OBJS = $(SRCS:.c=.o)
EXE = play

all: $(EXE)

.c.o:
	$(CC) -c $(CFLAGS) $<

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LIBS)

sdlevent.o : sdlevent.c sdlevent.h
	$(CC) -c $(CFLAGS) $<
sdlshape.o : sdlshape.c sdlshape.h
	$(CC) -c $(CFLAGS) $<
main.o : main.c
	$(CC) -c $(CFLAGS) $<

run : all
	./$(EXE)

clean:
	rm -f *.o *~ $(EXE)
