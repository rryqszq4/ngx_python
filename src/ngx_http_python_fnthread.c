/**
 *    Copyright(c) 2016-2019 rryqszq4
 */

#include "ngx_http_python_module.h"
#include "ngx_http_python_fnthread.h"
#include "ngx_http_python_util.h"

#include <Python.h>

/*
char *run_str = str_replace((char *)plcf->content_inline_code->code.string, "\t", "");
printf("%s\n", run_str);
//char *run_str1 = str_replace(run_str, "    ", "");
//printf("%s\n", run_str1);
char *run_str2 = str_replace(run_str, "\n", "\n    ");
printf("%s\n", run_str2);

PyRun_SimpleString(run_str);

PyObject *o1 = PyUnicode_FromString("__main__");
PyObject *m1 = PyImport_Import(o1);
PyObject *func1 = PyObject_GetAttrString(m1, "test");
if (!PyCallable_Check(func1)){
    printf("call_func: expected a callable\n");
}else {
    PyObject_CallFunction(func1,"");
}
*/

void 
ngx_http_python_fnthread_content_inline_routine(ngx_http_request_t *r)
{
	ngx_http_python_ctx_t 		*ctx;
	ngx_http_python_loc_conf_t 	*plcf;
	ngx_str_t 					inline_code;
	char *tmp_str, *tmp_str2;


	plcf = ngx_http_get_module_loc_conf(r, ngx_http_python_module);
	ctx = ngx_http_get_module_ctx(r, ngx_http_python_module);

	ctx->phase_status = NGX_OK;
	ngx_python_request = r;

	tmp_str = str_replace((char *)plcf->content_inline_code->code.string, "\t", "");
	tmp_str2 = str_replace(tmp_str, "\n", "\n    ");

	inline_code.data = (u_char *)malloc(sizeof("def ngx_content_():")-1 + ngx_strlen(tmp_str2) + 32);

	inline_code.len = ngx_sprintf(inline_code.data, "def ngx_content_%V():\n%*s", 
                                        &(plcf->content_inline_code->code_id), 
                                        ngx_strlen(tmp_str2),
                                        tmp_str2
                                    ) - inline_code.data;

	if (!plcf->enabled_content_inline_compile) {
		PyRun_SimpleString((char *)inline_code.data);
		plcf->enabled_content_inline_compile = 1;
		printf("%s, %d\n", inline_code.data, (int)strlen((char *)inline_code.data));
		free(inline_code.data);
	}

	ngx_http_python_fnthread_create(r, "ngx_content");
}

void 
ngx_http_python_fnthread_create(ngx_http_request_t *r, char *func_prefix)
{
	ngx_http_python_loc_conf_t *plcf;
	ngx_str_t func_name;
	PyObject *fn_name, *module_name, *fn, *result;

	plcf = ngx_http_get_module_loc_conf(r, ngx_http_python_module);

	char *f_name = malloc(strlen(func_prefix)+1 + 32);
	if (strcmp(func_prefix, "ngx_content") == 0) {
        //func_name.len = ngx_sprintf((u_char *)f_name, "%s_%V", func_prefix, &(plcf->content_inline_code->code_id)) - func_name.data;
        strncat(f_name, func_prefix, strlen(func_prefix));
        strncat(f_name, "_", 1);
        strncat(f_name, (char *)plcf->content_inline_code->code_id.data, 32);
    }else {
        func_name.len = 0;
    }

    printf("%s, %d\n", (char *)f_name, (int)strlen((char *)f_name));

    fn_name = PyUnicode_FromString("__main__");
	module_name = PyImport_Import(fn_name);
	Py_DECREF(fn_name);
	fn = PyObject_GetAttrString(module_name, (char *)f_name);
	
	if (!PyCallable_Check(fn)){
	    printf("call_func: expected a callable\n");
	    return ;
	}

	result = PyObject_CallFunction(fn,"");

	Py_DECREF(fn);
	Py_DECREF(result);
	free(f_name);
}

void 
ngx_http_python_fnthread_resume(ngx_http_request_t *r)
{

}

void 
ngx_http_python_fnthread_exit(ngx_http_request_t *r)
{

}