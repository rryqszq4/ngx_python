/**
 *    Copyright(c) 2016-2017 rryqszq4
 *
 *
 */

#ifndef NGX_HTTP_PYTHON_MODULE_H
#define NGX_HTTP_PYTHON_MODULE_H

#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_config.h>
#include <nginx.h>

#include "ngx_http_python_code.h"

#define NGX_HTTP_PYTHON_MODULE_NAME "ngx_python"
#define NGX_HTTP_PYTHON_MODULE_VERSION "0.0.1"

extern ngx_module_t ngx_http_python_module;
ngx_http_request_t *ngx_python_request;

typedef struct {
    unsigned enabled_rewrite_handler:1;
    unsigned enabled_access_handler:1;
    unsigned enabled_content_handler:1;
    unsigned enabled_log_handler:1;
} ngx_http_python_main_conf_t;

typedef struct {
    ngx_http_python_code_t *rewrite_file_code;
    ngx_http_python_code_t *rewrite_inline_code;
    ngx_http_python_code_t *access_file_code;
    ngx_http_python_code_t *access_inline_code;
    ngx_http_python_code_t *content_file_code;
    ngx_http_python_code_t *content_inline_code;
    ngx_http_python_code_t *log_file_code;
    ngx_http_python_code_t *log_inline_code;

    ngx_int_t (*rewrite_handler)(ngx_http_request_t *r);
    ngx_int_t (*access_handler)(ngx_http_request_t *r);
    ngx_int_t (*content_handler)(ngx_http_request_t *r);
    ngx_int_t (*log_handler)(ngx_http_request_t *r);

    unsigned enabled_content_inline_compile:1;

} ngx_http_python_loc_conf_t;

#endif