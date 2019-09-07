#!bin/bash
#make foo
make clean
make
foodprefix=$(dirname "$(readlink -f "$0")")
cd $foodprefix/nginx
${foodprefix}/nginx/configure --prefix=${foodprefix}/nginx/local --without-http_rewrite_module --without-http_gzip_module
#make nginx
cd $foodprefix/nginx
make clean
cd $foodprefix/nginx
${foodprefix}/nginx/configure --prefix=${foodprefix}/nginx/local --without-http_rewrite_module --without-http_gzip_module
cd $foodprefix/nginx
make 
cd $foodprefix/nginx
make install
