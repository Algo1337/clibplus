#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Libraries/global.h"
#include "Libraries/String/str.h"

int main() {
    str *s = string("d   test   ");
    long chk = (long) s->Utils(s, _STRIP);
    printf("_STRIP: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->Utils(s, _TRIM, ' ');
    printf("_TRIM: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->Utils(s, _COUNTCHAR, 't');
    printf("_COUNTCHAR: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->Utils(s, _COUNTSTR, "test");
    printf("_COUNTSTR: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->Utils(s, _STARTSWITH, "dt");
    printf("_STARTSWITH: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->Utils(s, _ENDSWITH, "est");
    printf("_ENDSWITH: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->Utils(s, _ISUPPERCASE);
    printf("_ISUPPERCASE: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->Utils(s, _ISLOWERCASE);
    printf("_ISLOWERCASE: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->Utils(s, _TOUPPERCASE);
    printf("_TOUPPERCASE: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->Utils(s, _TOLOWERCASE);
    printf("_TOLOWERCASE: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->Utils(s, _REPLACE, "test", "GAY");
    printf("__REPLACE: %ld | Data: %s\n", chk, s->data);

    char **test = (char **)s->Utils(s, _SPLITCHAR, 'G');
    strcat(s->data, " [ ");
    s->Utils(s, _JOIN, test, ' ');
    strcat(s->data, " ]");
    printf("_SPLITCHAR && _JOIN: %s\n", s->data);

    // Free array
    int i = 0;
    while(test[i] != NULL)
        free(test[i++]);
    
    free(test);
    free(s->data);
    free(s);
    return 0;
}