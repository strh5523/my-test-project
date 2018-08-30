all: main

main: main.o add.o max.o
	gcc -o main main.o max.o add.o
main.o: main.c
	gcc -c main.c
max.o: max.c
	gcc -c max.c
add.o: add.c
	gcc -c add.c
clean:
	rm -rf *.o main

