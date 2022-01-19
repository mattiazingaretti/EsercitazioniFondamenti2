all: driver.o bst.o bstnode.o
	gcc -Wall -g -o driver bst.o driver.o bstnode.o -lm

driver.o: driver.c
	gcc -Wall -g -c -lm driver.c

bst.o: bst.h bst.c
	gcc -Wall -g -c -lm bst.c

bstnode.o: bstnode.h bstnode.c
	gcc -Wall -g -c -lm bstnode.c

clean:
	-rm ./*.o
	-rm test
