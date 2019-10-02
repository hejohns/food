**Description**:

foo daemon just for fun. Started as messing around with systemd services. Combined with messing around with forks/exec. Turned into minecraft server installer. Hoping to add rcon capability tied in with nodejs. Current goal: write the rcon api based on https://github.com/Tiiffi/mcrcon in order to learn sockets. After, replace nodejs with a simple c http server?
	
**Requires**:

	g++ //might not need after removing nginx
	java runtime environment //for minecraft server.jar
	make //for my files and building nodejs
	bash //installer script is in bash
	python2.7 //for building nodejs
	git //for downloading/updating? nodejs
	
**Installation**:

	git clone <https://> OR wget <.zip>
	cd ./food
	vim configuration //set rcon password BEFORE install, otherwise manually edit rcon.password in server.properties file.
	sudo bash ./installer.sh
	sudo systemctl daemon-reload
	sudo systemctl enable food

**Usage**:

	systemctl status food
	systemctl start food
