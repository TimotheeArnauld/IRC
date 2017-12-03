CC=gcc
LIBS=-lpthread
EXEC=server

$(EXEC): font.o  menu.o socket.o main.o
	$(CC) -o $(EXEC) ../lib/fonts/font.o menu.o socket.o main.o $(LIBS)

socket.o: socket.c
	$(CC) -I../lib/fonts/ -o socket.o -c socket.c

font.o: ../lib/fonts/font.c
	$(CC) -o ../lib/fonts/font.o -c ../lib/fonts/font.c

main.o: main.c socket.h
	$(CC) -I./ -o main.o -c main.c

menu.o: menu.c
	$(CC) -o menu.o -c menu.c

clean:
	rm -rf *.o

mrproper:
	rm -rf $(EXEC)
