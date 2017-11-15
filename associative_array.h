#ifndef ASSOCIATIVE_ARRAY
#define ASSOCIATIVE_ARRAY
#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"

typedef void* TREE;

TREE tree_init_default(void);

int tree_height(TREE hTree);

Status tree_add(TREE hTree, MY_STRING key, MY_STRING word);

int tree_size(TREE hTree);

GENERIC_VECTOR tree_largest_word_bin(TREE hTree);

Boolean tree_empty(TREE hTree);

void tree_destroy(TREE* phRoot);

#endif
