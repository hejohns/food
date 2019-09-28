//launches nginx and stays alive

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>

#define PARENT_ENDGAME \
waitpid(forkreturn1, NULL, WNOHANG);\
waitpid(forkreturn2, NULL, WNOHANG);\
waitpid(forkreturn3, NULL, WNOHANG);\
return 0;

/*
 * DEBUG
 * 0-false
 * !0-true
 */

#define DEBUG 1 
#if DEBUG
#define PRINTF printf
#else
#define PRINTF //printf
#endif

typedef struct charArray{
	char* pointer;
	size_t size;
}darray;

void initializeDarray(darray* x);

void initializeDarray(darray* x){
	x->pointer = malloc(1);
	x->size = 1;
	if (x->pointer == (char *)0)
	{
		PRINTF("initializeDarray failed\n");
		exit(1);
	}
	else
	{
		PRINTF("initializeDarray success: %ld\n", (long int)x->pointer);
	}
}

void reallocDarray(darray* x, int newSize);

void reallocDarray(darray* x, int newSize){
	char* tmp = realloc(x->pointer, newSize);
	x->size = newSize;
	if (tmp == NULL){
		PRINTF("ERROR\n");
		exit(1);
	}
	else{
		PRINTF("reallocDarray success: %ld-%ld\n", (long int)x->pointer, x->size);
		x->pointer = tmp;
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
	PRINTF("$1: %s\n", foodprefix);
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
		PRINTF("$2: %s\n", path_to_sbin_nginx);
		execl(path_to_sbin_nginx, path_to_sbin_nginx, (char *)0);
	}
	else
	{
		//fork second child
		int forkreturn2 = fork();
		if (forkreturn2 < 0)
		{
			PRINTF("$3: fork2 failed\n");
			return 1;
		}
		else if (forkreturn2 == 0)
		{
			//read server.jar min/max ram
			darray minecraft_server_ram_min;
			darray minecraft_server_ram_max;
			darray* ramMin = &minecraft_server_ram_min;
			darray* ramMax = &minecraft_server_ram_max;
			initializeDarray(ramMin);
			initializeDarray(ramMax);
			//minecraft_server_ram_min.pointer[0] = 65;
			PRINTF("$10: %ld\n", (long int)ramMin->size);
			for(int i=0; argv[2][i] != (char) 0; i++)
			{
				ramMin->pointer[i] = argv[2][i];
				reallocDarray(ramMin, (int)ramMin->size + 1);
			}
			PRINTF("$11: %s\n", ramMin->pointer);
			for(int i=0; argv[3][i] != (char) 0; i++)
			{
				ramMax->pointer[i] = argv[3][i];
				reallocDarray(ramMax, (int)ramMax->size + 1);
			}
			PRINTF("$12: %s\n", ramMax->pointer);
			darray Xms_min;
			darray Xmx_max;
			darray* xms = &Xms_min;
			darray* xmx = &Xmx_max;
			initializeDarray(xms);
			initializeDarray(xmx);
			reallocDarray(xms, 5+ramMin->size);
			reallocDarray(xmx, 5+ramMax->size);
			strcat(xms->pointer, "-Xms");
			strcat(xmx->pointer, "-Xmx");
			PRINTF("$14: %ld-%ld\n", (long int)xms->pointer, xms->size);
			PRINTF("$15: %ld-%ld\n", (long int)xmx->pointer, xmx->size);
			PRINTF("$16: %ld-%ld\n", (long int)ramMin->pointer, ramMin->size);
			PRINTF("$17: %ld-%ld\n", (long int)ramMax->pointer, ramMax->size);
			snprintf(xms->pointer, xms->size, "%s%s", xms->pointer, ramMin->pointer);
			snprintf(xmx->pointer, xmx->size, "%s%s", xmx->pointer, ramMax->pointer);
			PRINTF("$18: %s\n", xms->pointer);
			PRINTF("$19: %s\n", xmx->pointer);
			//exec server.jar
			strcat(foodprefix, "minecraft/server.jar");
			char* path_to_minecraft_server_jar = foodprefix;
			PRINTF("$21: %s, %s, %s\n", xms->pointer, xmx->pointer, path_to_minecraft_server_jar);
			execl("/usr/bin/java", "/usr/bin/java", xms->pointer, xmx->pointer, "-jar", path_to_minecraft_server_jar, "nogui", (char *)0);
		}
		else
		{
			//fork third child
			int forkreturn3 = fork();
			if (forkreturn3 < 0)
			{
				printf("fork3 failed\n");
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
				PARENT_ENDGAME
			}
		}
	}
return 1;	
}
