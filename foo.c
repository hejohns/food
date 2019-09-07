#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
int counter = argv[0][0];
int forkreturn = fork();
if (forkreturn < 0)
{
	return 1;
}
else  if (forkreturn == 0)
{
	for(;counter<120;counter++)
	{
	sleep(1);
	}
	printf("%d: %d\n", getpid(), counter);
	return 0;
}
else
{
	return 0;
}
}
