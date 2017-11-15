#include <stdlib.h>
#include <string.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
  MY_STRING hString = NULL;

  hString = my_string_init_default();

  if(hString == NULL)
    {
      my_string_destroy(&hString);
      strncpy(buffer, "test_init_default_returns_nonNULL\n"
	      "my_string_init_default returns NULL", length);
      return FAILURE;
    }
  else
    {
      my_string_destroy(&hString);
      strncpy(buffer, "test_init_default_returns_nonNULL\n", length);
      return SUCCESS;
    }
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_default();

   if(my_string_get_size(hString) != 0)
     {
       status = FAILURE;
       printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
       strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	       "Did not receive 0 from get_size after init_default\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status;
}

Status test_init_default_get_capacity_returns_7(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_default();

   if(my_string_get_capacity(hString) != 7)
     {
       status = FAILURE;
       printf("Expected a capacity of 7  but got %d\n", my_string_get_capacity(hString));
       strncpy(buffer, "test_init_default_get_capacity_returns_7\n"
	       "Did not receive 7 from get_capacity after init_default\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_init_default_get_capacity_returns_7\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status;  
}

Status test_jshi_destroy_set_to_NULL(char*buffer,int length)
{
  MY_STRING hString = NULL;

  hString = my_string_init_default();
  my_string_destroy(&hString);

  if(hString != NULL)
    {
      strncpy(buffer, "test_jshi_destroy_set_to_NULL\n"
	      "my_string_destroy doesn't set to NULL", length);
      return FAILURE;
    }
  else
    {
      strncpy(buffer, "test_jshi_destroy_set_to_NULL\n", length);
      return SUCCESS;
    }
}

Status test_jshi_init_c_string_returns_nonNULL(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_c_string("hi");

  if(hString == NULL)
     {
       status = FAILURE;
       printf("Expected init c string returns nonNULL\n");
       strncpy(buffer, "test_jshi_init_c_string_capacity_1_greater_than_size\n"
	       "init_c_string returns NULL\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_jshi_init_c_string_returns_nonNULL\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status; 
}
Status test_jshi_init_c_string_capacity_one_greater_than_size(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_c_string("hi");

  if(my_string_get_capacity(hString) - my_string_get_size(hString) != 1)
     {
       status = FAILURE;
       printf("Expected capacity to be 1 greater than size but got %d\n", my_string_get_capacity(hString) - my_string_get_size(hString));
       strncpy(buffer, "test_jshi_init_c_string_capacity_1_greater_than_size\n"
	       "Did not get capacity to be one greater than size\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_jshi_init_c_string_capacity_one_greater_than_size\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status; 
}

Status test_jshi_get_capacity_returns_integer(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_c_string("hi");

  if(sizeof(my_string_get_capacity(hString)) != sizeof(int))
     {
       status = FAILURE;
       printf("Expected to return an integer of the object's capacity");
       strncpy(buffer, "test_jshi_get_capacity_returns_integer\n"
	       "Did not return an integer value of the object's capacity\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_jshi_get_capacity_returns_integer\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status; 
}

Status test_jshi_get_size_returns_integer(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_c_string("hi");

  if(sizeof(my_string_get_capacity(hString)) != sizeof(int))
     {
       status = FAILURE;
       printf("Expected to return an integer of the object's size");
       strncpy(buffer, "test_jshi_get_size_returns_integer\n"
	       "Did not return an integer value of the object's size\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_jshi_get_size_returns_integer\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status;   
}

Status test_jshi_compare_returns_size_difference(char* buffer, int length)
{
  MY_STRING hLeftString = my_string_init_c_string("app");;
  MY_STRING hRightString = my_string_init_c_string("apple");
  Status status;

  if(my_string_compare(hLeftString, hRightString) >= 0)
     {
       status = FAILURE;
       printf("Expected to return negative number but get %d\n", my_string_compare(hLeftString, hRightString));
       strncpy(buffer, "test_jshi_compare_returns_size_difference\n"
	       "Did not get left string size less than right string size\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_jshi_compare_returns_size_difference\n"
	       , length);
     }

   my_string_destroy(&hLeftString);
   my_string_destroy(&hRightString);
   return status; 
}

Status test_jshi_extraction_ignores_leading_space(char* buffer, int length)
{
  MY_STRING hString = NULL;
  FILE* fp;
  Status status;

  hString = my_string_init_default();
  fp = fopen("test.txt", "w");
  fputs("  Hello", fp);

  my_string_extraction(hString, fp);
  
  if(hString == NULL)
    {
      status = FAILURE;
      printf("Expected a character but got space");
      strncpy(buffer, "test_jshi_extraction_ignores_leading_space\n"
	      "Did not skip leading space\n",length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_jshi_extraction_ignores_leading_space\n"
	      , length);
    }

  my_string_destroy(&hString);
  fclose(fp);
  return status;
}

Status test_jshi_extraction_read_non_empty_string(char* buffer, int length)
{
  MY_STRING hString = NULL;
  FILE* fp;
  Status status;

  hString = my_string_init_default();
  fp = fopen("dictionary.txt", "r");

  my_string_extraction(hString, fp);

  if(my_string_get_size(hString) == 0)
    {
      status = FAILURE;
      printf("Expected non empty string but the size is %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_jshi_extraction_read_non_empty_string\n"
	      "Did not read non empty string\n",length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_jshi_extraction_read_non_empty_string\n"
	      , length);
    }

  my_string_destroy(&hString);
  fclose(fp);
  return status;
}

Status test_jshi_extraction_empty_file_returns_FAILURE(char* buffer, int length)
{
  MY_STRING hString = NULL;
  FILE* fp;
  Status status;

  hString = my_string_init_default();
  fp = fopen("test1.txt", "w");

  if(my_string_extraction(hString, fp))
    {
      status = FAILURE;
      printf("Expected FAILURE for empty file\n");
      strncpy(buffer, "test_jshi_extraction_empty_file_returns_FAILURE\n"
	      "Did not return FAILURE when reading empty file\n",length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_jshi_extraction_empty_file_returns_FAILURE\n"
	      , length);
    }

  my_string_destroy(&hString);
  fclose(fp);
  return status;
}

Status test_jshi_insertion_empty_string_returns_FAILURE(char* buffer, int length)
{
  MY_STRING hString = NULL;
  FILE* fp;
  Status status;

  hString = my_string_init_default();
  fp = fopen("test2.txt", "w");

  if(my_string_extraction(hString, fp))
    {
      status = FAILURE;
      printf("Expected FAILURE when read empty string\n");
      strncpy(buffer, "test_jshi_insertion_empty_string_returns_FAILURE\n"
	      "Did not return FAILURE when reading empty string\n",length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_jshi_insertion_empty_string_returns_FAILURE\n"
	      , length);
    }

  my_string_destroy(&hString);
  fclose(fp);
  return status;
}

Status test_jshi_insertion_successfully_write_string(char* buffer, int length)
{
  MY_STRING hString = NULL;
  FILE* fp;
  Status status;

  hString = my_string_init_default();
  fp = fopen("dictionary.txt", "r");

  my_string_extraction(hString, fp);

  if(my_string_insertion(hString, stdout) == FAILURE)
    {
      status = FAILURE;
      printf("Expected to write the string \n");
      strncpy(buffer, "test_jshi_insertion_successfully_write_string\n"
	      "Did not write the string\n",length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_jshi_insertion_successfully_write_string\n"
	      , length);
    }

  my_string_destroy(&hString);
  fclose(fp);
  return status;  
}

Status test_jshi_push_back_resize(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_default();

   if(my_string_push_back(hString, 'a') == FAILURE)
     {
       status = FAILURE;
       printf("Expected a resize but failed\n");
       strncpy(buffer, "test_jshi_push_back_resize\n"
	       "Did not resize when not enough room\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_jshi_push_back_resize\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status;
}

Status test_jshi_push_back_double_capacity(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("hi");
   int capacity_before = my_string_get_capacity(hString);

   my_string_push_back(hString, 'a');
   my_string_push_back(hString, 'b');
   int capacity_after = my_string_get_capacity(hString);

   if(capacity_after/capacity_before != 2)
     {
       status = FAILURE;
       printf("Expected to double the capacity but failed\n");
       strncpy(buffer, "test_jshi_push_back_double_capacity\n"
	       "Did not resize and double the capacity when size exceeds the capacity\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_jshi_push_back_double_capacity\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status;  
}

Status test_jshi_push_back_place_item_at_end(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_default();

   my_string_push_back(hString, 'a');
   if(my_string_empty(hString))
     {
       status = FAILURE;
       printf("Expected the character to be at the end but have %s\n", my_string_at(hString, my_string_get_size(hString)-1));
       strncpy(buffer, "test_jshi_push_back_place_character_at_end\n"
	       "Did not place the character at the end of the string\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_jshi_push_back_place_character_at_end\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status;
}

Status test_jshi_pop_back_remove_last_character(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString =my_string_init_default();

   my_string_push_back(hString, 'a');

   my_string_pop_back(hString);
   
   if(my_string_get_size(hString) != 0)
     {
       status = FAILURE;
       printf("Expected the last character to be removed\n");
       strncpy(buffer, "test_jshi_pop_back_remove_last_character\n"
	       "Did not remove the last character\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_jshi_pop_back_remove_last_character\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status;
}

Status test_jshi_pop_back_empty_string_returns_FAILURE(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_default();

   if(my_string_pop_back(hString))
     {
       status = FAILURE;
       printf("Expected the character to be at the end but have %s\n", my_string_at(hString, my_string_get_size(hString)-1));
       strncpy(buffer, "test_jshi_push_back_place_character_at_end\n"
	       "Did not place the character at the end of the string\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_jshi_push_back_place_character_at_end\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status;
}

Status test_jshi_at_out_of_bounds_returns_NULL(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_default();

   if(my_string_at(hString, 1) != NULL)
     {
       status = FAILURE;
       printf("Expected NULL\n");
       strncpy(buffer, "test_jshi_at_out_of_bounds_returns_NULL\n"
	       "Did not return NULL to out of bounds index\n",length);
     }
   else
     {
       status = SUCCESS;
       strncpy(buffer, "test_jshi_at_out_of_bounds_returns_NULL\n"
	       , length);
     }

   my_string_destroy(&hString);
   return status;
}

Status test_jshi_c_str_NULL_terminate(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  char* test;

  hString = my_string_init_c_string("hi");
  test = my_string_c_string(hString);

  test += my_string_get_size(hString);

  if(*test != '\0')
    {
      status = FAILURE;
      printf("Expected to NULL terminate the string\n");
      strncpy(buffer, "test_jshi_c_str_NULL_terminate\n"
	       "Did not NULL termiate the string\n",length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_jshi_c_str_NULL_terminate\n"
	       , length);
    }
  
  my_string_destroy(&hString);
  return status;  
}

Status test_jshi_c_str_returns_address_of_first_element(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_c_string("hi");

  if(my_string_c_string(hString) != my_string_at(hString, 0))
    {
      status = FAILURE;
      printf("Expected the address of the first element\n");
      strncpy(buffer, "test_jshi_c_str_returns_address_of_first_element\n"
	       "Did not return address of the first element\n",length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_jshi_c_str_returns_address_of_first_element\n"
	       , length);
    }
  
  my_string_destroy(&hString);
  return status;  
}

Status test_jshi_concat_no_change_to_hAppend_object(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hAppend = NULL;
  MY_STRING hTemp = NULL;
  Status status;

  hString = my_string_init_c_string("hello");
  hAppend = my_string_init_c_string("world");
  hTemp = hAppend;

  my_string_concat(hString, hAppend);

  if(my_string_compare(hAppend, hTemp) != 0)
    {
      status = FAILURE;
      printf("Expected no change to hAppend object\n");
      strncpy(buffer, "test_jshi_concat_no_change_to_hAppend_object\n"
	       "Changed hAppend object\n",length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_jshi_concat_no_change_to_hAppend_object\n"
	       , length);
    }
  
  my_string_destroy(&hString);
  my_string_destroy(&hAppend);
  return status;
}


Status test_jshi_concat_resize_operation(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hAppend = NULL;
  Status status;

  hString = my_string_init_c_string("hello");
  hAppend = my_string_init_c_string("world");

  if(my_string_concat(hString, hAppend) == FAILURE)
    {
      status = FAILURE;
      printf("Expected resize operation\n");
      strncpy(buffer, "test_jshi_concat_resize_operation\n"
	       "Failed to resize\n",length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_jshi_concat_resize_operation\n"
	       , length);
    }
  
  my_string_destroy(&hString);
  my_string_destroy(&hAppend);
  return status;
}

Status test_jshi_empty_returns_TRUE_for_empty_string(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_c_string("hi");

  if(my_string_empty(hString))
    {
      status = FAILURE;
      printf("Expected to return FALSE for nonempty string\n");
      strncpy(buffer, "test_jshi_empty_returns_TRUE_for_empty_string\n"
	       "Did not return FALSE for non-empty string\n",length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_jshi_empty_returns_TRUE_for_empty_string\n"
	       , length);
    }
  
  my_string_destroy(&hString);
  return status; 
}
