#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length);

Status test_get_size_on_init_default_returns_0(char* buffer, int length);

Status test_init_default_get_capacity_returns_7(char* buffer, int length);

Status test_jshi_destroy_set_to_NULL(char* buffer,int length);

Status test_jshi_init_c_string_returns_nonNULL(char* buffer, int length);

Status test_jshi_init_c_string_capacity_one_greater_than_size(char* buffer, int length);

Status test_jshi_get_capacity_returns_integer(char* buffer, int length);

Status test_jshi_get_size_returns_integer(char* buffer, int length);

Status test_jshi_compare_returns_size_difference(char* buffer, int length);

Status test_jshi_extraction_ignores_leading_space(char* buffer, int length);

Status test_jshi_extraction_read_non_empty_string(char* buffer, int length);

Status test_jshi_extraction_empty_file_returns_FAILURE(char* buffer, int length);

Status test_jshi_insertion_empty_string_returns_FAILURE(char* buffer, int length);

Status test_jshi_insertion_successfully_write_string(char* buffer, int length);

Status test_jshi_push_back_resize(char* buffer, int length);

Status test_jshi_push_back_double_capacity(char* buffer, int length);

Status test_jshi_push_back_place_item_at_end(char* buffer, int length);

Status test_jshi_pop_back_remove_last_character(char* buffer, int length);

Status test_jshi_pop_back_empty_string_returns_FAILURE(char* buffer, int length);

Status test_jshi_at_out_of_bounds_returns_NULL(char* buffer, int length);

Status test_jshi_c_str_NULL_terminate(char* buffer, int length);

Status test_jshi_c_str_returns_address_of_first_element(char* buffer, int length);

Status test_jshi_concat_no_change_to_hAppend_object(char* buffer, int length);

Status test_jshi_concat_resize_operation(char* buffer, int length);

Status test_jshi_empty_returns_TRUE_for_empty_string(char* buffer, int length);
#endif
