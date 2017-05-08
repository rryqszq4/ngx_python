/**
 *    Copyright(c) 2016-2017 rryqszq4
 *
 *
 */

#include "ngx_python_uthread.h"

static void ngx_python_uthread_routine(ngx_python_uthread_t *uthread);

static void 
ngx_python_uthread_routine(ngx_python_uthread_t *uthread)
{
    uthread->routine(uthread->data);
}

ngx_int_t 
ngx_python_uthread_create(ngx_python_uthread_t *uthread)
{

    if (getcontext(&uthread->child) == -1) {
        return -1;
    }

    ngx_python_uthread_max++;
    uthread->id = ngx_python_uthread_max;
    uthread->status = PYTHON_UTHREAD_READY;

    uthread->child.uc_stack.ss_size = PYTHON_UTHREAD_STACK_SIZE;
    uthread->child.uc_stack.ss_sp = uthread->stack;
    uthread->child.uc_link = &uthread->main;

    makecontext(&uthread->child, (void (*)(void)) ngx_python_uthread_routine, 1, uthread);

    if (swapcontext(&uthread->main, &uthread->child) == -1) {
        return -1;
    }

    return 0;

}

ngx_int_t 
ngx_python_uthread_yield(ngx_python_uthread_t *uthread)
{
    uthread->status = PYTHON_UTHREAD_RUNNING;
    
    if (swapcontext(&uthread->child, &uthread->main) == -1) {
        return -1;
    }

    return 0;
}

ngx_int_t 
ngx_python_uthread_resume(ngx_python_uthread_t *uthread)
{
    uthread->status = PYTHON_UTHREAD_SUSPEND;

    if (swapcontext(&uthread->main, &uthread->child) == -1) {
        return -1;
    }

    return 0;
}


ngx_uint_t 
ngx_python_uthread_id(ngx_python_uthread_t *uthread)
{
    if (uthread->id) {
        return uthread->id;
    }

    return 0;
}



