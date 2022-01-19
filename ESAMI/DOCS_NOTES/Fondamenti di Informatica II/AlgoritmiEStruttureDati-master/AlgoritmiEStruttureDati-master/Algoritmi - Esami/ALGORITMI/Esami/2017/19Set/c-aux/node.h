#ifndef NODEH
#define NODEH

typedef struct Node {
    char *nome;
    struct Node *parent;
    struct Node *firstChild;
    struct Node *nextSibling;
    int size;
    int isDir;
} Node;

Node *newNode(char *n, int s, int isD);
int illegalName(char *s);
int getIsDir(Node *v);

#endif