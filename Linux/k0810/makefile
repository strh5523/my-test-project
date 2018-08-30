all : main

main : add.o main.o max.o
	gcc -o main add.o main.o max.o

add.o : add.c
	gcc -c add.c

main.o : main.c
	gcc -c main.c

max.o : max.c
	gcc -c max.c

clean :
	rm -rf *.o main
