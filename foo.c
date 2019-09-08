#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>

#define parent_endgame \
waitpid(forkreturn1, NULL, WNOHANG);\
waitpid(forkreturn2, NULL, WNOHANG);\
waitpid(forkreturn3, NULL, WNOHANG);\
return 0;

int main(int argc, char **argv)
{
	//set path to directory
	char foodprefix[PATH_MAX];
	for(int i=0; argv[1][i] != (char) 0;i++)
	{
		foodprefix[i]=argv[1][i];
	}
	//fork first child
	int forkreturn1 = fork();
	if (forkreturn1 < 0)
	{
		return 1;
	}
	else  if (forkreturn1 == 0)
	{
		//exec nginx
		strcat(foodprefix, "/nginx/local/sbin/nginx");
		char *path_to_sbin_nginx = foodprefix;
		execl(path_to_sbin_nginx, path_to_sbin_nginx, (char *)0);
	}
	else
	{
		//fork second child
		int forkreturn2 = fork();
		if (forkreturn2 < 0)
		{
			return 1;
		}
		else if (forkreturn2 == 0)
		{
			//keep parent in waiting state
eternal_sleep:
			sleep(60);
goto eternal_sleep;
			return 1;
		}
		else
		{
			int forkreturn3 = fork();
			if (forkreturn3 < 0)
			{
				return 1;
			}
			else if (forkreturn3 == 0)
			{
				//useful child
				return 0;
			}
			else
			{
				parent_endgame
			}
		}
	}
	
}
