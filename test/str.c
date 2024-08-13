#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/String/str.h>

int main() {
    str *s = string("d   test   ");
    long chk = (long)s->Strip(s);
    printf("_STRIP: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->Trim(s, ' ');
    printf("_TRIM: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->CountChar(s, 't');
    printf("_COUNTCHAR: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->CountSubstr(s, "test");
    printf("_COUNTSTR: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->StartsWith(s, "dt");
    printf("_STARTSWITH: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->EndsWith(s, "est");
    printf("_ENDSWITH: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->IsUppercase(s);
    printf("_ISUPPERCASE: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->IsLowercase(s);
    printf("_ISLOWERCASE: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->ToUppercase(s);
    printf("_TOUPPERCASE: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->ToLowercase(s);
    printf("_TOLOWERCASE: %ld | Data: %s\n", chk, s->data);

    chk = (long)s->ReplaceString(s, "test", "GAY");
    printf("__REPLACE: %ld | Data: %s\n", chk, s->data);

    char **test = (char **)s->Split(s, "G");

    str *new = string("[");

    int i = 0;
    while(test[i] != NULL) {
        new->AppendString(new, test[i]);
        new->AppendString(new, " ");
        i++;
    }
    new->AppendString(new, "]");
    printf("_SPLITCHAR && _JOIN: %s\n", new->data);

    // Free array
    i = 0;
    while(test[i] != NULL)
        free(test[i++]);
    
    free(test);
    free(s->data);
    free(s);
    return 0;
}