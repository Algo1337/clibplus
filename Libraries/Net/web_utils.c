#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "web.h"

char *JS_VAR[] = {"const ", " = document.getElementById('", "').value;\n"};

char *PATH = "path?";

char *JS_FORM_VAR[] = {"<script>\n\n document.getElementById('",
    "').addEventListener('click', function() { ",
    "fetch(`http://127.0.0.1", 
    "`).then(response => response.text()).then(data => {document.getElementById('",
    "').innerText = data;}).catch(error => {console.error('Error:', error);});}); \n\n</script>"};

str *construct_path(str *route, Map *parameters) {
    str *para = string(route->data);
    para->AppendString(para, "?");
    for(int i = 0; i < parameters->idx; i++) {
        if(i > 0)
            para->AppendString(para, "&");
        para->AppendString(para, (char *)((Key *)parameters->keys[i])->name);
        para->AppendString(para, "=${encodeURIComponent(");
        para->AppendString(para, (char *)((Key *)parameters->keys[i])->value);
        para->AppendString(para, ")}");
    }

    return para;
}

str *construct_js_var(Map *vars) {
    str *code = string(NULL);
    for(int i = 0; i < vars->idx; i++) {
        if(!strcmp((char *)((Key *)vars->keys[i])->name, "TEXT_INPUT")) {
            for(int j = 0; j < 3; j++) {
                code->AppendString(code, JS_VAR[j]);
                if(j != 2)
                    code->AppendString(code, (char *)((Key *)vars->keys[i])->value);
            }
        }
    }

    return code;
}

str *construct_js_input_var(str *route, Map *vars, Map *parameters) {
    str *js_code = string(NULL);
    for(int i = 0; i < 5; i++) {
        js_code->AppendString(js_code, JS_FORM_VAR[i]);
        switch(i) {
            case 0: {
                js_code->AppendString(js_code, (char *)((Key *)vars->keys[vars->idx - 2])->value);
                break;
            }
            case 1: {
                js_code->AppendString(js_code, construct_js_var(vars)->data);
                break;
            }
            case 2:
            {
                js_code->AppendString(js_code, construct_path(route, parameters)->data);
                break;
            }
            case 3: {
                js_code->AppendString(js_code, (char *)((Key *)vars->keys[vars->idx - 1])->value);
                break;
            }
        }

    }

    return js_code;
}