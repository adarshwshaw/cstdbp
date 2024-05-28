#include "list.h"

typedef struct {
    size_t len;
    size_t cap;
    char **items;
} Strings;

int main(void) {
    Strings strs = {0};
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    std_list_append(&strs, "hello");
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    std_list_append(&strs, "how");
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    std_list_append(&strs, "are");
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    std_list_insert(&strs, 1, "adarsh");
    std_list_append(&strs, "you");
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    std_list_append(&strs, "doing");
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    std_list_append(&strs, "today");
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    std_list_append(&strs, "?");
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    std_list_append(&strs, "?");
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    char *c;
    std_list_pop(&strs, &c);
    printf("poped : %s\n", c);
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    std_list_pop(&strs, &c);
    printf("poped : %s\n", c);
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    std_list_pop_at(&strs, 2, &c);
    printf("poped : %s\n", c);
    std_list_debugPrint(&strs, "%s", (&strs)->items[i]);
    std_list_destroy(&strs);
    printf("done\n");
    return 0;
}
