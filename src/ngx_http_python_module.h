/**
 *    Copyright(c) 2016 rryqszq4
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

#define MODULE_NAME "ngx_python"
#define MODULE_VERSION "0.0.1"

extern ngx_module_t ngx_http_python_module;
ngx_http_request_t *ngx_python_request;

typedef struct {
    unsigned enabled_content_handler:1;
} ngx_http_python_main_conf_t;

typedef struct {
    ngx_http_python_code_t *content_code;
    ngx_http_python_code_t *content_inline_code;
} ngx_http_python_loc_conf_t;

#endif