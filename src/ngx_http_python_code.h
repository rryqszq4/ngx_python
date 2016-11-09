/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#ifndef NGX_HTTP_PYTHON_CODE_H
#define NGX_HTTP_PYTHON_CODE_H

#include <ngx_http.h>

extern ngx_http_request_t *ngx_python_request;

typedef enum code_type_t {
    NGX_HTTP_PYTHON_CODE_TYPE_FILE,
    NGX_HTTP_PYTHON_CODE_TYPE_STRING
} code_type_t;

typedef struct ngx_http_python_code_t {
    union code {
        char *file;
        char *string;
    } code;
    code_type_t code_type;
} ngx_http_python_code_t;


ngx_http_python_code_t *ngx_http_python_code_from_file(ngx_pool_t *pool, ngx_str_t *code_file_path);
ngx_http_python_code_t *ngx_http_python_code_from_string(ngx_pool_t *pool, ngx_str_t *code_str);

#endif