#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/global_memory.h>

typedef struct String {
    char *data;
    long idx;
} String;

String *string(const char *data) {
    String *s = (String *)malloc(sizeof(String));

    if(data == NULL || strlen(data) == 0)
    {
        s->data = (char *)alloc(1);
        s->idx = 0;
        return s;
    }

    s->data = (char *)alloc(strlen(data) + 1);
    strcpy(s->data, data);
    s->idx = (long)strlen(data) + 1;

    return s;
}

String *new_string(String *s, const char *data) {
    s = string(data);
    return s;
}

String *append2str(String *s, const char *data) {
    if(data == NULL || strlen(data) == 0)
        return s;

    if(strlen(s->data) == 0) {
        s = string(data);
        return s;
    }

    char *new = (char *)alloc(strlen(s->data) + strlen(data));
    strcpy(new, s->data);
    strncat(new, data, strlen(data));

    free(s->data);
    s->data = new;
    s->idx += strlen(data);
    return s;
}

// If a char is found the number of count provided, it will return the position of the char in string
long findchar_at_count(String *s, const char ch, int count) {
    int c = 0;
    for(int i = 0; i < s->idx; i++) {
        if(s->data[i] == ch)
            c++;

        if(c == count || (s->data[i] == ch && count == 0))
            return i;
    }

    return 0;
}

// only find the first matched char and return position
long findchar(String *s, const char ch) {
    return findchar_at_count(s, ch, 1);
}

long findstr(String *s, const char *str) {
    for(int i = 0; i < s->idx; i++) {
        if(s->data[i] == str[0] && s->data[s->idx] == str[strlen(str)]) {
            return i;
        }
    }

    return 0;
}

long count_char(String *s, const char ch) {
    long count = 0;
    for(int i = 0; i < s->idx; i++) {
        if(s->data[i] == ch)
            count++;
    }

    return count;
}

char *get_substr(String *s, int start, int end) {
    char *new = (char *)alloc(1);
    int idx = 0;
    for(int i = 0; i < s->idx; i++) { 
        if(i >= start && i < end) {
            strncat(new, &s->data[i], sizeof(char));
            idx++;
            new = (char*)realloc(new, idx + 1);
        }
    }

    return new;
}

char **split_string_w_char(String *s, const char delim) {
    long count = count_char(s, delim) + 1;
    
    char **arr = (char **)alloc2(count);
    long idx = 0;

    int start = findchar_at_count(s, delim, 0), end = 0;
    for(int i = 1; i < count; i++)
    {
        end = findchar_at_count(s, delim, i);
        char *sub = get_substr(s, start, end);

        if(i > 1)
            sub = get_substr(s, start + 1, end);

        arr[idx] = strdup(sub);
        idx++;
        free(sub);
        start = end;
    }

    return arr;
}

char *replace_string(String *s, const char *find, const char *replace) {

    char *new = (char *)alloc(s->idx + strlen(replace) + 1);
    int string_at = findstr(s, find);
    int i = 0;
    while(i < s->idx) {
        if(i >= string_at && i < (string_at + strlen(find))) {
            printf("ADDED\n");
            strncat(new, replace, strlen(replace));
            i += strlen(find);
            continue;
        }

        strncat(new, &s->data[i], sizeof(char));
        i++;
    }

    return new;
}

int main() {
    String *n = string(NULL);
    n = append2str(n, "NEW\n");
    n = append2str(n, "BEEP\n");
    n = append2str(n, "GEE\n");

    long t = findstr(n, "BEEP");
    printf("%ld '%s'\n", t, n->data);

    char *test = replace_string(n, "BEEP", "LUL");
    printf("%s\n", test);
    return 0;
}