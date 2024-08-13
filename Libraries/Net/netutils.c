#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../String/str.h"
#include "../Array/arr.h"

int validate_ipv4(str *ip) {
    char **args = ip->Split(ip, ".");
    int arg_c = count_arr(args);
    if(arg_c != 4)
        return 0;

    for(int i = 0; i < 3; i++) {
        if(isdigit(args[i]) == 0) {
            return 0;
        }
    }

    if(atoi(args[0]) < 1 && atoi(args[0]) > 255) {
        return 0;
    } else if((atoi(args[1]) < 0 && atoi(args[1]) > 255) || (atoi(args[2]) < 0 && atoi(args[2]) > 255) || (atoi(args[3]) < 0 && atoi(args[3]) > 255)) {
        return 0;
    }

    
    free(args);
    return 1;
}