#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#include "str.h"

str *string(const char *data) {
    str *s = (str *)malloc(sizeof(str));

    s->BASE = s;

    s->NewString            = __newString;
    s->AppendString         = __add2str;
    s->CountChar            = __CountChar;
    s->FindChar             = findchar;
    s->FindCharAt           = findchar_at_count;
    s->Strip                = __Strip;
    s->StripCh2End          = __StripCh2End;
    s->IsEmpty              = _IsEmpty;
    s->Trim                 = __Trim;
    s->TrimAtIdx            = __Trim_By_Idx;
    s->CountSubstr          = __CountSubstr;
    s->FindSubstr           = __findSubstr;
    s->GetSubstr            = get_substr;
    s->RemoveSubstr         = remove_substr;
    s->StartsWith           = __StartsWith;
    s->EndsWith             = __EndsWith;
    s->IsUppercase          = __IsUppercase; 
    s->IsLowercase          = __IsLowercase;
    s->ToUppercase          = __ToUppercase;
    s->ToLowercase          = __ToLowercase;
    s->ReplaceString        = replace_string;
    s->ReplaceChar          = __ReplaceChar;
    s->ReplaceCharWithStr   = __ReplaceCharWithStr;
    s->Split                = __Split;
    s->SplitStringWithChar  = split_string_w_char;
    s->Join                 = __Join;

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

int __newString(str *s, const char *data) {
    if(strlen(data) == 0)
        return 0;

    if(s->data == NULL) {
        s->data = strdup(data);
        s->idx = strlen(data) + 1;
        return 1;
    }

    free(s->data);
    s->data = (char *)alloc(strlen(data) + 1);
    strcpy(s->data, data);
    s->idx = (long)strlen(data) + 1;
    return 1;
}

int __add2str(str *s, const char *data) {
    if(s->data == NULL || strlen(s->data) == 0) {
        *s = *string(data);
        return 0;
    }

    char *new = (char *)alloc(strlen(s->data) + strlen(data) + 1);
    strcpy(new, s->data);
    strcat(new, data);

    s->idx = strlen(s->data) + strlen(data);
    s->data = strdup(new);
    free(new);

    return 1;
}

// == [ DEALING WITH BYTES ] ==

long __CountChar(str *s, const char ch) {
    long count = 0;
    for(int i = 0; i < s->idx; i++)
        if(s->data[i] == ch)
            count++;

    return count;
}

// only find the first matched char and return position
long findchar(str *s, const char ch) {
    return findchar_at_count(s, ch, 0);
}

// If a char is found the number of count provided, it will return the position of the char in string
long findchar_at_count(str *s, const char ch, int count) {
    int c = 0;
    for(int i = 0; i < s->idx; i++) {
        if(s->data[i] == ch)
            c++;

        if(c == count || (s->data[i] == ch && count == 0))
            return i;
    }

    return 0;
}

long __Strip(str *s) {
    char *buffer = (char *)alloc(strlen(s->data) + 1);
    
    int start = 0;
    while(s->data[start] != '\0')
        if(isspace(s->data[start]))
            start++;
        else
            break;

    int end = strlen(s->data) - 1;
    while(s->data[end] != '\0')
        if(isspace(s->data[end]))
            end--;
        else
            break;

    for(int i = start; i < end + 1; i++)
        strncat(buffer, &s->data[i], sizeof(char));

    s->data = strdup(buffer);
    s->idx = strlen(buffer) + 1;
    free(buffer);

    return (start > 0 && end < strlen(s->data) ? 1 : 0);
}

long __StripCh2End(str *s, const char start) {
    char *new = (char *)alloc(1);
    
    int i = 0;
    while(i < s->idx) {
        if(s->data[i] == start)
            break;

        
        strncat(new, &s->data[i], sizeof(char));
        i++;
        new = (char *)realloc(new, i + 1);
        if(new)
            break;
    }

    free(s->data);
    s->data = strdup(new);
    s->idx = strlen(new);

    return 1;
}

long _IsEmpty(str *s) { 
    if(s == NULL || s->data == NULL)
        return -1;

    for(int i = 0; i < s->idx; i++) {
        if(s->data[i] == '\0')
            break;

        if(!isblank(s->data[i]))
            return -1;
    }

    return 1;
}

long __Trim(str *s, const char delim) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    char *buffer = (char *)alloc(strlen(s->data));
    memset(buffer, '\0', strlen(s->data) + 1);
    
    int start = 0;
    for(int i = 0; i < strlen(s->data); i++) {
        if(s->data[i] != delim) {
            strncat(buffer, &s->data[start], sizeof(char));
            start++;
        }
    }

    int modify_chk = strlen(buffer) < strlen(s->data) ? 1 : 0;
    s->data = strdup(buffer);
    free(buffer);

    return modify_chk;
}

