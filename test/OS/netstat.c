#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/OS/Utils.h>
#include <clib/String/str.h>
#include <clib/Array/arr.h>

typedef enum Protocol {
    __NULL,
    __UDP,
    __TCP
} Protocol;

typedef enum ConState {
    _null,
	close_wait,
	closed,
	established,
	fin_wait1,
	fin_wait2,
	last_ack,
	listen,
	syn_recv,
	syn_sent,
	time_wait,
	closing
} ConState;

typedef struct Netstat {
    Protocol    protocol;
    int         bytes_recv;
    int         bytes_sent;
    str         *source_ip;
    int         source_port;
    str         *destination_ip;
    int         destination_port;
    ConState    state;
} Netstat;

Netstat **CONNECTIONS;
size_t    Count;

void new_con(const char **arr) {
    Netstat *con = (Netstat *)malloc(sizeof(Netstat));
    if(!strcmp(arr[0], "Proto"))
        return;

    if(!strcmp(arr[0], "tcp"))
        con->protocol = __TCP;
        
    con->bytes_recv = atoi(arr[1]);
    con->bytes_sent = atoi(arr[2]);

    str *src_ip_info = string(arr[3]);
    str *dest_ip_info = string(arr[4]);

    char **src_ip_args = src_ip_info->Split(src_ip_info, ":");
    char **dest_ip_args = dest_ip_info->Split(dest_ip_info, ":");

    con->source_ip = string(src_ip_args[0]);
    con->source_port = atoi(src_ip_args[1]);
    free(src_ip_info);
    free(src_ip_args);

    con->destination_ip = string(dest_ip_args[0]);
    con->destination_port = atoi(dest_ip_args[1]);
    free(dest_ip_info);
    free(dest_ip_args);

    if(!strcmp(arr[5], "ESTABLISHED"))
        con->state = established;
    else
        con->state = _null;

    CONNECTIONS[Count] = con;
    Count++;
    CONNECTIONS = (Netstat **)realloc(CONNECTIONS, (sizeof(Netstat *) * Count) + 1);
}

Netstat **get_netstat() {
    CONNECTIONS = (Netstat **)malloc(sizeof(Netstat *) * 1);
    memset(CONNECTIONS, '\0', sizeof(Netstat *) * 1);
    Count = 0;
    str *s = ExecuteCmd("netstat -tn");

    char **lines = s->Split(s, "\n");
    int line_count = count_arr((char **)lines);

    for(int i = 1; i < line_count; i++) {
        str *line = string(lines[i]);
        char **args = line->Split(line, " ");
        int arg_count = count_arr(args);
        
        if(arg_count < 3)
            break;

        new_con((const char **)args);
        free(line);
        free(args);
    }

    free(lines);
    free(s);

    return CONNECTIONS;
}

int main() {
    Netstat **cons = get_netstat();
    for(int i = 0; i < Count; i++)
        printf("%s:%d => %s:%d\n", cons[i]->source_ip->data, cons[i]->source_port, cons[i]->destination_ip->data, cons[i]->destination_port);
    return 0;
}