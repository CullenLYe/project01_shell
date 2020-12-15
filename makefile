all: shell.o
	gcc -o shell shell1.c

shell.o: shell.c
	gcc -c shell1.c

run:
	./shell

clean:
	rm *.o