long __Trim_By_Idx(str *s, int idx) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    char *buffer = (char *)alloc(strlen(s->data));
    memset(buffer, '\0', strlen(s->data));
    
    int start = 0;
    for(int i = 0; i < strlen(s->data); i++) {
        if(i != idx) {
            strncat(buffer, &s->data[i], sizeof(char));
        }
    }

    int modify_chk = strlen(buffer) < strlen(s->data) ? 1 : 0;
    s->data = strdup(buffer);
    free(buffer);
    s->idx--;

    return modify_chk;
}

// == [ DEALING WITH STRING ] == 

long __findSubstr(str *s, const char *substr) {
    for(int i = 0; i < s->idx; i++) {
        if(s->data[i] == substr[0] && s->data[s->idx] == substr[strlen(substr)]) {
            return i;
        }
    }

    return 0;
}

long __CountSubstr(str *s, const char *substr) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    long count = 0;
    if(strlen(substr) < 2) 
        return 0;

    for(int i = 0; i < strlen(s->data); i++)
        if(s->data[i] == substr[0] && s->data[ i + strlen(substr)-1 ] == substr[strlen(substr) - 1])
            count++;

    return count;
}

char *get_substr(str *s, int start, int end) {
    int left = end-start;
    char *new = (char *)alloc(s->idx + left + 1);
    int idx = 0;
    for(int i = 0; i < s->idx; i++) { 
        if(i >= start && i < end) {
            strncat(new, &s->data[i], sizeof(char));
            idx++;
            // new = (char*)realloc(new, idx + 1);
        }
    }

    return new;
}

int remove_substr(str *s, int start, int end) {
    char *new = (char *)alloc(1);

    int ch = 0;
    for(int i = 0; i < s->idx; i++)
    {
        if(i < start || i > end) {
            strncat(new, &s->data[ch], sizeof(char));
            ch++;
            new = (char *)realloc(new, ch + 1);
        }
    }

    s->data = strdup(new);
    s->idx = strlen(new);
    free(new);

    return 1;
}

long __StartsWith(str *s, const char *str) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    if(strlen(str) < 2) 
        return 0;

    long count = 0;
    for(int i = 0; i < strlen(str); i++)
        if(s->data[i] == str[i])
            count++;
    
    return (count == strlen(str) ? 1 : 0);
}

long __EndsWith(str *s, const char *str) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    if(strlen(str) < 1)
        return 0;

    long count = 0;
    for(int i = strlen(s->data) - strlen(str); i < strlen(s->data); i++)
        if(s->data[i] == str[count])
            count++;

    return (count == strlen(str) ? 1 : 0);
}

long __IsUppercase(str *s) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    for(int i = 0; i < strlen(s->data) - 1; i++)
        if(!isupper(s->data[i]))
            return 0;

    return 1;
}

long __IsLowercase(str *s) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    for(int i = 0; i < strlen(s->data) - 1; i++)
        if(!islower(s->data[i]))
            return 0;

    return 1;
}

long __ToUppercase(str *s) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    char *buffer = (char *)alloc(strlen(s->data) + 1);
    long chk = 0;

    for(int i = 0; i < strlen(s->data); i++) {
        if(isalpha(s->data[i]) && !isupper(s->data[i])) {
            chk++;
            char byte = toupper(s->data[i]);
            strncat(buffer, &byte, sizeof(char));
            continue;
        }

        strncat(buffer, &s->data[i], sizeof(char));
    }

    s->data = strdup(buffer);
    free(buffer);

    return chk;
}

