#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHECK_CONDITION(typ, name, x) if ((x) > 0) { \
    typedef const typ *name; \
} else { \
    typedef const typ name; \
}

// #define DeclareVariable(n, name) \
//     typedef const n name;

DeclareVariable(char, String, 1);
DeclareVariable(char, Char, NULL);
// DeclareVariable(char, Char);

void print_shit(String s, Char c) {
    printf("%s: %c\n", (char *)s, (char)c);
}

int main() {
    Char n = 'c';
    char buff[1024] = {0};
    strcpy(buff, "GAY");

    String t = (const char *)&buff;
    print_shit(t, n);
    return 0;
}