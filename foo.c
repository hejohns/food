//launches nginx and stays alive

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>

#define parent_endgame \
waitpid(forkreturn1, NULL, WNOHANG);\
waitpid(forkreturn2, NULL, WNOHANG);\
waitpid(forkreturn3, NULL, WNOHANG);\
return 0;

typedef struct charArray{
	char* pointer;
	size_t size;
}darray;

void initializeDarray(darray x);

void initializeDarray(darray x){
	x.pointer = malloc(1);
	x.size = 1;
}

void reallocDarray(darray x, int newSize);

void reallocDarray(darray x, int newSize){
	char* tmp = realloc(x.pointer, newSize);
	x.size = newSize;
	if (tmp == NULL){
		printf("ERROR\n");
		exit(1);
	}
	else{
		x.pointer = tmp;
	}
}

int main(int argc, char **argv)
{
	//set path to directory
	char foodprefix[PATH_MAX];
	for(int i=0; argv[1][i] != 0; i++)
	{
		foodprefix[i]=argv[1][i];
	}
	printf("%s\n", foodprefix);
	//fork first child
	int forkreturn1 = fork();
	if (forkreturn1 < 0)
	{
		return 1;
	}
	else  if (forkreturn1 == 0)
	{
		//exec nginx
		strcat(foodprefix, "nginx/local/sbin/nginx");
		char *path_to_sbin_nginx = foodprefix;
		printf("%s#%s\n", path_to_sbin_nginx, path_to_sbin_nginx);
		execl(path_to_sbin_nginx, path_to_sbin_nginx, (char *)0);
	}
	else
	{
		//fork second child
		int forkreturn2 = fork();
		if (forkreturn2 < 0)
		{
			printf("ef");
			return 1;
		}
		else if (forkreturn2 == 0)
		{
			printf("ef");
			//read server.jar min/max ram
			darray minecraft_server_ram_min;
			darray minecraft_server_ram_max;
			initializeDarray(minecraft_server_ram_min);
			initializeDarray(minecraft_server_ram_max);
			for(int i=0; argv[3][i] != (char) 0; i++)
			{
				minecraft_server_ram_min.pointer[i] = argv[2][i];
				reallocDarray(minecraft_server_ram_min, minecraft_server_ram_min.size + 1);
			}
			for(int i=0; argv[3][i] != (char) 0; i++)
			{
				minecraft_server_ram_max.pointer[i] = argv[3][i];
				reallocDarray(minecraft_server_ram_max, minecraft_server_ram_max.size + 1);
			}
			reallocDarray(minecraft_server_ram_min, minecraft_server_ram_min.size + 4);
			reallocDarray(minecraft_server_ram_max, minecraft_server_ram_max.size + 4);
			darray Xms;
			darray Xmx;
			initializeDarray(Xms);
			initializeDarray(Xmx);
			reallocDarray(Xms, 4+minecraft_server_ram_min.size);
			reallocDarray(Xmx, 4+minecraft_server_ram_max.size);
			Xms.pointer = "-Xms";
			Xmx.pointer = "-Xmx";
			strcat(Xms.pointer, minecraft_server_ram_min.pointer);
			strcat(Xmx.pointer, minecraft_server_ram_max.pointer);
			//exec server.jar
			strcat(foodprefix, "/minecraft/server.jar");
			char *path_to_minecraft_server_jar = foodprefix;
			printf("FU");
			execl("/usr/bin/java", "/usr/bin/java", Xms.pointer, Xmx.pointer, "-jar", path_to_minecraft_server_jar, "nogui", (char *)0);
		}
		else
		{
			//fork third child
			printf("ef");
			int forkreturn3 = fork();
			if (forkreturn3 < 0)
			{
				return 1;
			}
			else if (forkreturn3 == 0)
			{
				//keep parent in waiting state
				eternal_sleep:
				sleep(60);
				goto eternal_sleep;
				return 1;
			}
			else
			{
				parent_endgame
			}
		}
	}
return 1;	
}
