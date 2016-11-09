/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#include "ngx_http_python_directive.h"
#include "ngx_http_python_module.h"

char *
ngx_http_python_content_phase(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_python_main_conf_t *pmcf;
    ngx_http_python_loc_conf_t *plcf;
    ngx_str_t *value;
    ngx_http_python_code_t *code;

    if (cmd->post == NULL) {
        return NGX_CONF_ERROR;
    }

    pmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_python_module);
    plcf = conf;

    if (plcf->content_handler != NULL){
        return "is duplicated";
    }

    value = cf->args->elts;

    code = ngx_http_python_code_from_file(cf->pool, &value[1]);
    if (code == NGX_CONF_UNSET_PTR){
        return NGX_CONF_ERROR;
    }

    plcf->content_code = code;
    plcf->content_handler = cmd->post;
    pmcf->enabled_content_handler = 1;

    return NGX_CONF_OK;
}

char *
ngx_http_python_content_inline_phase(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_python_main_conf_t *pmcf;
    ngx_http_python_loc_conf_t *plcf;
    ngx_str_t *value;
    ngx_http_python_code_t *code;

    if (cmd->post == NULL) {
        return NGX_CONF_ERROR;
    }

    pmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_php_module);
    plcf = conf;

    if (plcf->content_handler != NULL){
        return "is duplicated";
    }

    value = cf->args->elts;

    code = ngx_http_python_code_from_string(cf->pool, &value[1]);
    if (code == NGX_CONF_UNSET_PTR){
        return NGX_CONF_ERROR;
    }

    plcf->content_inline_code = code;
    plcf->content_handler = cmd->post;
    pmcf->enabled_content_handler = 1;

    return NGX_CONF_OK;
}


