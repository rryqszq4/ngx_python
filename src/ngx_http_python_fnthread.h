/**
 *    Copyright(c) 2016-2019 rryqszq4
 */

#ifndef NGX_HTTP_PYTHON_FNTHREAD_H
#define NGX_HTTP_PYTHON_FNTHREAD_H

#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>

void ngx_http_python_fnthread_content_inline_routine(ngx_http_request_t *r);

void ngx_http_python_fnthread_create(ngx_http_request_t *r, char *func_prefix);

void ngx_http_python_fnthread_resume(ngx_http_request_t *r);

void ngx_http_python_fnthread_exit(ngx_http_request_t *r);

#endif