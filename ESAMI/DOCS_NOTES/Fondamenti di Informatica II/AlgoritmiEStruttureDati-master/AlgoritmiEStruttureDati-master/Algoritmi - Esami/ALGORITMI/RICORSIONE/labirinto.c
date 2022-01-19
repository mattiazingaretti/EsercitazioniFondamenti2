#include "labirinto.h"

#include <stdlib.h>
#include <assert.h>

typedef struct {
    int n;
    int **matrix;
    int **marcata;
} labirinto_struct ;

labirinto * labirinto_new(int n) {
    // TODO: Da completare
    labirinto_struct * new_labirinto = (labirinto_struct *) malloc (sizeof(labirinto_struct));
    new_labirinto->n = n;
    new_labirinto->matrix = (int **) calloc(n, sizeof(int*));
    new_labirinto->marcata = (int **) calloc(n, sizeof(int*));
    int i,j;
	for (i = 0; i < n; i++) {
		new_labirinto->matrix[i] = (int *)calloc(n, sizeof(int));
		new_labirinto->marcata[i] = (int *)calloc(n, sizeof(int));
	}
    for (i = 0; i < n; i++) {
		for(j = 0; j<n; j++){
			new_labirinto->matrix[i][j] = LABIRINTO_VUOTA;
			new_labirinto->marcata[i][j] = LABIRINTO_FALSE;
		}
    }
    return (labirinto *) new_labirinto;
}


void labirinto_delete(labirinto * lab) {
    // TODO: Da completare
}

void labirinto_setpiena(labirinto * lab, int r, int c) {
    // TODO: Da completare
    labirinto_struct* labi = lab;
    labi->matrix[r][c] = LABIRINTO_PIENA;
}

int labirinto_uscita(labirinto * lab, int r, int c) {
    // TODO: Da completare
    labirinto_struct* labi = lab;
    int n = labi->n;
    if( r == n-1 && c== n-1) return 1;
	return 0;
}

int labirinto_percorribile(labirinto * lab, int r, int c) {
    // TODO: Da completare
    labirinto_struct* labi = lab;
    int n = labi->n;
    if( r < n && c< n && c>=0 && r>=0){
        if((labi->matrix[r][c]) == LABIRINTO_VUOTA){
            return 1;
        }
    }
	return 0;
}

void labirinto_setTrue(labirinto * lab, int r, int c) {
    // TODO: Da completare
    labirinto_struct* labi = lab;
    labi->marcata[r][c] = LABIRINTO_TRUE;
}

int labirinto_uscitaraggiungibileda(labirinto * lab, int r, int c) {
    // TODO: Da completare
    labirinto_struct* l = lab;
    labirinto_setTrue(lab,r,c);
    printf("%d, %d\n", r, c);
    int n = l->n;
    if((labirinto_percorribile(lab, n-1, n-1)) == 0) return 0;
    else if( labirinto_uscita(lab, r, c)){
            return 1;
     }
    else if((labirinto_percorribile(lab, r, c+1)) && ((l->marcata[r][c+1])!= LABIRINTO_TRUE)){
            labirinto_uscitaraggiungibileda(lab, r, c+1);
    }
    else if((labirinto_percorribile(lab, r+1, c)) &&((l->marcata[r+1][c])!= LABIRINTO_TRUE)){
            labirinto_uscitaraggiungibileda(lab,r+1,c);
    }
    else if((labirinto_percorribile(lab, r-1, c))&&((l->marcata[r-1][c])!= LABIRINTO_TRUE)){
            labirinto_uscitaraggiungibileda(lab,r-1,c);
    }
   else if((labirinto_percorribile(lab, r, c-1))&&((l->marcata[r][c-1])!= LABIRINTO_TRUE)){
            labirinto_uscitaraggiungibileda(lab,r,c-1);
    }

	else return 0;
}

int labirinto_risolvibile(labirinto * lab) {
    // TODO: Da completare
    if((labirinto_uscitaraggiungibileda(lab, 0, 0))==1) return LABIRINTO_TRUE;
	return LABIRINTO_FALSE;
}

void labirinto_tostring(labirinto * lab, char * buffer, int buffer_size) {
	labirinto_struct * ptr = (labirinto_struct *) lab;
        assert(buffer_size >= (ptr->n + 1) * ptr->n);
    buffer[0] = '\0';
    char *buffer_ptr = buffer;
    int i;
    for (i = 0; i < ptr->n; i++) {
        int j;
        for (j = 0; j < ptr->n; j++) {
            char c;
            if(ptr->matrix[i][j] == LABIRINTO_PIENA)
                c = '#';
            if(ptr->matrix[i][j] == LABIRINTO_VUOTA && ptr->marcata[i][j] == LABIRINTO_FALSE)
                c = '.';
            if(ptr->matrix[i][j] == LABIRINTO_VUOTA && ptr->marcata[i][j] == LABIRINTO_TRUE)
                c = '+';
            buffer_ptr[0] = c;
            buffer_ptr++;
        }
        buffer_ptr[0] = '\n';
        buffer_ptr++;
    }
    buffer_ptr[0] = '\0';
}