long __ToLowercase(str *s) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    char *buffer = (char *)alloc(strlen(s->data) + 1);
    long chk = 0;

    for(int i = 0; i < strlen(s->data); i++) {
        if(isalpha(s->data[i]) && !islower(s->data[i])) {
            chk++;
            char byte = tolower(s->data[i]);
            strncat(buffer, &byte, sizeof(char));
            continue;
        }

        strncat(buffer, &s->data[i], sizeof(char));
    }

    s->data = strdup(buffer);
    free(buffer);

    return chk;
}

long __ReplaceChar(str *s, const char ch, const char r) {
    char *new = (char *)alloc(strlen(s->data) + 1);
    int i = 0;
    while(i < s->idx) {
        if(s->data[i] == ch) {
            strncat(new, &r, sizeof(char));
            i++;
            continue;
        }

        strncat(new, &s->data[i], sizeof(char));
        i++;
    }

    free(s->data);
    s->data = strdup(new);
    s->idx = strlen(s->data) + 1;
}

long __ReplaceCharWithStr(str *s, const char ch, const char *r) {
    long c = __CountChar(s, ch) * strlen(r) + strlen(s->data);
    char *new = (char *)alloc(c);

    for(int i = 0; i < strlen(s->data); i++) {
        if(s->data[i] == ch) {
            strncat(new, r, strlen(r));
            continue;
        }

        strncat(new, &s->data[i], sizeof(char));
    }

    free(s->data);
    s->data = new;
    s->idx = c;

    return 1;
}

char *replace_string(str *s, const char *find, const char *replace) {
    char *new = (char *)alloc(s->idx + strlen(replace) + 1);
    int string_at = __findSubstr(s, find);
    int i = 0;
    while(i < s->idx) {
        if(s->data[i] == NULL)
            break;

        if(i >= string_at && i < (string_at + strlen(find))) {
            strncat(new, replace, strlen(replace));
            i += strlen(find);
            continue;
        }

        strncat(new, &s->data[i], sizeof(char));
        i++;
    }
    s->idx = strlen(s->data) + strlen(replace) + 1;
    s->data = strdup(new);
    free(new);

    return s->data;
}

char **__Split(str *s, const char *delim) {
    char **arr = (char **)alloc2(1);

    int i = 0, idx = 0;
    char *token = strtok(s->data, delim);
    while(token != NULL) {
        arr[i] = (char *)alloc(strlen(token) + 1);
        strcpy(arr[i], token);
        token = strtok(NULL, delim);
        i++;
        arr = (char **)realloc(arr, (sizeof(char *) * i) + 1);
    }
    arr[i] = NULL;

    

    return arr;
}

char **split_string_w_char(str *s, const char delim) {
    long count = __CountChar(s, delim) + 1;
    
    char **arr = (char **)alloc2(count);
    long idx = 0;

    int start = findchar_at_count(s, delim, 0), end = 0;
    for(int i = 1; i < count + 1; i++)
    {
        end = findchar_at_count(s, delim, i);
        char *sub = get_substr(s, start, end);

        if(i > 1) {
            if(end == 0)
                end = s->idx;
            sub = get_substr(s, start + 1, end);
        }

        arr[idx] = strdup(sub);
        idx++;
        free(sub);
        start = end;
    }
    arr[idx] = NULL;

    return arr;
}

long __Join(str *s, const char **arr, const char delim) {
    if(arr == NULL)
        return 0;
        
    int i = 0;
    while(arr[i] != NULL)
    {
        if(arr[i] == NULL)
            break;
            
        s->data = (char *)realloc(s->data, s->idx + strlen(arr[i]) + 1);
        strncat(s->data, arr[i], strlen(arr[i]));
        if(arr[ i + 1] != NULL)
            strncat(s->data, &delim, sizeof(char));
        i++;
        s->idx += strlen((const char *)&arr[i]) + 1;
    }

    return 1;
}

void CleanString(str *s) {
    if(s->data == NULL)
        return;

    s->idx = 0;
    free(s);
}