/**
 *    Copyright(c) 2016-2017 rryqszq4
 *
 *
 */

#include "ngx_http_python_module.h"
#include "ngx_http_python_code.h"

ngx_http_python_code_t *
ngx_http_python_code_from_file(ngx_pool_t *pool, ngx_str_t *code_file_path)
{
    ngx_http_python_code_t *code;
    size_t len;
    u_char *p;

    code = ngx_pcalloc(pool, sizeof(* code));

    if (code == NULL) {
        return NGX_CONF_UNSET_PTR;
    }

    len = ngx_strlen((char *)code_file_path->data);
    if (len == 0){
        return NGX_CONF_UNSET_PTR;
    }else if (code_file_path->data[0] == '/' || code_file_path->data[0] == '$'){
        code->code.file = ngx_pcalloc(pool, len + 1);
        if (code->code.file == NULL){
            return NGX_CONF_UNSET_PTR;
        }
        ngx_cpystrn((u_char *)code->code.file, (u_char *)code_file_path->data, code_file_path->len + 1);    
    }else {
        code->code.file = ngx_pcalloc(pool, ngx_cycle->conf_prefix.len + len + 1);
        if (code->code.file == NULL){
            return NGX_CONF_UNSET_PTR;
        }
        p = ngx_cpystrn((u_char *)code->code.file, (u_char *)ngx_cycle->conf_prefix.data, ngx_cycle->conf_prefix.len + 1);
        ngx_cpystrn(p, (u_char *)code_file_path->data, code_file_path->len + 1);
    }
    code->code_type = NGX_HTTP_PYTHON_CODE_TYPE_FILE;
    return code;
}


ngx_http_python_code_t *
ngx_http_python_code_from_string(ngx_pool_t *pool, ngx_str_t *code_str)
{
    ngx_http_python_code_t *code;
    size_t len;

    code = ngx_pcalloc(pool, sizeof(*code));
    if (code == NULL){
        return NGX_CONF_UNSET_PTR;
    }

    len = ngx_strlen(code_str->data);
    code->code.string = ngx_pcalloc(pool, len + 1);
    if (code->code.string == NULL){
        return NGX_CONF_UNSET_PTR;
    }
    ngx_cpystrn((u_char *)code->code.string, code_str->data, len + 1);
    code->code_type = NGX_HTTP_PYTHON_CODE_TYPE_STRING;
    return code;
}






