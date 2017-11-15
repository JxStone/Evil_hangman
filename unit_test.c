#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
  Status (*tests[])(char*, int) =
    {
      test_init_default_returns_nonNULL,
      test_get_size_on_init_default_returns_0,
      test_init_default_get_capacity_returns_7,
      test_jshi_destroy_set_to_NULL,
      test_jshi_init_c_string_returns_nonNULL,
      test_jshi_init_c_string_capacity_one_greater_than_size,
      test_jshi_get_capacity_returns_integer,
      test_jshi_get_size_returns_integer,
      test_jshi_compare_returns_size_difference,
      test_jshi_extraction_ignores_leading_space,
      test_jshi_extraction_read_non_empty_string,
      test_jshi_extraction_empty_file_returns_FAILURE,
      test_jshi_insertion_empty_string_returns_FAILURE,
      test_jshi_insertion_successfully_write_string,
      test_jshi_push_back_resize,
      test_jshi_push_back_double_capacity,
      test_jshi_push_back_place_item_at_end,
      test_jshi_pop_back_remove_last_character,
      test_jshi_pop_back_empty_string_returns_FAILURE,
      test_jshi_at_out_of_bounds_returns_NULL,
      test_jshi_c_str_NULL_terminate,
      test_jshi_c_str_returns_address_of_first_element,
      test_jshi_concat_no_change_to_hAppend_object,
      test_jshi_concat_resize_operation,
      test_jshi_empty_returns_TRUE_for_empty_string
    };

  int number_of_functions = sizeof(tests)/sizeof(tests[0]);
  int i;
  char buffer[500];
  int success_count = 0;
  int failure_count = 0;

  for(i = 0; i < number_of_functions; i++)
    {
      if(tests[i](buffer,500) == FAILURE)
	{
	  printf("FAILED: TEST %d failed miserably\n", i);
	  printf("\t%s\n", buffer);
	  failure_count++;
	}
      else
	{
	  printf("PASS: TEST %d passed\n", i);
	  printf("\t%s\n", buffer);
	  success_count++;
	}
    }
  printf("Total number of tests: %d\n", number_of_functions);
  printf("%d/%d Pass, %d/%d Failure\n", success_count, number_of_functions, failure_count, number_of_functions);
  return 0;
}
