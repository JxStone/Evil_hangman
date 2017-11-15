#include "associative_array.h"

struct node;
typedef struct node Node;

struct node
{
    MY_STRING data;
    GENERIC_VECTOR words;
    Node* left;
    Node* right;
    int height;
};

struct tree
{
    Node* root;
};
typedef struct tree Tree;

Node* left_rotation(Node* pRoot);
Node* right_rotation(Node* pRoot);
void destroy(Node* pRoot);
Status insert(Node** pNode, MY_STRING key, MY_STRING word);
int max(int a, int b);
int size(Node* pRoot);
int get_height(Node* pRoot);
GENERIC_VECTOR find_largest(Node* pRoot);


TREE tree_init_default(void)
{
    Tree* pTree = (Tree*)malloc(sizeof(Tree));
    if(pTree != NULL)
    {
        pTree->root = NULL;
    }
    return pTree;
}

int tree_height(TREE hTree)
{
    Tree* pTree = (Tree*)hTree;
    if(pTree == NULL)
    {
        return 0;
    }
    return get_height(pTree->root);
}

int get_height(Node* pRoot)
{
    if(pRoot == NULL)
    {
        return 0;
    }
    return pRoot->height;
}

int max(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    return b;
}

int get_balance(Node* pRoot)
{
    if(pRoot == NULL)
    {
        return 0;
    }
    return get_height(pRoot->left) - get_height(pRoot->right);
}

Node* left_rotation(Node* pRoot)
{
    Node* newRoot = pRoot;
    if(newRoot == NULL)
    {
        return NULL;
    }
    else if(newRoot->right == NULL)
    {
        return NULL;
    }
    else
    {
        newRoot = pRoot->right;
        pRoot->right = newRoot->left;
        newRoot->left = pRoot;
    
        pRoot->height = max(get_height(pRoot->left), get_height(pRoot->right)) + 1;
        newRoot->height = max(get_height(newRoot->left), get_height(newRoot->right)) + 1;
    }
    return newRoot;
}

Node* right_rotation(Node* pRoot)
{
    Node* newRoot = pRoot;
    if(newRoot == NULL)
    {
        return NULL;
    }
    else if(newRoot->left == NULL)
    {
        return NULL;
    }
    else
    {
        newRoot = pRoot->left;
    
        pRoot->left = newRoot->right;
        newRoot->right = pRoot;
    
        pRoot->height = max(get_height(pRoot->left), get_height(pRoot->right))+1;
        newRoot->height = max(get_height(newRoot->left), get_height(newRoot->right))+1;
    }
    
    return newRoot;
}

Status tree_add(TREE hTree, MY_STRING key, MY_STRING word)
{
    Tree* pTree = (Tree*)hTree;
    if(pTree == NULL)
    {
        return FAILURE;
    }
    
    return insert(&(pTree->root), key, word);
    /*
    Tree* pTree = (Tree*)hTree;
    int balance;
    
    if (pTree->root== NULL)
    {
        pTree->root = (Node*)malloc(sizeof(Node));
        if (pTree->root == NULL)
        {
            return FAILURE;
        }
        pTree->root->left= NULL;
        pTree->root->right = NULL;
        pTree->root->data = my_string_init_c_string(my_string_c_str(key));

        pTree->root->words = generic_vector_init_default(my_string_assignment, my_string_destroy);
        generic_vector_push_back(pTree->root->words, word);
    }
    else
    {
        if(my_string_compare(pTree->root->data, key) > 0)
        {
            tree_add(&(pTree->root->right), key, word);
        }
        else if(my_string_compare(pTree->root->data, key) < 0)
        {
            tree_add(&(pTree->root->left), key, word);
        }
        else if(my_string_compare(pTree->root->data, key) == 0)
        {
            generic_vector_push_back(pTree->root->words, word);
        }
        else
        {
            return FAILURE;
        }
        
     
        
        pTree->root->height = 1 + max(get_height(pTree->root->left), get_height(pTree->root->right));
     
        balance = get_balance(pTree->root);
     
        if(balance < -1 && my_string_compare(word, pTree->root->data) > 0)
        {
            left_rotation(pTree->root);
        }
        else if(balance > 1 && my_string_compare(word, pTree->root->data) < 0)
        {
            right_rotation(pTree->root);
        }
        else if(balance > 1 && my_string_compare(word, pTree->root->data) > 0)
        {
            pTree->root->left = left_rotation(pTree->root->left);
            right_rotation(pTree->root);
        }
        else if(balance < -1 && my_string_compare(word, pTree->root->data) < 0)
        {
            pTree->root->right = right_rotation(pTree->root->right);
            left_rotation(pTree->root);
        }
        
    }
    */
}


