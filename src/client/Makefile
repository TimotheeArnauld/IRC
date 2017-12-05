CC=gcc
EXEC=client
LDFLAGS=-L/usr/lib/python2.7/config-x86_64-linux-gnu -L/usr/lib -lpython2.7 -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions
CFLAGS=-I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7  -fno-strict-aliasing -Wdate-time -D_FORTIFY_SOURCE=2 -g -fstack-protector-strong -Wformat -Werror=format-security  -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes

$(EXEC): font.o main.o
	$(CC) -o $(EXEC) ../lib/fonts/font.o main.o -lncurses $(LDFLAGS)

font.o: ../lib/fonts/font.c
	$(CC) -o ../lib/fonts/font.o -c ../lib/fonts/font.c

main.o: main.c
	$(CC) $(CFLAGS) -o main.o -c main.c -lncurses

clean: 
	rm -rf *.o

mrproper:
	rm -rf $(EXEC)
