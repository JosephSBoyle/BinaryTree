#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include "binary_tree.c"


/* Create a new binary tree. Errors if allocating memory for the tree fails */
struct Node* bt_create(void);

/* Free the memory of a binary tree */
void bt_free(struct Node* binary_tree);

/* Get the child index of a Node, returning -1 if no such child exists */
long bt_get_child_idx(const size_t parent_idx, bool right_node);

/* Get the parent index of a Node, returns -1 if called on the root Node */
long bt_get_parent_idx(const size_t child_idx);


/////* HELPERS */////
/* Get the child Node of a Node */
struct Node* bt_get_child(const struct Node* binary_tree, const size_t parent_idx, bool right_node);

/* Get the parent of a Node */
struct Node* bt_get_parent(const struct Node* binary_tree, const size_t child_idx);

/* Pretty print a binary tree to stdout. */
void bt_pretty_print(const struct Node* binary_tree);


//////* SEARCH ALGORITHMS *//////
struct Node* bt_breadth_first_search(const struct Node* binary_tree, char* target);
struct Node* bt_depth_first_search(const struct Node* binary_tree, char* target);

#endif