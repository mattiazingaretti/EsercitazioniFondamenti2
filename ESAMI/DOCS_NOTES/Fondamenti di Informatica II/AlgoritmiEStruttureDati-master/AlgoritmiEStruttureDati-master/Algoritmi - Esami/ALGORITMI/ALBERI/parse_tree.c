#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "parse_tree.h"

char * next_line(char * buffer, int size) {

	size_t s = size;
	ssize_t res = getline(&buffer, &s, stdin);
	if (res >= 0)
		return buffer;
	else
		return NULL;
}

int parse_int(char * buffer) {
	return atoi(buffer);
}

int get_depth_line(char * buffer) {
	char lvlchar[1] = "-";
	return strspn(buffer, lvlchar);
}

node_tree * parse_tree() {
    int size = 128;
    char* buf = malloc(size);
    char* b = next_line(buf, size);
    node_tree* root = NULL;

    if(b!= NULL){
        int trat = get_depth_line(b);
        root = new_node_tree(parse_int(buf + trat));
    }
    free(buf);
	return root;
}


