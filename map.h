#ifndef CSTDBP_MAP_H
#define CSTDBP_MAP_H

/**
 * struct type {
 *   bool occupied;
 *   key_type <any_name>;
 *   val_type <any_name>;
 * }
 * struct {
 *   uint32_t (*hash)(key_type);
 *   uint_8_t (*compare)(key_type, key_type);
 *   size_t cap;
 *   type *items;
 * }
 *
 * both struct need to be defined by the user in order to use the library
 */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define std_map_init(map, icap, ihash, icompare)                               \
    do {                                                                       \
        (map)->cap = (icap);                                                   \
        (map)->hash = (ihash);                                                 \
        (map)->compare = (icompare);                                           \
        (map)->items = calloc((icap), sizeof(*((map)->items)));                \
        assert((map)->items != NULL && "ERROR(MAP): OUT OF MEMORY");           \
    } while (0)

#define std_map_get(map, ikey, out)                                            \
    do {                                                                       \
        uint32_t h = (map)->hash((ikey));                                      \
        h = h % (map)->cap;                                                    \
        for (int i = 0; i < (map)->cap && (map)->items[h].occupied &&          \
                        (map)->compare((map)->items[h].key, (ikey));           \
             i++) {                                                            \
            h = (h + 1) % (map)->cap;                                          \
        }                                                                      \
        if (!((map)->compare((map)->items[h].key, (ikey)))) {                  \
            *out = ((map)->items[h].val);                                      \
        }                                                                      \
    } while (0)

#define std_map_put(map, ikey, ival)                                           \
    do {                                                                       \
        uint32_t h = (map)->hash((ikey));                                      \
        h = h % (map)->cap;                                                    \
        for (int i = 0; i < (map)->cap && (map)->items[h].occupied &&          \
                        (map)->compare((map)->items[h].key, (ikey));           \
             i++) {                                                            \
            h = (h + 1) % (map)->cap;                                          \
        }                                                                      \
        if ((map)->items[h].occupied) {                                        \
            if ((map)->compare((map)->items[h].key, (ikey)) == 0) {            \
                (map)->items[h].key = (ikey);                                  \
                (map)->items[h].val = (ival);                                  \
            } else {                                                           \
                assert(false && "No more space to insert in table");           \
            }                                                                  \
        } else {                                                               \
            (map)->items[h].key = (ikey);                                      \
            (map)->items[h].val = (ival);                                      \
            (map)->items[h].occupied = true;                                   \
        }                                                                      \
    } while (0)

#define std_map_destroy(map)                                                   \
    do {                                                                       \
        assert((map) != NULL && "ERROR(MAP): Cannot free a null pointer");     \
        free((map)->items);                                                    \
        (map).cap = 0;                                                         \
        (map).items = NULL;                                                    \
    } while (0)

#endif // CSTDBP_MAP_H
