#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "iter_postorder.h"
#include "stack.h"

void iterative_postorder_visit(node_tree * node) {
    stack* s = new_stack();
    char from_stack = 0;

    while(stack_size(s) > 0 || node != NULL){
        if( node != NULL){
            if(from_stack== 0 && get_first_child(node) != NULL){
                stack_push(s, node);
                node = get_first_child(node);
            }
            else {
                printf("visito nodo %d\n", get_node_info(node));
                node = get_next_sibling(node);
            }
        }
        if(node == NULL){
            node = stack_pop(s);
            from_stack = 1;
        }
        else from_stack = 0;
    }
    delete_stack(s);
}
