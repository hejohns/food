#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	//set path to directory
	char foodprefix[PATH_MAX];
	for(int i=0; argv[1][i] != (char) 0;i++)
	{
		foodprefix[i]=argv[1][i];
	}
	//start nginx as child
	int forkreturn = fork();
	if (forkreturn < 0)
	{
		return 1;
	}
	else  if (forkreturn == 0)
	{
		strcat(foodprefix, "/nginx/local/sbin/nginx");
		char *path_to_sbin_nginx = foodprefix;
		printf("%s\n", path_to_sbin_nginx);
		execl(path_to_sbin_nginx, path_to_sbin_nginx, (char *)0);
	}
	else
	{
		wait(NULL);
		return 0;
	}
	
}
