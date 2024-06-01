#include "cstdbp_list.h"
#include "cstdbp_string.h"
#include <stdio.h>
#define SVFMT "%.*s"
#define SVARG(sv) (int)((sv)->len), (sv)->items
#define print(str)                                                             \
    printf(#str "(len:%zu) : " SVFMT "\n", (str)->len, SVARG(str))

int main(void) {
    StringBuilder sb1 = {0};
    print(&sb1);
    char *data1 = "olleh";
    for (int i = 0; i < strlen(data1); i++) {
        std_sb_insertAt(&sb1, 0, data1[i]);
        print(&sb1);
    }
    std_sb_append(&sb1, " ");
    StringBuilder sb2 = std_sb_fromString("world");
    print(&sb2);
    char ar[6] = {0};
    char *ar1;
    ar1 = std_string_toCStr(&sb2, ar);
    printf("ar: %s\n", ar);
    std_sb_append(&sb1, ar);
    print(&sb1);
    printf("char at 6: %c\n", std_sb_CharAt(&sb1, 6));
    char c = std_sb_deleteCharAt(&sb1, 7);
    printf("char at 6: %c\n", c);
    print(&sb1);
    (void)ar1;

    StringView sv = std_sv_formStringBuffer(sb1);
    print(&sv);
    StringView sv1 = std_sv_splitBy(&sv, " ");
    print(&sv1);
    print(&sv);
    printf("cmp: %d\n", std_sv_eq(sv1, sv));

    sv = std_sv_fromString(data1, 6);
    print(&sv);
    sv1 = std_sv_splitByString(&sv, "ll");
    print(&sv1);
    print(&sv);
    return 0;
}
