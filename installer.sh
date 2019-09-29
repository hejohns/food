#!bin/bash
#required to force script cd
foodprefix=$(dirname "$(readlink -f "$0")")
source configuration
cd $foodprefix
#create makefile
echo 'foo : foo.c
	gcc -o foo foo.c
string_length : string_length.c
	gcc -o string_length string_length.c

clean : 
	rm foo string_length
'> makefile
#make foo
make
#git clone nodejs
git clone https://github.com/nodejs/node.git
mv node nodejs
#install foo.service unit
echo '[Unit]
Description=minecraft server (+nodejs?)

[Service]
Type=forking
ExecStart='$foodprefix'/foo '$foodprefix' '$minecraft_server_ram_min' '$minecraft_server_ram_max'
Nice=0

[Install]
WantedBy=multi-user.target' > food.service

mv food.service ${systemd_unit_directory}food.service

#wget minecraft server
cd $foodprefix
mkdir minecraft
cd $foodprefix/minecraft
wget $minecraft_server_jar_uri
java -Xms$minecraft_server_ram_min -Xmx$minecraft_server_ram_max -jar server.jar nogui
echo 'eula=true'>eula.txt
cp eula.txt ../eula.txt
echo 'broadcast-rcon-to-ops=true
view-distance=10
max-build-height=256
server-ip=
level-seed=
rcon.port=25575
gamemode=survival
server-port=25565
allow-nether=true
enable-command-block=false
enable-rcon=false
enable-query=false
op-permission-level=4
prevent-proxy-connections=false
generator-settings=
resource-pack=
level-name=world
rcon.password=
player-idle-timeout=0
motd=food is running
query.port=25565
force-gamemode=false
hardcore=false
white-list=false
broadcast-console-to-ops=true
pvp=true
spawn-npcs=true
generate-structures=true
spawn-animals=true
snooper-enabled=true
difficulty=hard
function-permission-level=2
network-compression-threshold=256
level-type=amplified
spawn-monsters=true
max-tick-time=60000
enforce-whitelist=false
use-native-transport=true
max-players=64
resource-pack-sha1=
spawn-protection=16
online-mode=false
allow-flight=false
max-world-size=29999984'>server.properties

#create default nodejs files
cd $foodprefix
mv index.js $foodprefix/nodejs/index.js
#Building nodejs takes a LONG time
#make nodejs
cd $foodprefix/nodejs
${foodprefix}/nodejs/configure
make -j4
