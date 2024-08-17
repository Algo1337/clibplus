#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/String/str.h>
#include <clib/Net/request.h>

int main() {
    Arr *test = parse_url("https://api.vedbex.com/v2/free/subdomainfinder?domain=google.com&token=0c0bf7acveddcdfv00fd0hce4cd9bf7b&stoken=3ce9b865ee40d4e49b5ea520a87a199b&id=992&ses=v0c57av9dhccv0cfcd8400fbhb8ff0ha");
    printf("'%s' => %s\n", test->arr[0], test->arr[1]);
    
    test = parse_url("https://chatgpt.com/c/d442b22d-ed4a-4693-a0a3-4f704ffb75e7");
    printf("%s => %s\n", test->arr[0], test->arr[1]);
    
    test = parse_url("https://google.com/");
    printf("%s => %s\n", test->arr[0], test->arr[1]);

    test = parse_url("google.com/");
    printf("%s => %s\n", test->arr[0], test->arr[1]);

    test = parse_url("https://google.com");
    printf("%s => %s\n", test->arr[0], test->arr[1]);
    return 0;    
}