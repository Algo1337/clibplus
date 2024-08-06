#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void looop(const char **arr) {
    int i = 0;
    while(arr[i] != NULL) {
        printf("%s\n", arr[i]);
        i++;
    }
}

int main() {
  printf("==== [ TEST 1 ] ====\n");
  char *t[] = {"Test", "0", "GAY", "\0"};
  looop((const char **)t);

  printf("==== [ TEST 2 ] ====\n");
  char *g[] = {"Test", "0", "GAY"};
  looop((const char **)g);

  printf("==== [ TEST 3 ] ====\n");
  char *b[] = {"Test", "0", "\0", "G", NULL, "GAY"};
  looop((const char **)b);
  return 0;
}