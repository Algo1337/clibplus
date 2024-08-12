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

        if(c == count)
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
    int count = 0;
    for(int i = 0; i < s->idx; i++)
        if(s->data[i] == ch)
            count++;

    return count;
}

char *get_substr(String *s, int start, int end) {
    char *new = (char *)alloc(end + 1);
    int idx = 0;
    for(int i = 0; i < s->idx; i++) { 
        if(i >= start && i <= end) {
            strcat(new, &s->data[i]);
            idx++;
            new = (char *)realloc(new, idx + 1);
        }
    }

    return new;
}

char **split_string_w_char(String *s, const char delim) {
    int char_count = count_char(s, delim);
    char **new = (char *)alloc2(char_count + 1);

    int start = 0;
    for(int i = 0; i < char_count + 1; i++) {
        int pos = findchar_at_count(s, delim, i);
        start = pos;
        char *substr = get_substr(s, start, pos);
        new[i] = strdup(substr);
        free(substr);
    }

    return new;
}

int main() {
    String *n = string(NULL);
    n = append2str(n, "NEW");
    n = append2str(n, "\nBEEP");
    n = append2str(n, "\nGEE");

    char **lines = split_string_w_char(n, '\n');
    for(int i = 0; i < 3; i++)
        printf("%s\n", lines[i]);
    return 0;
}