all: driver.o bst.o
	gcc -g -Wall -o driver driver.o bst.o

driver.o: bst.h bst.o driver.c
	gcc -g -Wall -c driver.c

bst.o: bst.h bst.c
	gcc -g -Wall -c bst.c

clean:
	-rm ./*.o
	-rm driver
