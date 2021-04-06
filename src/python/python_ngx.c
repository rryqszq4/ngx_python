/**
 *    Copyright(c) 2016-2017 rryqszq4
 *
 *
 */

#include <Python.h>
#include "python_ngx.h"
#include "../ngx_http_python_module.h"
#include "../ngx_http_python_code.h"

static PyObject *
ngx_echo(PyObject *self, PyObject *args)
{
    PyObject *object;

    ngx_buf_t *b;
    ngx_http_python_rputs_chain_list_t *chain;
    ngx_http_python_ctx_t *ctx;
    ngx_http_request_t *r;
    u_char *u_str;
    ngx_str_t ns;

    r = ngx_python_request;
    ctx = ngx_http_get_module_ctx(r, ngx_http_python_module);

    if (!PyArg_ParseTuple(args, "O", &object)){
        return NULL;
    }

    PyObject *s;
    s = PyObject_Str(object);
    ns.data = (u_char *)PyUnicode_AsUTF8AndSize(s, (Py_ssize_t *)&ns.len);

    if (ctx->rputs_chain == NULL){
        chain = ngx_pcalloc(r->pool, sizeof(ngx_http_python_rputs_chain_list_t));
        chain->out = ngx_alloc_chain_link(r->pool);
        chain->last = &chain->out;
    }else {
        chain = ctx->rputs_chain;
        (*chain->last)->next = ngx_alloc_chain_link(r->pool);
        chain->last = &(*chain->last)->next;
    }

    b = ngx_calloc_buf(r->pool);
    (*chain->last)->buf = b;
    (*chain->last)->next = NULL;

    u_str = ngx_pstrdup(r->pool, &ns);
    //u_str[ns.len] = '\0';
    (*chain->last)->buf->pos = u_str;
    (*chain->last)->buf->last = u_str + ns.len;
    (*chain->last)->buf->memory = 1;
    ctx->rputs_chain = chain;
    ngx_http_set_ctx(r, ctx, ngx_http_python_module);

    if (r->headers_out.content_length_n == -1){
        r->headers_out.content_length_n += ns.len + 1;
    }else {
        r->headers_out.content_length_n += ns.len;
    }

    return Py_BuildValue("i", r->headers_out.content_length_n);
}

static PyObject *
ngx_print(PyObject *self, PyObject *args)
{
    PyObject *object;

    ngx_buf_t *b;
    ngx_http_python_rputs_chain_list_t *chain;
    ngx_http_python_ctx_t *ctx;
    ngx_http_request_t *r;
    u_char *u_str;
    ngx_str_t ns;

    r = ngx_python_request;
    ctx = ngx_http_get_module_ctx(r, ngx_http_python_module);

    if (!PyArg_ParseTuple(args, "O", &object)){
        return NULL;
    }

    PyObject *s;
    s = PyObject_Str(object);
    ns.data = (u_char *)PyUnicode_AsUTF8AndSize(s, (Py_ssize_t *)&ns.len);

    if (ctx->rputs_chain == NULL){
        chain = ngx_pcalloc(r->pool, sizeof(ngx_http_python_rputs_chain_list_t));
        chain->out = ngx_alloc_chain_link(r->pool);
        chain->last = &chain->out;
    }else {
        chain = ctx->rputs_chain;
        (*chain->last)->next = ngx_alloc_chain_link(r->pool);
        chain->last = &(*chain->last)->next;
    }

    b = ngx_calloc_buf(r->pool);
    (*chain->last)->buf = b;
    (*chain->last)->next = NULL;

    u_str = ngx_pstrdup(r->pool, &ns);
    //u_str[ns.len] = '\0';
    (*chain->last)->buf->pos = u_str;
    (*chain->last)->buf->last = u_str + ns.len;
    (*chain->last)->buf->memory = 1;

    *b->last++ = '\n';

    ctx->rputs_chain = chain;
    ngx_http_set_ctx(r, ctx, ngx_http_python_module);

    if (r->headers_out.content_length_n == -1){
        r->headers_out.content_length_n += ns.len + 1 + 1;
    }else {
        r->headers_out.content_length_n += ns.len + 1;
    }

    return Py_BuildValue("i", r->headers_out.content_length_n);
}

static PyObject *
ngx_exit(PyObject *self, PyObject *args)
{
    PyObject *exit_code = 0;
    
    ngx_http_python_ctx_t *ctx;
    ngx_http_request_t *r;

    r = ngx_python_request;
    ctx = ngx_http_get_module_ctx(r, ngx_http_python_module);
    
    if (!PyArg_ParseTuple(args, "l", &exit_code)){
        return NULL;
    }

    ctx->exit_code = (ngx_int_t )(exit_code);

    return Py_BuildValue("l", exit_code);
}

static PyMethodDef NgxMethods[]={
    {"echo", ngx_echo, METH_VARARGS, "ngx.echo"},
    {"print", ngx_print, METH_VARARGS, "ngx.print"},
    {"exit", ngx_exit, METH_VARARGS, "ngx.exit"},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef NgxModule = {
    PyModuleDef_HEAD_INIT, "ngx", NULL, -1, NgxMethods,
    NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_ngx(void)
{
    PyObject    *m;
    m = PyModule_Create(&NgxModule);
    if ( !m ) {
        return NULL;
    }

    PyModule_AddIntConstant(m, "OK", NGX_OK);
    PyModule_AddIntConstant(m, "ERROR", NGX_ERROR);
    PyModule_AddIntConstant(m, "AGAIN", NGX_AGAIN);
    PyModule_AddIntConstant(m, "BUSY", NGX_BUSY);
    PyModule_AddIntConstant(m, "DONE", NGX_DONE);
    PyModule_AddIntConstant(m, "DECLINED", NGX_DECLINED);
    PyModule_AddIntConstant(m, "ABORT", NGX_ABORT);

    PyModule_AddIntConstant(m, "LOG_STDERR", NGX_LOG_STDERR);
    PyModule_AddIntConstant(m, "LOG_EMERG", NGX_LOG_EMERG);
    PyModule_AddIntConstant(m, "LOG_ALERT", NGX_LOG_ALERT);
    PyModule_AddIntConstant(m, "LOG_CRIT", NGX_LOG_CRIT);
    PyModule_AddIntConstant(m, "LOG_ERR", NGX_LOG_ERR);
    PyModule_AddIntConstant(m, "LOG_WARN", NGX_LOG_WARN);
    PyModule_AddIntConstant(m, "LOG_NOTICE", NGX_LOG_NOTICE);
    PyModule_AddIntConstant(m, "LOG_INFO", NGX_LOG_INFO);
    PyModule_AddIntConstant(m, "LOG_DEBUG", NGX_LOG_DEBUG);

    return m;
}

void initNgx()
{

    PyImport_AppendInittab("ngx", &PyInit_ngx);

}