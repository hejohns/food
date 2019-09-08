#!bin/bash
#required to force script cd
foodprefix=$(dirname "$(readlink -f "$0")")
source configuration
#wget and unpack nginx
wget http://nginx.org/download/$nginx_version
gzip -d $nginx_version
tar -xf ${nginx_version%.gz}
mv ${nginx_version%.tar.gz} nginx
rm -rf ${nginx_version%.gz}
#create makefile
echo 'foo : foo.c
	gcc -o foo foo.c

clean : 
	rm foo
'> makefile
#make foo
make
#make nginx
cd $foodprefix/nginx
${foodprefix}/nginx/configure --prefix=${foodprefix}/nginx/local --without-http_rewrite_module --without-http_gzip_module
make 
make install
#modify default nginx files
cd $foodprefix
rm $foodprefix/nginx/local/conf/nginx.conf
cp nginx.default.conf $foodprefix/nginx/local/conf/nginx.conf
#install foo.service unit
echo '[Unit]
Description=My first attempt at a systemd service

[Service]
Type=forking
ExecStart='$foodprefix'/foo '$foodprefix'
Nice=0

[Install]
WantedBy=multi-user.target' > food.service

mv food.service ${systemd_unit_directory}food.service

