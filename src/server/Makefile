CC=gcc
LIBS=-pthread
EXEC=server

$(EXEC): font.o menu.o socket.o main.o
	$(CC) -o $(EXEC) font.o menu.o socket.o main.o $(LIBS)

font.o: font.c
	$(CC) -o font.o -c font.c

menu.o: menu.c
	$(CC) -o menu.o -c menu.c

socket.o: socket.c
	$(CC)  -o socket.o -c socket.c

main.o: main.c
	$(CC) -o main.o -c main.c

clean:
	rm -rf *.o

mrproper:
	rm -rf $(EXEC)
