/*
 * array.h - Simple C arrays
 *
 * Written in 2020 by Rick Mark <rickmark@outlook.com>
 *
 * To the extent possible under law, the author(s) have dedicated all
 * copyright and related and neighboring rights to this software to
 * the public domain worldwide. This software is distributed without
 * any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication
 * along with this software. If not, see
 * <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef IDEVICECOMMON_ARRAY_H
#define IDEVICECOMMON_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    size_t capacity;
    size_t count;
    void** data;
} array_header_t;

typedef array_header_t* array_t;

/**
 * Creates a new array_t with an initial capacity.
 *
 * @param capacity The initial capacity of the Array.
 *
 * @return a new array.
 */
array_t array_new(size_t capacity);


/**
 * Creates a new array_t by copying an array, without copying elements.
 *
 * @param source The array to copy.
 *
 * @return a new array, which is a copy of the other pointing at the same elements.
 */
array_t array_copy(array_t source);


/**
 * Creates a new array_t with elements which are the strings split by a token.
 *
 * @param string The string to split.
 * @param split_on the delineator between strings.
 *
 * @return a new array_t with elements which are split from the string.
 */
array_t array_from_split_string(char* string, const char* split_on);


/**
 * Creates a new array_t by joining the elements of two array_ts without copying the elements.
 *
 * @param first The first array to join.
 * @param second The second array to join.
 *
 * @return a new array_t with the elements of both arrays.
 */
array_t array_join(array_t first, array_t second);


/**
 * Frees an array_t without freeing the elements in the array.
 *
 * @param array The array to free.
 */
void array_free(array_t array);


/**
 * Frees an array_t without freeing the elements in the array.
 *
 * @param array The array to free, after freeing all of it's elements.
 */
void array_free_all(array_t array);


/**
 * Get's the count of the elements of the array.
 *
 * @param array The array to get the count from.
 *
 * @return The count of elements in the array.
 */
size_t array_count(array_t array);


/**
 * Appends an element to the end of the array.  Will automatically grow the
 * array's capacity if it is needed.
 *
 * @param array The array to be added too.
 * @param element The element to add to the array.
 */
void array_add(array_t array, void* element);


/**
 * Appends elements from one array to the other, without copying or taking
 * ownership of the elements of the source array.
 *
 * @param array The array to append the elements too.
 * @param to_add The array of elements to append.
 */
void array_append_elements(array_t array, array_t to_add);


/**
 * Appends an array to an array by duplicating the elements as strings.
 *
 * @param array The array to copy into.
 * @param to_add An array of strings to append.
 */
void array_append_duplicating_strings(array_t array, array_t to_add);


/**
 * Gets an element of the array by index.
 *
 * @param array The array to index into.
 * @param index The index into the array.
 *
 * @return The element at the index in the array.
 */
void* array_element(array_t array, size_t index);


/**
 * A boolean representing if the array has no elements.
 *
 * @param array The array.
 *
 * @return True if the array has no elements, otherwise false.
 */
bool array_is_empty(array_t array);


/**
 * A boolean representing if the array_t is full, and appending would
 * cause a reallocation of the backing data.
 *
 * @param array The array to check.
 *
 * @return True if the array size is at capacity, otherwise false.
 */
bool array_is_full(array_t array);


/**
 * A boolean representing if the pointer element is contained in the
 * array.
 *
 * @param array The array to search.
 * @param element The element to search for.
 *
 * @return True if the element is contained in the array.
 */
bool array_contains_element(array_t array, void* element);


/**
 * A boolean representing if the string is any of the elements in the
 * array.
 *
 * @param array The array to search.
 * @param string The string to search for in the array.
 *
 * @return True if the string is contained in the array, false if the
 *         string is not in the array.
 */
bool array_contains_string(array_t array, char* string);


/**
 * Searches one array if it contains any of the elements of the second.
 *
 * @param array The array to search.
 * @param elements The elements to search for.
 *
 * @return True if array contains an element that is in the array elements.
 */
bool array_contains_any_element(array_t array, array_t elements);


/**
 * Search an array elements for any string in array of strings.
 *
 * @param array The array to search.
 * @param strings The strings to search for.
 *
 * @return True if the array contains any of the strings in the array strings.
 */
bool array_contains_any_string(array_t array, array_t strings);


/**
 * Checks to see if a string contains any of the strings in an array of strings.
 *
 * @param array The array of elements to search for.
 * @param string The string to be searched.
 */
bool array_string_contains_any(array_t array, char* string);

#ifdef DEBUG
void array_print_debug(char* name, array_t array);
#else
void array_print_debug(char* name, array_t array);
#endif

#endif //IDEVICECOMMON_ARRAY_H
