#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"


MY_STRING my_string_init_default(void)
{
    String* pString = (String*) malloc(sizeof(String));
    if(pString != NULL)
    {
        pString->size = 0;
        pString->capacity = 7;
        pString->data = (char*) malloc(sizeof(char) * pString->capacity);
        if(pString->data == NULL)
        {
            free(pString);
            return NULL;
        }
    }
    return pString;
}

void my_string_destroy(ITEM* phItem)
{
    String* pItem = (String*)*phItem;
    
    if(pItem != NULL)
    {
        free(pItem->data);
        free(pItem);
        *phItem = NULL;
    }
}

MY_STRING my_string_init_c_string(const char* c_string)
{
    int size = 0;
    while(c_string[size] != 0)
    {
        size++;
    }
    
    String* pString = (String*)malloc(sizeof(String));
    if(pString != NULL)
    {
        pString->size = size;
        pString->capacity = size+1;
        pString->data = (char*)malloc(sizeof(char) * pString->capacity);
        if(pString->data == NULL)
        {
            free(pString);
            return NULL;
        }
    }
    for(int i = 0; i <= pString->size; i++)
    {
        pString->data[i] = c_string[i];
    }
    
    return pString;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
    String* pString = (String*) hMy_string;
    return pString->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
    String* pString = (String*)hMy_string;
    return pString->size;
}

void my_string_increase_capacity(MY_STRING hMy_string)
{
    String* pMy_string = (String*) hMy_string;
    char* temp;
    int i;
    
    temp = (char*) malloc(sizeof(char)* pMy_string->capacity * 2);
    if(temp != NULL)
    {
        for(i = 0; i < pMy_string->size; i++)
        {
            temp[i] = pMy_string->data[i];
        }
    }
    free(pMy_string->data);
    pMy_string->data = temp;
    pMy_string->capacity *= 2;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
    String* pLeft = (String*)hLeft_string;
    String* pRight = (String*)hRight_string;
    int i;
    
    for (i = 0; i < pLeft->size && i < pRight->size; i++)
    {
        if (pLeft->data[i] < pRight->data[i]) {
            return -1;
        }
        else if (pLeft->data[i] > pRight->data[i]) {
            return 1;
        }
    }
    
    return 0;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
    String* pString = (String*)hMy_string;
    if(fp == NULL)
    {
        return FAILURE;
    }
    
    pString->size = 0;
    char ch;
    
    if(fscanf(fp," %c",&ch) != EOF)
    {
        while(ch != ' ' && ch != '\n' && ch != '\t')
        {
            if(pString->size >= pString->capacity)
            {
                my_string_increase_capacity(pString);
            }
            pString->data[pString->size] = ch;
            pString->size++;
            ch = fgetc(fp);
        }
    }
    else
    {
        return FAILURE;
    }
    
    if(pString->size != 0)
    {
        return SUCCESS;
    }
    return FAILURE;
    
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
    String* pMy_string = (String*)hMy_string;
    if(pMy_string->size == 0)
    {
        return FAILURE;
    }
    
    for(int i = 0; i < pMy_string->size; i++)
    {
        fputc(pMy_string->data[i],fp);
    }
    return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
    String* pString = (String*) hMy_string;
    char* temp;
    int i;
    
    if(pString->size >= pString->capacity)
    {
        temp = (char*) malloc(sizeof(char)* pString->capacity * 2);
        if(temp == NULL)
        {
            free(temp);
            return FAILURE;
        }
        for(i = 0; i < pString->size; i++)
        {
            temp[i] = pString->data[i];
        }
        free(pString->data);
        pString->data = temp;
        pString->capacity *= 2;
    }
    pString->data[pString->size] = item;
    pString->size++;
    return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
    String* pString = (String*) hMy_string;
    
    if(pString->size == 0)
    {
        return FAILURE;
    }
    pString->size--;
    return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
    String* pString = (String*) hMy_string;
    
    if(index >= pString->size)
    {
        return NULL;
    }
    return &(pString->data[index]);
}

char* my_string_c_str(MY_STRING hMy_string)
{
    /*
    String* pString = (String*)hMy_string;
    pString->data[pString->size] = '\0';
    return pString->data;
     */
    char* tempArray;
    int i;
    String* pMy_string = (String*)hMy_string;
    if (pMy_string->size + 1 > pMy_string->capacity) { //resize
        tempArray = (char*)malloc(sizeof(char) * 2 * pMy_string->capacity);
        if (tempArray == NULL) {
            free(tempArray);
            return tempArray;
        }
        for (i = 0; i < pMy_string->capacity; i++) {
            tempArray[i] = pMy_string->data[i];
        }
        free(pMy_string->data); pMy_string->data = NULL;
        pMy_string->data = tempArray;
        tempArray = NULL;
        pMy_string->capacity *= 2;
    }
    pMy_string->data[pMy_string->size] = '\0';
    return pMy_string->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
    String* pString = (String*) hResult;
    String* pAppend = (String*) hAppend;
    char* temp;
    int i;
    
    if(pAppend->size >= 0)
    {
        temp = (char*) malloc(sizeof(char)* pString->capacity * 2);
        if(temp == NULL)
        {
            return FAILURE;
        }
        for( i = 0; i < pAppend->size; i++)
        {
            temp[i] = pAppend->data[i];
            my_string_push_back(pString, temp[i]);
        }
        free(temp);
        return SUCCESS;
    }
    return FAILURE;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
    String* pString = (String*) hMy_string;
    
    return (Boolean)(pString->size == 0);
}

Status my_string_assignment(ITEM* phLeft, ITEM hRight)
{
    /*
    String* pLeft = (String*)*phLeft;
    String* pRight = (String*)hRight;
    int i;
    
    if(pLeft == NULL)
    {
        pLeft = my_string_init_default();
        if(pLeft == NULL)
        {
            return FAILURE;
        }
    }
    
    for(i = 0; i < pLeft->size; i++)
    {
        my_string_pop_back(pLeft);
    }
    
    for(i = 0; i < pRight->size; i++)
    {
        my_string_push_back(pLeft, pRight->data[i]);
    }
    
    *phLeft = pLeft;
    
    return SUCCESS;
     */
    String* pMy_string_left = (String*)*phLeft;
    String* pMy_string_right = (String*)hRight;
    int i;
    const char* temp;
    
    temp = my_string_c_str((MY_STRING)hRight);
    
    if (pMy_string_left == NULL) {
        pMy_string_left = my_string_init_c_string(temp);
    }
    else {
        pMy_string_left->size = 0;
        for (i = 0; i < pMy_string_right->size + 1; i++) {
            my_string_push_back(pMy_string_left, pMy_string_right->data[i]);
        }
    }
    *phLeft = pMy_string_left;

    return SUCCESS;
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
    String* pNew_key = (String*)new_key;
    String* pWord = (String*)word;
    int i;

    guess = tolower(guess);
    
    my_string_assignment(&new_key, current_word_family);
    
    for(i = 0; i < pWord->size; i++)
    {
        if(pWord->data[i] == guess)
        {
            pNew_key->data[i] = guess;
        }
    }
    
    return SUCCESS;
}
