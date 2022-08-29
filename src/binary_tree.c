/* Binary tree of max depth `n` represented as a fixed-length array.
 * Empty nodes will be represented by a special sentinal node.
 * Knowledge of where a node's children are is implicit (citation needed),
 * and is computed using the position of the parent node.
 */
// start= 10.30 am
// end= 1.40pm
// start= 10.30 am
// DFS finished 11.30am
// 12.47 refactored and added header file.
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include <stdio.h>
#include <stddef.h>

#define TREE_HEIGHT      4 
#define N_ELEMENTS       15  // (2^TREE_HEIGHT) - 1
#define MAX_ROW_ELEMENTS 7   // 2^(TREE_HEIGHT-1)
#define N_CHARS          5
#define BUFFER_SIZE      127


typedef struct Node{
    char value[N_CHARS];
} Node;


/* Create a fixed-size binary tree */
Node* bt_create(void){
    Node* node_array = malloc(sizeof(Node) * N_ELEMENTS);
    if (node_array == NULL){
        printf("ERROR - FAILED TO ALLOCATE BINARY TREE\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i=0; i<N_ELEMENTS; i++){
        char buffer [N_CHARS];

        snprintf(buffer, N_CHARS, "%lu", i);
        strcpy(node_array[i].value, buffer);
    }

    printf("binary tree initialized\n");
    return node_array;
}

/* Free the memory of a fixed-size binary tree */
void bt_free(Node* binary_tree){
    free(binary_tree);
}

/* Get the child index of a node, or -1 if no such child exists */
long bt_get_child_idx(const size_t parent_idx, bool right_node){
    long child_idx = (2 * parent_idx) + 1 + right_node;
    if (child_idx >= N_ELEMENTS){
        // this node has no children!
        return -1;
    }
    return child_idx;
}

/* Get the left or right child of a node */
Node* bt_get_child(const Node* binary_tree, const size_t parent_idx, bool right_node){
    long child_idx = bt_get_child_idx(parent_idx, right_node);
    if (child_idx == -1){
        printf("ERROR - this node has no children!\n");
        exit(EXIT_FAILURE);
    }
    return &binary_tree[child_idx];
}

long bt_get_parent_idx(const size_t child_idx){
    if (child_idx == 0){
        // root node has no parent!
        return -1;
    }
    return (long)(child_idx - 1) / 2;
}

/* Get the parent of a given node */
Node* bt_get_parent(const Node* binary_tree, const size_t child_idx){
    long parent_idx = bt_get_parent_idx(child_idx);
    if (parent_idx == -1){
        printf("ERROR - the root node has no parent node!\n");
        exit(EXIT_FAILURE);
    }
    return &binary_tree[parent_idx];
}

/* Return the node whose value matches a given string, else NULL. */
Node* bt_breadth_first_search(const Node* binary_tree, char* target){
    for (size_t i=0; i<N_ELEMENTS; i++){
        if (!strcmp(binary_tree[i].value, target)){
            return &binary_tree[i]; 
        }
    }
    return NULL;
}

/* Return the node whose value matches a given string, else NULL. */
Node* bt_depth_first_search(const Node* binary_tree, char* target){
    u_int8_t visited_nodes[N_ELEMENTS] = {0}; // No nodes have been visited
    
    // the current node index
    size_t idx = 0;
    long lchild_idx;
    long rchild_idx;
    
    while (true){
        if (strcmp(binary_tree[idx].value, target) == 0){
            return &binary_tree[idx];
        }

        visited_nodes[idx] = 1;
        lchild_idx = bt_get_child_idx(idx, false);
        rchild_idx = bt_get_child_idx(idx, true);
        
        // Find the next index to check
        if (lchild_idx >= 0 &&
            !visited_nodes[lchild_idx]){
            // continue from the left subtree
            idx = lchild_idx;
            continue;
        } else if
           (rchild_idx >= 0 &&
            !visited_nodes[rchild_idx]){
            // continue from the right subtree
            idx = rchild_idx;
            continue;
        }
        // go back up the tree.
        idx = bt_get_parent_idx(idx);
        if (idx == 0 &&
            visited_nodes[1] &&
            visited_nodes[2]
            ){
            // if we're at the first node and both subtrees have been marked as visited,
            // we have checked all nodes in the tree.
            return NULL;
        }
    }
}

void bt_pretty_print(const Node* binary_tree){
    size_t c = 1; // the number of nodes at the current level of the tree
    size_t elems_per_row = 1;
    size_t spacing = BUFFER_SIZE / (elems_per_row * 2);
    
    char row_buffer[BUFFER_SIZE] = "";
    
    for (size_t i=0; i<BUFFER_SIZE; i++){
        row_buffer[i] = '_';
    }
    for (size_t i=0; i<N_ELEMENTS; i++, c++){
        row_buffer[c*spacing] = binary_tree[i].value[0];
        for (size_t j=0; binary_tree[i].value[j] != '\0'; j++){
            row_buffer[c*spacing + j] = binary_tree[i].value[j];
        }

        if (c == elems_per_row){
            // this row has been fully traversed
            printf("\n|%s", row_buffer);
            printf("\n|");

            // update the state to handle the next row.
            c = 0;
            elems_per_row *= 2;
            for (size_t i=0; i<BUFFER_SIZE; i++){
                row_buffer[i] = '_';
            }
            // compute the size of each space in the next row.
            spacing = BUFFER_SIZE / (elems_per_row + 1);
        }
    }
}


int main(int argc, char** argv){
    Node* binary_tree = bt_create();
    Node* left_child = bt_get_child(binary_tree, 0, 0);
    Node* right_child = bt_get_child(binary_tree, 0, 1);

    printf("<%s>\n", left_child->value);
    printf("<%s>\n", right_child->value);

    // check that the parent nodes are correct.
    Node* parent = bt_get_parent(binary_tree, 1);
    printf("<%s>\n", parent->value);
    parent = bt_get_parent(binary_tree, 2);
    printf("<%s>\n", parent->value);

    // search for a value that exists in the tree
    printf("Searching for: 14...\n");
    Node* bfs_match = bt_breadth_first_search(binary_tree, "14");
    printf(bfs_match ? "A match was found!\n" : "No match found.\n");

    Node* dfs_match = bt_depth_first_search(binary_tree, "14");
    printf(dfs_match ? "A match was found!\n" : "No match found.\n");

    // search for a value that **doesn't** exist in the tree
    printf("Searching for: 21...\n");
    bfs_match = bt_breadth_first_search(binary_tree, "21");
    printf(bfs_match ? "A match was found!\n" : "No match found.\n");

    dfs_match = bt_depth_first_search(binary_tree, "21");
    printf(dfs_match ? "A match was found!\n" : "No match found.\n");


    // print and free the tree.
    bt_pretty_print(binary_tree);
    bt_free(binary_tree);
}