Status insert(Node** pRoot, MY_STRING key, MY_STRING word)
{
    int balance;
    
    if(*pRoot == NULL)
    {
        *pRoot = (Node*)malloc(sizeof(Node));
        if(*pRoot == NULL)
        {
            printf("failed to create a node!\n");
            return FAILURE;
        }
            
        (*pRoot)->data = my_string_init_c_string(my_string_c_str(key));
        (*pRoot)->words = generic_vector_init_default(my_string_assignment, my_string_destroy);
        (*pRoot)->left = NULL;
        (*pRoot)->right = NULL;
        (*pRoot)->height = 1;
        
        generic_vector_push_back((*pRoot)->words, word);
        return SUCCESS;
    }
    else
    {
        if(my_string_compare((*pRoot)->data, key) < 0)
        {
            insert(&((*pRoot)->left), key, word);
        }
        else if(my_string_compare((*pRoot)->data, key) > 0)
        {
            insert(&((*pRoot)->right), key, word);
        }
        else if(my_string_compare((*pRoot)->data, key) == 0)
        {
            generic_vector_push_back((*pRoot)->words, word);
        }
        else
        {
            return FAILURE;
        }

        
        
        (*pRoot)->height = max(get_height((*pRoot)->left), get_height((*pRoot)->right)) + 1;
        
        balance = get_balance(*pRoot);
        
        if(balance < -1 && my_string_compare((*pRoot)->right->data, word) > 0)
        {
            *pRoot = left_rotation(*pRoot);
            return SUCCESS;
        }
        if(balance > 1 && my_string_compare((*pRoot)->left->data, word) < 0)
        {
            *pRoot = right_rotation(*pRoot);
            return SUCCESS;
        }
        if(balance > 1 && my_string_compare((*pRoot)->left->data, word) > 0)
        {
            (*pRoot)->left = left_rotation((*pRoot)->left);
            *pRoot = right_rotation(*pRoot);
            return SUCCESS;
        }
        if(balance < -1 && my_string_compare((*pRoot)->right->data, word) < 0)
        {
            (*pRoot)->right = right_rotation((*pRoot)->right);
            *pRoot = left_rotation(*pRoot);
            return SUCCESS;
        }
        
        return SUCCESS;
     }
}


int tree_size(TREE hTree)
{
    Tree* pTree = (Tree*)hTree;
    if(pTree == NULL)
    {
        return 0;
    }
    return size(pTree->root);
}

int size(Node* pRoot)
{
    if(pRoot == NULL)
    {
        return 0;
    }
    return 1 + size(pRoot->left) + size(pRoot->right);
}

void tree_destroy(TREE* phRoot)
{
    Tree* pRoot = (Tree*)*phRoot;
    
    if(pRoot->root != NULL)
    {
        destroy(pRoot->root);
        free(pRoot);
        *phRoot = NULL;
    }
}

void destroy(Node* pRoot)
{
    if(pRoot == NULL)
    {
        return;
    }
    else
    {
        generic_vector_destroy(&(pRoot->words));
        destroy(pRoot->left);
        destroy(pRoot->right);
        my_string_destroy(&(pRoot->data));
        free(pRoot);
    }
}

GENERIC_VECTOR tree_largest_word_bin(TREE hTree)
{
    Tree* pMy_tree = (Tree*)hTree;
    GENERIC_VECTOR return_vector = NULL;
    GENERIC_VECTOR temp;
    int i;
    temp = find_largest(pMy_tree->root);
    return_vector = generic_vector_init_default(my_string_assignment, my_string_destroy);
    for (i = 0; i < generic_vector_get_size(temp); i++) {
        generic_vector_push_back(return_vector, generic_vector_at(temp, i));
    }
    return return_vector;
}

GENERIC_VECTOR find_largest(Node* pRoot)
{
    Vector* temp = NULL;
    int elements_in_currentNode;
    
    {
        elements_in_currentNode = generic_vector_get_size(pRoot->words);
        // assumed to be the root at first.
        if (pRoot->left != NULL) {
            temp = find_largest(pRoot->left);
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->words)) {
                // fprintf(fp1,("First\n");
                temp = pRoot->words;
            }
        }
        if (pRoot->right != NULL) {
            temp = find_largest(pRoot->right);
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->words)) {
                // fprintf(fp1,("Second\n");
                temp = pRoot->words;
            }
        }
        if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->words)) {
            // fprintf(fp1,("Third\n");
            temp = pRoot->words;
        }
    }
    
    
    my_string_insertion(pRoot->data, stdout);
    printf(" %d\n", elements_in_currentNode);
    
    return temp;
}


Boolean tree_empty(TREE hTree)
{
    Tree* pTree = (Tree*)hTree;
    
    return (Boolean)(pTree->root == NULL);
}

