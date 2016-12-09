/**
 *    Copyright(c) 2016 rryqszq4
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

    ns.len = PyBytes_GET_SIZE(s);
    ns.data = (u_char *)PyBytes_AS_STRING(s);

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

    return Py_BuildValue("i", r->headers_out.content_length_n);;
}

static PyMethodDef NgxMethods[]={
    {"echo", ngx_echo, METH_VARARGS, "ngx.echo"},
    {NULL, NULL, 0, NULL}
};

void initNgx()
{
    Py_InitModule("ngx",NgxMethods);
}