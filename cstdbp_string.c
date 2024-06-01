#include "cstdbp_string.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

CSTDBP_API StringBuilder std_sb_initex(size_t cap) {
    StringBuilder sb = {0};
    assert(cap > 0 &&
           "Error(StringBuilder): Error capacity cannot be less than 0");
    sb.items = calloc(cap, sizeof(*(sb.items)));
    sb.cap = cap;
    return sb;
}
CSTDBP_API StringBuilder std_sb_fromString(const char *str) {
    size_t len = strlen(str);
    StringBuilder sb = {0};
    for (size_t i = 0; i < len; i++) {
        std_list_append(&sb, str[i]);
    }
    return sb;
}
CSTDBP_API char std_sb_CharAt(StringBuilder *sb, int idx) {
    idx = (idx < 0) ? sb->len - idx : idx;
    return sb->items[idx];
}
CSTDBP_API bool std_sb_insertAt(StringBuilder *sb, int idx, char c) {

    idx = (idx < 0) ? sb->len - idx : idx;
    std_list_insert(sb, idx, c);
    return true;
}
CSTDBP_API char std_sb_deleteCharAt(StringBuilder *sb, int idx) {
    idx = (idx < 0) ? sb->len - idx : idx;
    char c = 0;
    std_list_pop_at(sb, idx, &c);
    return c;
}
CSTDBP_API bool std_sb_append(StringBuilder *sb, char *str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        std_list_append(sb, str[i]);
    }
    return true;
}
CSTDBP_API char *std_sb_toCStr(StringBuilder *sb, char *out) {
    strncpy(out, sb->items, sb->len);
    return out;
}

CSTDBP_API StringView std_sv_fromString(char *str, int size) {
    StringView sv = {.len = size, .items = str};
    return sv;
}

CSTDBP_API StringView std_sv_formStringBuffer(StringBuilder sb) {
    StringView sv = {.len = sb.len, .items = sb.items};
    return sv;
}

CSTDBP_API StringView std_sv_splitBy(StringView *sv, char *c) {
    StringView rsv = {.len = 0, .items = sv->items};
    int dlen = strlen(c);
    while (rsv.len < sv->len) {
        for (int i = 0; i < dlen; i++) {
            if (rsv.items[rsv.len] == c[i]) {
                sv->len--;
                sv->items++;
                break;
            } else {
                rsv.len++;
                sv->items++;
                sv->len--;
            }
        }
    }
    return rsv;
}
CSTDBP_API StringView std_sv_splitByPredicate(StringView *sv,
                                              int (*predicate)(int)) {
    StringView rsv = {.len = 0, .items = sv->items};
    while (rsv.len < sv->len) {
        if (predicate(rsv.items[rsv.len])) {
            sv->items++;
            sv->len--;
            break;
        } else {
            rsv.len++;
            sv->items++;
            sv->len--;
        }
    }
    return rsv;
}
CSTDBP_API StringView std_sv_splitByString(StringView *sv, char *str) {
    StringView rsv = {0, sv->items};
    int dlen = strlen(str);
    while (rsv.len < sv->len) {
        if (!strncmp(&(rsv.items[rsv.len]), str, dlen)) {
            sv->items += dlen;
            sv->len -= dlen;
            break;
        } else {
            rsv.len++;
            sv->items++;
            sv->len--;
        }
    }
    return rsv;
}
CSTDBP_API bool std_sv_eq(StringView v1, StringView v2) {
    if (v1.len != v2.len)
        return false;
    if (v1.items[0] != v2.items[0])
        return false;
    return (strncmp(v1.items, v2.items, v1.len) == 0) ? true : false;
}
