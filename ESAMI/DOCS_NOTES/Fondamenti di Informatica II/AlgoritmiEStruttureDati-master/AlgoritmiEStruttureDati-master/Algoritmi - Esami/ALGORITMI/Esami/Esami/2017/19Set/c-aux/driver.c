#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "tree.h"

#define MAXDIRS 300
#define MAXFILES 300
#define MAXSTR 100

static int nextInt(int min, int max) { // min incluso, max escluso
    return (rand() % (max - min)) + min;
}

int main(int argc, char** argv) {
    Tree *t = newTree();
    Node *directories[MAXDIRS]; int dCount = 0;
    Node *files[MAXDIRS]; int fCount = 0;
    char str[MAXSTR];
    
    srand(20170919);
    
    directories[dCount++] = t->root;

    int i;
    int indexParent;
    Node *nuovoNodo;
    for (i = 0; i < 30; i++) {
        indexParent = nextInt(0, dCount);
        if (nextInt(1, 1000) < 300) {
            sprintf(str, "dir%d", i);
            nuovoNodo = insertDir(t, directories[indexParent], str);
            directories[dCount++] = nuovoNodo;
        } else {
            int size = nextInt(1, 1024+512);
            sprintf(str, "file%d.txt", i);
            nuovoNodo = insertFile(t, directories[indexParent], str, size);
            files[fCount++] = nuovoNodo;
        }
    }
    indexParent = nextInt(0, dCount);
    nuovoNodo = insertDir(t, directories[indexParent], "sameName");
    for (i = 0; i < 5; i++) {
        indexParent = nextInt(0, dCount);
        int size = nextInt(1, 1024+512);
        nuovoNodo = insertFile(t, directories[indexParent], "sameName", size);
    }

    printf("\n File System: \n");
    printTree(t);

    printf("\n findAll test: \n");
    for (i = 0; i < dCount; i++){
        printf("Searching %s\n", directories[i]->nome);
        findAll(t, directories[i]->nome);
    }
    for (i = 0; i < fCount; i++){
        printf("Searching %s\n", files[i]->nome);
        findAll(t, files[i]->nome);
    }
    printf("Searching sameName\n");
    findAll(t, "sameName");
        
    printf("\n Pulizia cartelle: \n");
    int rimosso = cleanSmallDirs(t, 2000);
    printf("\t Cancellati %d Bytes\n", rimosso);

    printf("\n Nuovo File System: \n");
    printTree(t); 
    
    return 0;
}
