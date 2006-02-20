CFLAGS=-Iinclude -I/usr/include -Wall
LIBS=-lslang
CC=gcc

OBJS=map.o screen.o slangfun.o utils.o main.o menu.o player.o monster.o

hacknslash: $(OBJS)
	$(CC) -o hacknslash $(CFLAGS) $(LIBS) *.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o

mrclean:
	rm -f *.o *~
