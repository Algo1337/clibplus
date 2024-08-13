#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/OS/Utils.h>

int main() {
    str *cmd = ExecuteCmd("ifconfig");
    printf("%s\n", cmd->data);
    return 0;
}