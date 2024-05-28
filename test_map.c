#include "cstdbp_map.h"
#include <string.h>

typedef struct {
    bool occupied;
    char *key;
    int *val;
} kv;

typedef struct {
    uint32_t (*hash)(char *);
    uint32_t (*compare)(char *, char *);
    size_t cap;
    kv *items;
} ht;

uint32_t shash(char *str) {
    uint32_t res = 0;
    for (int i = 0; i < strlen(str); i++) {
        res = res * 33 + str[i];
    }
    return res;
}

uint32_t scompare(char *a, char *b) {
    uint32_t res = strcmp(a, b);
    return res;
}

void dumpht(ht *tbl) {
    printf("[\n");
    for (int i = 0; i < tbl->cap; i++) {
        printf("\t%s : %d\n", tbl->items[i].key ? tbl->items[i].key : "-",
               (tbl->items[i].val) ? *(tbl->items[i].val) : -1);
    }
    printf("]\n");
}

static char *strs[] = {"Monday", "tuesday",  "Wednesday", "thursday",
                       "Friday", "Saturday", "Sunday"};
static int data[] = {10, 20, 30, 40, 50, 60, 70};

int main(void) {
    ht tbl = {0};
    std_map_init(&tbl, 16, shash, scompare);
    dumpht(&tbl);
    for (int i = 0; i < 7; i++) {
        std_map_put(&tbl, strs[i], &(data[i]));
    }
    dumpht(&tbl);
    int *myval = NULL;
    std_map_get(&tbl, "Wednesday", &myval);
    printf("Found %s : %d", "Wednesday", *myval);
    return 0;
}
