IDIR =../include
CC=gcc
CFLAGS=-g -ansi -Wall -I$(IDIR)

ODIR=../obj
LDIR =../lib

LIBS=-lm -pthread

_DEPS = grafo.h file.h dijkstra.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o grafo.o file.o dijkstra.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
