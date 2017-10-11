CC=gcc
EXEC=client

$(EXEC): main.c main.h
	$(CC) -o $(EXEC) main.c

clean: 
	rm -rf *.o

mrproper:
	rm -rf $(EXEC)
