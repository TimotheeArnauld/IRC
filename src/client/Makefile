CC=gcc
EXEC=client

$(EXEC): font.o main.c main.h
	$(CC) -o $(EXEC) ../lib/fonts/font.o main.c

font.o: ../lib/fonts/font.c
	$(CC) -o ../lib/fonts/font.o -c ../lib/fonts/font.c

clean: 
	rm -rf *.o

mrproper:
	rm -rf $(EXEC)
