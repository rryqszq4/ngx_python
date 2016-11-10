/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#ifndef NGX_HTTP_PYTHON_HANDLER_H
#define NGX_HTTP_PYTHON_HANDLER_H

#include <nginx.h>
#include <ngx_http.h>

#include "ngx_http_python_module.h"

ngx_int_t ngx_http_python_content_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_python_content_file_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_python_content_inline_handler(ngx_http_request_t *r);

#endif