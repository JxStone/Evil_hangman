#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "generic.h"
#include "status.h"

#ifndef  CHAR_STRING
#define CHAR_STRING

struct string
{
    int size;
    int capacity;
    char* data;
};
typedef struct string String;


typedef void* MY_STRING;

MY_STRING my_string_init_default(void);

void my_string_destroy(ITEM* pItem);

MY_STRING my_string_init_c_string(const char* c_string);

int my_string_get_capacity(MY_STRING hMy_string);

int my_string_get_size(MY_STRING hMy_string);

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);

Status my_string_extraction(MY_STRING hMy_string, FILE* fp);

Status my_string_insertion(MY_STRING hMy_string, FILE* fp);

void my_string_increase_capacity(MY_STRING hMy_string);

Status my_string_push_back(MY_STRING hMy_string, char item);

Status my_string_pop_back(MY_STRING hMy_string);

char* my_string_at(MY_STRING hMy_string, int index);

char* my_string_c_str(MY_STRING hMy_string);

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend);

Boolean my_string_empty(MY_STRING hMy_string);

Status my_string_assignment(ITEM* phLeft, ITEM hRight);

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);

#endif
