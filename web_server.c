#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <clib/Array/arr.h>
#include <clib/Map/map.h>
#include <clib/Net/web.h>
#include <clib/OS/cFile.h>
#include <clib/Net/request.h>

void *index_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    printf("[ \x1b[32m/\x1b[0m ] Page Visited\n");

    Map *headers = create_map();
    headers->Utils(headers, __ADD_KEY, "Content-Type", "text/html; charset=UTF-8");
    headers->Utils(headers, __ADD_KEY, "Connection", "close");

    Map *vars = create_map();
    cFile *css = Openfile("pages/css_files/styles.css");
    cFile *statistic = Openfile("pages/css_files/statistics.css");
    css->Read(css);
    statistic->Read(statistic);
    vars->Utils(vars, __ADD_KEY, "$CSS_FILE", css->data);
    vars->Utils(vars, __ADD_KEY, "$CSS_STATISTIC_FILE", statistic->data);

    SendResponse(s, request_socket, OK, headers, "pages/index.html", vars);
    free(css);
    free(statistic);
}

void *doc_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    printf("[ \x1b[32m/doc\x1b[0m ] Page Visited\n");

    Map *headers = create_map();
    headers->Utils(headers, __ADD_KEY, "Content-Type", "text/html; charset=UTF-8");
    headers->Utils(headers, __ADD_KEY, "Connection", "close");

    SendResponse(s, request_socket, OK, headers, "pages/doc.html", NULL);
}

void *source_code_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    printf("[ \x1b[32m/source_code\x1b[0m ] Page Visited\n");

    Map *headers = create_map();
    headers->Utils(headers, __ADD_KEY, "Content-Type", "text/html; charset=UTF-8");
    headers->Utils(headers, __ADD_KEY, "Connection", "close");
    
    SendResponse(s, request_socket, OK, headers, "pages/source_code.html", NULL);
}

void *test_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    printf("[ \x1b[32m/post\x1b[0m ] Page Visited\n");

    str *key = string("Input: ");
    if(!strcmp(r->request_type->data, "POST"))
        if(r->queries->Utils(r->queries, __IN_KEYS, "name_input"))
            key->AppendString(key, (char *)r->queries->Utils(r->queries, __GET_KEY_VALUE, "name_input"));

        if(!strcmp(key->data, "Input: ")) {
            key->AppendString(key, "N/A");
    }

    Map *headers = create_map();
    headers->Utils(headers, __ADD_KEY, "Content-Type", "text/html; charset=UTF-8");
    headers->Utils(headers, __ADD_KEY, "Connection", "close");

    Map *vars = create_map();
    vars->Utils(vars, __ADD_KEY, "$INPUT", key->data);
    
    SendResponse(s, request_socket, OK, headers, "pages/post.html", vars);
}

void get_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    printf("[ \x1b[32m/get\x1b[0m ] Page Visited\n");

    str *key = string("Input: ");
    if(retrieve_get_parameter(s, r) > 0) {
        key->AppendString(key, (char *)r->queries->Utils(r->queries, __GET_KEY_VALUE, "q"));

        printf("%s\n", key->data);
    } else {
        key->AppendString(key, "N/A");
    }

    Map *headers = create_map();
    headers->Utils(headers, __ADD_KEY, "Content-Type", "text/html; charset=UTF-8");
    headers->Utils(headers, __ADD_KEY, "Connection", "close");

    Map *vars = create_map();
    vars->Utils(vars, __ADD_KEY, "$INPUT", key->data);

    SendResponse(s, request_socket, OK, headers, "pages/get.html", vars);
}



void live_action_test_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    printf("[ \x1b[32m/test\x1b[0m ] Page Visited\n");

    Map *headers = create_map();
    headers->Utils(headers, __ADD_KEY, "Content-Type", "text/html; charset=UTF-8");
    headers->Utils(headers, __ADD_KEY, "Connection", "close");

    /* Handle GETs for Updates*/
    str *key = string("Response: ");
    if(retrieve_get_parameter(s, r) > 0) {
        key->AppendString(key, (char *)r->queries->Utils(r->queries, __GET_KEY_VALUE, "q"));
        key->AppendString(key, " | ");
        key->AppendString(key, (char *)r->queries->Utils(r->queries, __GET_KEY_VALUE, "a"));
        write(request_socket, key->data, strlen(key->data));
        return;
    }

    /* Create form for handler (Implement JS input handlers) */
    Map *form = create_map();
    form->Utils(form, __ADD_KEY, "TEXT_INPUT", "name_input");
    form->Utils(form, __ADD_KEY, "TEXT_INPUT", "age_input");
    form->Utils(form, __ADD_KEY, "SUBMIT_BUTTON", "NIGGER");
    form->Utils(form, __ADD_KEY, "RESPONSE_NAME", "response");

    /* Create parameter handler for the JS code */
    Map *parameters = create_map();
    parameters->Utils(parameters, __ADD_KEY, "q", "name_input");
    parameters->Utils(parameters, __ADD_KEY, "a", "age_input");
    str *raw_form = construct_js_input_var(r->route, form, parameters);

    /* Replace Var With JS Code */
    Map *html_vars = create_map();
    html_vars->Utils(html_vars, __ADD_KEY, "$FORM_LOGIN", raw_form->data);

    SendResponse(s, request_socket, OK, headers, "pages/test.html", html_vars);
}

void *login_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    
    Map *vars = create_map();
    cFile *css = Openfile("pages/css_files/styles.css");
    cFile *button_css = Openfile("pages/css_files/buttons.css");
    css->Read(css);
    button_css->Read(button_css);
    vars->Utils(vars, __ADD_KEY, "$CSS_FILE", css->data);
    vars->Utils(vars, __ADD_KEY, "$CSS_BUTTONS_FILE", button_css->data);

    Map *headers = create_map();
    headers->Utils(headers, __ADD_KEY, "Content-Type", "text/html; charset=UTF-8");
    headers->Utils(headers, __ADD_KEY, "Connection", "close");

    SendResponse(s, request_socket, OK, headers, "pages/login.html", vars);
    free(css);
    free(vars);
    free(headers);
    free(button_css);
}

int main() {
    HTTPServer *s = StartWebServer(NULL, 80, 0);
    Add404Page(s, "404.html");
    
    AddRoute(s, "/index", index_page);
    AddRoute(s, "/doc", doc_page);
    AddRoute(s, "/source_code", source_code_page);
    AddRoute(s, "/post", test_page);
    AddRoute(s, "/get", get_page);
    AddRoute(s, "/test", live_action_test_page);
    AddRoute(s, "/login", login_page);

    StartListener(s);
    return 0;
}
