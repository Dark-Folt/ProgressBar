CC=gcc
CFLAGS=-Wall -O
LDFLAGS=
EXEC=prog

all: $(EXEC) 

prog: main.o 
	$(CC) -o $@ $< $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o core


