/*
 * array.c - Simple C arrays
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array.h"

size_t memory_align_ceiling(size_t size) {
    size_t aligned = 2;
    if (size <= 1) return 1;
    size--;
    while (size >>= 1 != 0) aligned <<= 1;
    return aligned;
}

array_t array_new(size_t elements) {
    array_t result = calloc(1, sizeof(array_header_t));
    result->capacity = memory_align_ceiling(elements);
    result->count = 0;
    result->data = calloc(result->capacity, sizeof(void*));

    return result;
}

array_t array_copy(array_t source) {
    array_t result = malloc(sizeof(array_header_t));
    memcpy(result, source, sizeof(array_header_t));

    result->data = calloc(source->capacity, sizeof(void*));
    memcpy(result->data, source->data, source->capacity * sizeof(void*));

    return result;
}

array_t array_from_split_string(char* string, const char* split_on)
{
    array_t items = array_new(8);
    if (string == NULL) { return items; }

    char* state = NULL;
    char* local_string = strdup(string);
    char* token = strtok_r(local_string, split_on, &state);

    while (token != NULL) {
        array_add(items, strdup(token));
        token = strtok_r(NULL, split_on, &state);
    }
    free(local_string);

    return items;
}

array_t array_join(array_t first, array_t second) {
    array_t items = array_new(first->count + second->count);

    void* data_region = (void*)items->data;
    memcpy(data_region, first->data, first->count * sizeof(void*));

    void* second_region = data_region + (sizeof(void*) * first->count);
    memcpy(second_region, second->data, second->count * sizeof(void*));

    items->count = first->count + second->count;

    return items;
}

void array_append_elements(array_t array, array_t to_add) {
    size_t new_count = array->count + to_add->count;
    size_t new_capacity = memory_align_ceiling(new_count);

    array->data = realloc(array->data, new_capacity * sizeof(void*));
    array->capacity = new_capacity;

    void* data_region = (void*)array->data;
    void* second_region = data_region + (sizeof(void*) * array->count);
    memcpy(second_region, to_add->data, to_add->count * sizeof(void*));

    array->count = new_count;
}

void array_append_duplicating_strings(array_t array, array_t to_add) {
    for (size_t index = 0; index < to_add->count; index++) {
        array_add(array, strdup(array_element(to_add, index)));
    }
}

void array_free(array_t array) {
    if (array) {
        if (array->data) {
            free(array->data);
        }
        free(array);
    }
}

void array_free_all(array_t array) {
    for (size_t index = 0; index < array->count; index++) {
        void* element = array_element(array, index);
        if (element) { free(element); }
    }

    array_free(array);
}

size_t array_count(array_t array) {
    return array->count;
}

void array_add(array_t array, void* element) {
    if (array_is_full(array)) {
        size_t new_capacity = array->capacity * 2;
        array->data = realloc(array->data, new_capacity * sizeof(void*));
        array->capacity = new_capacity;
    }

    array->data[array->count++] = element;
}

bool array_is_full(array_t array) {
    return array->capacity == array->count;
}

bool array_is_empty(array_t array) {
    return array->count == 0;
}

void* array_element(array_t array, size_t index) {
    if (index > array->count) {
        return NULL;
    }

    return array->data[index];
}

bool array_contains_element(array_t array, void* element) {
    for (size_t index = 0; index < array->count; index++) {
        if (array->data[index] == element) {
            return true;
        }
    }

    return false;
}

bool array_contains_string(array_t array, char* string) {
    size_t outer_length = strlen(string);
    for (size_t index = 0; index < array->count; index++) {
        size_t inner_length = strlen(array->data[index]);
        if (outer_length != inner_length) {
            continue;
        }

        if (memcmp(array->data[index], (void*)string, outer_length)) {
            return true;
        }
    }

    return false;
}

bool array_contains_any_element(array_t array, array_t elements) {
    for (size_t index = 0; index < array->count; index++) {
        for (size_t element = 0; element < elements->count; element++) {
            if (array->data[index] == elements->data[element]) {
                return true;
            }
        }
    }

    return false;
}

bool array_contains_any_string(array_t array, array_t strings) {
    for (size_t index = 0; index < strings->count; index++) {
        if (array_contains_string(array, strings->data[index])) {
            return true;
        }
    }

    return false;
}

bool array_string_contains_any(array_t array, char* string) {
    for (size_t index = 0; index < array->count; index++) {
        if (strstr(string, array->data[index])) {
            return true;
        }
    }

    return false;
}

#ifdef DEBUG
void array_print_debug(char* name, array_t array) {
    if (array == NULL) {
        printf("%s = NULL\n", name);
        return;
    }

    if (array_is_empty(array)) {
        printf("%s = empty\n", name);
        return;
    }

    printf("%s = (count = %zu, capacity = %zu) [ ", name, array_count(array), array->capacity);
    for (size_t index = 0; index < array->count; index++) {
        printf("\"%s\"", array_element(array, index));
        if (index + 1 != array->count) {
            printf(", ");
        }
    }
    printf(" ] \n");
}
#else
void array_print_debug(char* name, array_t array) {}
#endif