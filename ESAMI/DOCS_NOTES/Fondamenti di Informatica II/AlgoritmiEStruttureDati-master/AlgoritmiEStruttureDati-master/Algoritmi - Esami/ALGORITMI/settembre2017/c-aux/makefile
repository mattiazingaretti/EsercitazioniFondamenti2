all: driver.o tree.o queue.o node.o printTree.o
	gcc -g -Wreturn-type -std=c99 -Wextra -o driver driver.o tree.o queue.o node.o printTree.o

driver.o: driver.c
	gcc -g -Wreturn-type -std=c99 -Wextra -c driver.c

tree.o: tree.h tree.c
	gcc -g -Wreturn-type -std=c99 -Wextra -c tree.c

node.o: node.h node.c
	gcc -g -Wreturn-type -std=c99 -Wextra -c node.c

queue.o: queue.h queue.c
	gcc -g -Wreturn-type -std=c99 -Wextra -c queue.c

clean:
	-rm ./*.o
	-rm driver
