Requires:
	g++
	java runtime environment 
	make
	bash
	python2.7
	git

Installation:
	git clone <https://> OR wget <.zip>
	cd ./food
	vim configuration #set rcon password BEFORE install, otherwise manually edit rcon.password in server.properties file.
	sudo bash ./installer.sh
	sudo systemctl daemon-reload
	sudo systemctl enable food

Usage:
	systemctl status food
	systemctl restart food
