/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#ifndef NGX_HTTP_PY_MODULE_H
#define NGX_HTTP_PY_MODULE_H

#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_config.h>
#include <nginx.h>

#define MODULE_NAME "ngx_py"
#define MODULE_VERSION "0.0.1"

extern ngx_module_t ngx_http_py_module;
ngx_http_request_t *ngx_py_request;

typedef struct {
    unsigned enable_content_handler:1;
} ngx_http_py_main_conf_t;

typedef struct {
    ngx_http_py_code_t *content_file;
    ngx_http_py_code_t *content_inline_code;
} ngx_http_py_loc_conf_t;

#endif