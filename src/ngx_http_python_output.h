/**
 *    Copyright(c) 2016-2017 rryqszq4
 */

#ifndef NGX_HTTP_PYTHON_OUTPUT_H
#define NGX_HTTP_PYTHON_OUTPUT_H

#include <nginx.h>
#include <ngx_http.h>

void ngx_http_python_set_output(ngx_http_request_t *r, char *buffer, int buffer_len);

void ngx_http_python_check_output_empty(ngx_http_request_t *r);

#endif