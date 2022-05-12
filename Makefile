

build:
	gcc -c main.c
	gcc -c database.c
	gcc database.o main.o -o database

clean:
	rm *.o database
