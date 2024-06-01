#ifndef CSTDBP_STRING_H
#define CSTDBP_STRING_H

/**
 * This library contains better string function and structures
 * StringBuilder inspired from JAVA which is a mutable string buffer
 * StringView - This is basically like a view in tables in DBs. Its a window of
 * string it doesn't owns the memory
 *
 */

#ifdef CSTDBP_LIBMODE
#define CSTDBP_API static
#else
#define CSTDBP_API
#endif

#include "cstdbp_list.h"
#include <stdbool.h>
typedef struct {
    size_t len;
    size_t cap;
    char *items;
} StringBuilder;

#define std_sb_init() std_sb_initex(8)

#define std_string_toCStr(str, out) strncpy((out), (str)->items, (str)->len)

CSTDBP_API StringBuilder std_sb_initex(size_t cap);
CSTDBP_API StringBuilder std_sb_fromString(const char *str);
CSTDBP_API char std_sb_CharAt(StringBuilder *sb, int idx);
CSTDBP_API bool std_sb_insertAt(StringBuilder *sb, int idx, char c);
CSTDBP_API char std_sb_deleteCharAt(StringBuilder *sb, int idx);
CSTDBP_API bool std_sb_append(StringBuilder *sb, char *str);

typedef struct {
    size_t len;
    char *items;
} StringView;

CSTDBP_API StringView std_sv_fromString(char *str, int size);
CSTDBP_API StringView std_sv_formStringBuffer(StringBuilder sb);
CSTDBP_API StringView std_sv_splitBy(StringView *sv, char *c);
CSTDBP_API StringView std_sv_splitByPredicate(StringView *sv,
                                              int (*predicate)(int));
CSTDBP_API StringView std_sv_splitByString(StringView *sv, char *str);
CSTDBP_API bool std_sv_eq(StringView v1, StringView v2);

#endif // CSTDBP_STRING_H
