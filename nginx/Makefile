
default:	build

clean:
	rm -rf Makefile objs

build:
	$(MAKE) -f objs/Makefile

install:
	$(MAKE) -f objs/Makefile install

modules:
	$(MAKE) -f objs/Makefile modules

upgrade:
	/home/hejohns/documentsNoSync/food/nginx/local/sbin/nginx -t

	kill -USR2 `cat /home/hejohns/documentsNoSync/food/nginx/local/logs/nginx.pid`
	sleep 1
	test -f /home/hejohns/documentsNoSync/food/nginx/local/logs/nginx.pid.oldbin

	kill -QUIT `cat /home/hejohns/documentsNoSync/food/nginx/local/logs/nginx.pid.oldbin`
