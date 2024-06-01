#ifndef CSTDBP_LIST_H
#define CSTDBP_LIST_H

/*
 * Array Structure
 * struct {
 *   size_t len;
 *   size_t cap;
 *   type *items;
 * }
 *
 * User will define the struct replace the type with their desired type and use
 * the function provided by the library to operate on it.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * accept the pointer to the struct and just initialize is allocating space for list
*/
#define std_list_init(list,capacity) \
    do { \
        assert((capacity) < 1 && "ERROR(List): cannot initialize an list with 0 capacity!");\
        (list)->items = calloc(cap, sizeof (*((list)->items))); \
            assert((list)->items != NULL && "ERROR(List): Out of Memory");     \
        (list)->len=0;\
        (list)->cap=capacity;\
    }while(0)


/**
 * Macro accept list, index and item and insert the item in the list at
 * specified index if its < length list is accpted as a pointer
 */
#define std_list_insert(list, idx, item)                                       \
    do {                                                                       \
        assert((idx) <= (list)->len &&                                         \
               "ERROR(List): Overflow - index cannot be larger than the "      \
               "length of the array");                                         \
        if ((list)->len == (list)->cap) {                                      \
            size_t len = (list)->cap ? (list)->cap * 2 : 8;                    \
            (list)->items =                                                    \
                realloc((list)->items, sizeof(*((list)->items)) * len);        \
            assert((list)->items != NULL && "ERROR(List): Out of Memory");     \
            (list)->cap = len;                                                 \
        }                                                                      \
        if ((idx) == (list)->len) {                                            \
            (list)->items[(list)->len] = (item);                               \
        } else {                                                               \
            memmove(&((list)->items[idx + 1]), &((list)->items[idx]),          \
                    ((list)->len - idx) * (sizeof(*((list)->items))));         \
            (list)->items[idx] = item;                                         \
        }                                                                      \
        (list)->len++;                                                         \
    } while (0)

#define std_list_append(list, item) std_list_insert(list, (list)->len, item)

/**
 * Macro deletes the element at index and loads it to out variable
 * List is a pointer
 * out is a pointer
 */
#define std_list_pop_at(list, idx, out)                                        \
    do {                                                                       \
        assert(idx > 0 && idx < (list)->len &&                                 \
               "Error(List): index out of bounds");                            \
        if ((idx) == (list)->len - 1) {                                        \
            *out = (list)->items[(idx)];                                       \
        } else {                                                               \
            *out = (list)->items[(idx)];                                       \
            memmove(&((list)->items[idx]), &((list)->items[idx + 1]),          \
                    ((list)->len - idx - 1) * (sizeof(*((list)->items))));     \
        }                                                                      \
        (list)->len--;                                                         \
    } while (0)

#define std_list_pop(list, out) std_list_pop_at(list, (list)->len - 1, out)

#define std_list_destroy(list) free((list)->items)

#define std_list_debugPrint(list, item_fmt, ...)                               \
    do {                                                                       \
        printf("(len: %zu, cap %zu)[", (list)->len, (list)->cap);              \
        for (int i = 0; i < (list)->len; i++) {                                \
            printf((item_fmt), __VA_ARGS__);                                   \
            if (i < (list)->len - 1)                                           \
                printf(", ");                                                  \
        }                                                                      \
        printf("]\n");                                                         \
    } while (0)

#endif // CSTDBP_LIST_H
