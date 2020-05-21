#include <criterion/criterion.h>

#include <array.h>

Test(array, new_empty_array) {
    array_t empty = array_new(0);
    array_print_debug("empty", empty);
    cr_expect(array_is_empty(empty), "is empty");
}

Test(array, adding_one_element) {
    array_t adding_one_element = array_new(0);
    array_add(adding_one_element, "One");
    array_print_debug("adding_one_element", adding_one_element);
    cr_expect_eq(array_count(adding_one_element), 1);
    cr_expect_not(array_is_empty(adding_one_element));
}

Test(array, copy_of_one_element) {
    array_t adding_one_element = array_new(0);
    array_add(adding_one_element, "One");
    array_t copy_of_one_element = array_copy(adding_one_element);
    array_print_debug("copy_of_one_element", copy_of_one_element);
    cr_assert_neq(adding_one_element, copy_of_one_element);
    cr_assert_eq(array_count(copy_of_one_element), 1);
}
/*
void test_array() {
    array_t empty = array_new(8);

    printf("array_is_empty(empty) = %s\n", array_is_empty(empty) ? "true" : "false");
    array_t adding_one_element = array_new(0);
    array_add(adding_one_element, "One");
    array_print_debug("adding_one_element", adding_one_element);
    printf("array_is_empty(adding_one_element) = %s\n", array_is_empty(adding_one_element) ? "true" : "false");
    printf("array_is_full(adding_one_element) = %s\n", array_is_full(adding_one_element) ? "true" : "false");
    array_t copy_of_one_element = array_copy(adding_one_element);
    array_print_debug("copy_of_one_element", copy_of_one_element);
    array_add(copy_of_one_element, "Two");
    array_print_debug("copy_of_one_element (after adding world)", copy_of_one_element);
    array_t from_string = array_from_split_string("Hello,World", ",");
    array_print_debug("from_string", from_string);
    printf("array_is_empty(from_string) = %s\n", array_is_empty(from_string) ? "true" : "false");
    printf("array_is_full(from_string) = %s\n", array_is_full(from_string) ? "true" : "false");
    array_t joined_array = array_join(copy_of_one_element, from_string);
    array_print_debug("joined_array", joined_array);
    printf("joined_array contain string \"One\" = %s\n", array_contains_string(joined_array, "One") ? "true" : "false");
    printf("joined_array contain element \"One\" = %s\n", array_contains_element(joined_array, array_element(joined_array, 0)) ? "true" : "false");
    printf("joined_array contain element copy_of_one_element = %s\n", array_contains_element(joined_array, copy_of_one_element) ? "true" : "false");
    printf("String \"One of these will match\" contains from joined_array = %s\n", array_string_contains_any(joined_array, "One of these will match") ? "true" : "false");
    printf("String \"None of these will match\" contains from joined_array = %s\n", array_string_contains_any(joined_array, "None of these will match") ? "true" : "false");
    array_t second_split = array_from_split_string("Five,Six,Seven,Eight", ",");
    array_print_debug("second_split", second_split);
    array_t match_one = array_from_split_string("One", ",");
    array_t match_none = array_from_split_string("None", ",");
    array_print_debug("match_one", match_one);
    array_print_debug("match_none", match_none);
    printf("joined_array contains_any_string(match_one) = %s\n", array_contains_any_string(joined_array, match_one) ? "true" : "false" );
    printf("joined_array contains_any_string(match_none) = %s\n", array_contains_any_string(joined_array, match_none) ? "true" : "false" );
    array_t match_element = array_new(8);
    array_add(match_element, array_element(joined_array, 0));
    array_t non_match_element = array_new(8);
    array_add(non_match_element, "This will not match");
    printf("joined_array contains_any_element(match_element) = %s\n", array_contains_any_element(joined_array, match_element) ? "true" : "false" );
    printf("joined_array contains_any_element(non_match_element) = %s\n", array_contains_any_element(joined_array, non_match_element) ? "true" : "false" );
    array_append_elements(joined_array, second_split);
    array_print_debug("joined_array", joined_array);
    array_t new_elements = array_from_split_string("Buckle,Shoe", ",");
    array_append_duplicating_strings(joined_array, new_elements);
    array_print_debug("joined_array", joined_array);
    array_t dyanmic_strings = array_from_split_string("One,Two,Three,Four", ",");
    array_free_all(dyanmic_strings);
    return;
}
 */