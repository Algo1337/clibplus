#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <clib/Net/netutils.h>

int main() {
    str *t = string("7.7.7.7");
    printf("%d\n", validate_ipv4(t));
    return 0;
}