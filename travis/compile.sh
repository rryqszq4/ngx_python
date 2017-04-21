#!/bin/bash
# Copyright (c) 2016-2017, rryqszq4
mkdir build
cd build
mkdir python
mkdir nginx
echo "python download ..."
wget https://www.python.org/ftp/python/${PYTHON_SRC_VERSION}/Python-${PYTHON_SRC_VERSION}.tgz
echo "python download ... done"
tar -xf Python-${PYTHON_SRC_VERSION}.tgz

PYTHON_SRC=`pwd`'/Python-'${PYTHON_SRC_VERSION}
PYTHON_SRC_ROOT=`pwd`'/python'
cd ${PYTHON_SRC}

echo "python install ..."
./configure --prefix=${PYTHON_SRC_ROOT}
make
make install
echo "python install ... done"

cd ..
echo "nginx download ..."
wget http://nginx.org/download/nginx-${NGINX_SRC_VERSION}.tar.gz
echo "nginx download ... done"
tar xf nginx-${NGINX_SRC_VERSION}.tar.gz

NGINX_SRC=`pwd`'/nginx-'${NGINX_SRC_VERSION}
NGINX_SRC_ROOT=`pwd`'/nginx'
cd ${NGINX_SRC}

export PYTHON_INC=${PYTHON_SRC_ROOT}'include/python2.7'
export PYTHON_BIN=${PYTHON_SRC_ROOT}'/bin'

ls ${PYTHON_SRC_ROOT}

echo "nginx install ..."
./configure --prefix=${NGINX_SRC_ROOT} \
--add-module=../../../ngx_python
make
make install
if [ $? -eq 0 ];then
    echo "nginx install ... done"
    echo "ngx_python compile success."
else 
    echo "ngx_python compile failed."
    exit 1
fi
#echo "nginx install ... done"
#cd ../..
#echo "ngx_python compile success."