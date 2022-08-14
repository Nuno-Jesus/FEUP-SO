FLAGS := -Wunused -Wall

all: matrix utils link

matrix: matrix.c	
	gcc -c $(FLAGS) matrix.c

utils: utils.c
	gcc -c $(FLAGS) utils.c

link: addmx.c matrix.o utils.o
	gcc $(FLAGS) addmx.c -o addmx matrix.o utils.o

clean:
	rm addmx
	rm matrix.o
	rm utils.o