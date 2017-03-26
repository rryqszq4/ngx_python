/**
 *    Copyright(c) 2016-2017 rryqszq4
 *
 *
 */

#include "ngx_http_python_directive.h"
#include "ngx_http_python_module.h"

char *
ngx_http_python_rewrite_phase(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
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

    if (plcf->rewrite_handler != NULL){
        return "is duplicated";
    }

    value = cf->args->elts;

    code = ngx_http_python_code_from_file(cf->pool, &value[1]);
    if (code == NGX_CONF_UNSET_PTR){
        return NGX_CONF_ERROR;
    }

    plcf->rewrite_file_code = code;
    plcf->rewrite_handler = cmd->post;
    pmcf->enabled_rewrite_handler = 1;

    return NGX_CONF_OK;
}

char *
ngx_http_python_rewrite_inline_phase(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
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

    if (plcf->rewrite_handler != NULL){
        return "is duplicated";
    }

    value = cf->args->elts;

    code = ngx_http_python_code_from_string(cf->pool, &value[1]);
    if (code == NGX_CONF_UNSET_PTR){
        return NGX_CONF_ERROR;
    }

    plcf->rewrite_inline_code = code;
    plcf->rewrite_handler = cmd->post;
    pmcf->enabled_rewrite_handler = 1;

    return NGX_CONF_OK;
}

char *
ngx_http_python_access_phase(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
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

    if (plcf->access_handler != NULL){
        return "is duplicated";
    }

    value = cf->args->elts;

    code = ngx_http_python_code_from_file(cf->pool, &value[1]);
    if (code == NGX_CONF_UNSET_PTR){
        return NGX_CONF_ERROR;
    }

    plcf->access_file_code = code;
    plcf->access_handler = cmd->post;
    pmcf->enabled_access_handler = 1;

    return NGX_CONF_OK;
}

char *
ngx_http_python_access_inline_phase(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
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

    if (plcf->access_handler != NULL){
        return "is duplicated";
    }

    value = cf->args->elts;

    code = ngx_http_python_code_from_string(cf->pool, &value[1]);
    if (code == NGX_CONF_UNSET_PTR){
        return NGX_CONF_ERROR;
    }

    plcf->access_inline_code = code;
    plcf->access_handler = cmd->post;
    pmcf->enabled_access_handler = 1;

    return NGX_CONF_OK;
}

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

    plcf->content_file_code = code;
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

    pmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_python_module);
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

char *
ngx_http_python_log_phase(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
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

    if (plcf->log_handler != NULL){
        return "is duplicated";
    }

    value = cf->args->elts;

    code = ngx_http_python_code_from_file(cf->pool, &value[1]);
    if (code == NGX_CONF_UNSET_PTR){
        return NGX_CONF_ERROR;
    }

    plcf->log_file_code = code;
    plcf->log_handler = cmd->post;
    pmcf->enabled_log_handler = 1;

    return NGX_CONF_OK;
}

char *
ngx_http_python_log_inline_phase(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
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

    if (plcf->log_handler != NULL){
        return "is duplicated";
    }

    value = cf->args->elts;

    code = ngx_http_python_code_from_string(cf->pool, &value[1]);
    if (code == NGX_CONF_UNSET_PTR){
        return NGX_CONF_ERROR;
    }

    plcf->log_inline_code = code;
    plcf->log_handler = cmd->post;
    pmcf->enabled_log_handler = 1;

    return NGX_CONF_OK;
}

