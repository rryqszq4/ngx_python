/**
 *    Copyright(c) 2016-2017 rryqszq4
 *
 *
 */

#ifndef _NGX_PYTHON_UTHREAD_H_
#define _NGX_PYTHON_UTHREAD_H_

#include <ngx_config.h>
#include <ngx_core.h>

#include <ucontext.h>

#define PYTHON_UTHREAD_DEAD    0
#define PYTHON_UTHREAD_READY   1
#define PYTHON_UTHREAD_RUNNING 2
#define PYTHON_UTHREAD_SUSPEND 3

#define PYTHON_UTHREAD_STACK_SIZE      32*1024
#define PYTHON_UTHREAD_MAX_SIZE        1024

ngx_uint_t ngx_python_uthread_max;

typedef struct ngx_python_uthread_s {

    ngx_uint_t      id;
    ngx_int_t       status;

    ucontext_t      child;
    ucontext_t      main;

    void            *stack;
    size_t          stack_size;

    void            (*routine)(void *data);
    void            *data;

    ngx_log_t       *log;

} ngx_python_uthread_t;

ngx_int_t ngx_python_uthread_create(ngx_python_uthread_t *uthread);

ngx_int_t ngx_python_uthread_yield(ngx_python_uthread_t *uthread);

ngx_int_t ngx_python_uthread_resume(ngx_python_uthread_t *uthread);

ngx_int_t ngx_python_uthread_destroy(ngx_python_uthread_t *uthread);

ngx_uint_t ngx_python_uthread_id(ngx_python_uthread_t *uthread);

#endif