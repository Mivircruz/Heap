CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion 
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = main.c heap.c testing.c pruebas_alumno.c
HFILES = heap.h testing.h 
EXEC = pruebas

build: $(CFILES) 
	$(CC) $(CFLAGS)  -o $(EXEC) $(CFILES) 

run: build
	./$(EXEC) 

valgrind: build
	valgrind $(VFLAGS) ./$(EXEC)

gdb: build
	gdb $(GDBFLAGS) ./$(EXEC)

zip: build
	zip $(EXEC).zip $(CFILES) $(HFILES)

clean:
	rm -f *.o $(EXEC)
