#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Libraries/Map/map.h"

int main() {
    Map *m = create_map();
    m->Utils(m, __ADD_KEY, "TEST", "THIS");
    m->Utils(m, __ADD_KEY, "LUL", "ME");
    m->Utils(m, __ADD_KEY, "BEEP", "BOOP");
    m->Utils(m, __ADD_KEY, "ALIAS", "CHRIS");

    printf("%ld\n", m->idx);
    for(int i = 0; i < m->idx; i++)
        if(m->keys[i] != NULL)
            printf("%s %s\n", m->keys[i]->name, m->keys[i]->value);

    Key *k = (Key *)m->Utils(m, __GET_KEY, "TEST");
    if(k == NULL)
        err_n_exit("Failed");
    printf("%s\n", k->value);
    return 0;
}