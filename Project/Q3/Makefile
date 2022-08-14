FLAGS := -Wunused -Wall

all: StringPair StringPairList utils link

utils: utils.c	
	gcc -c $(FLAGS) utils.c

StringPairList: StringPairList.c
	gcc -c $(FLAGS) StringPairList.c

StringPair: StringPair.c
	gcc -c $(FLAGS) StringPair.c

link: cypher.c StringPairList.o StringPair.o utils.o
	gcc $(FLAGS) cypher.c -g -o cypher StringPairList.o utils.o StringPair.o

clean:
	rm *.o
	rm cypher
