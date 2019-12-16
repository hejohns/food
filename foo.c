#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct darray_{
    char* pointer;
    size_t size;
    void (*resize)(struct darray_*, int);
} darray;

void darrayResize(darray* x, int newSize);

void darrayInitialize(darray* x){
    x->pointer = malloc(1);
    x->size = 1;
    if (x->pointer == (char *)0)
    {
	fprintf(stderr, "darrayInitialize error on line %d\n", __LINE__);
	exit(1);
    }
    else
    {
	x->resize = &darrayResize;
    }
}

void darrayResize(darray* x, int newSize){
    char* tmp = realloc(x->pointer, newSize);
    x->size = newSize;
    if (tmp == NULL){
	fprintf(stderr, "darray.resize error on line %d\n", __LINE__);
	exit(1);
    }
    else{
	x->pointer = tmp;
    }
}

int main(int argc, char **argv)
{
    //set path to directory
    char foodprefix[PATH_MAX+4];
    strcpy(foodprefix, argv[1]);
    //fork first child
    //starts nodejs
    int forkreturn1 = fork();
    if (forkreturn1 < 0)
    {
	fprintf(stderr, "first fork failed on line %d\n", __LINE__);
	exit(1);
    }
    else  if (forkreturn1 == 0)
    {
	/* replace with nodejs
	    //exec nginx
	    strcat(foodprefix, "/nginx/local/sbin/nginx");
	    char *path_to_sbin_nginx = foodprefix;
	    PRINTF("$2: %s\n", path_to_sbin_nginx);
	    execl(path_to_sbin_nginx, path_to_sbin_nginx, (char *)0);
	 */
	return 0;
    }
    else
    {
	//fork second child
	//starts minecraft server.jar
	int forkreturn2 = fork();
	if (forkreturn2 < 0)
	{
	    fprintf(stderr, "second fork failed on line %d\n", __LINE__);
	    exit(1);
	}
	else if (forkreturn2 == 0)
	{
	    //read server.jar min/max ram
	    darray ramMin_, ramMax_;
	    darray* ramMin = &ramMin_;
	    darray* ramMax = &ramMax_;
	    darrayInitialize(ramMin);
	    darrayInitialize(ramMax);
	    //yes, it's generally a terrible idea to realloc every byte, but writing it this way is easier to read. 
	    //theres not enough of a performance decrease in this context to sacrifice readability
	    for(int i=0; argv[2][i] != (char) 0; i++)
	    {
		ramMin->pointer[i] = argv[2][i];
		ramMin->resize(ramMin, (int)ramMin->size + 1);
	    }
	    for(int i=0; argv[3][i] != (char) 0; i++)
	    {
		ramMax->pointer[i] = argv[3][i];
		ramMax->resize(ramMax, (int)ramMax->size + 1);
	    }
	    darray xms_, xmx_;
	    darray* xms = &xms_;
	    darray* xmx = &xmx_;
	    darrayInitialize(xms);
	    darrayInitialize(xmx);
	    xms->resize(xms, strlen("-Xms")+ramMin->size);
	    xmx->resize(xmx, strlen("-Xmx")+ramMax->size);
	    snprintf(xms->pointer, xms->size, "%s%s", "-Xms", ramMin->pointer);
	    snprintf(xmx->pointer, xmx->size, "%s%s", "-Xmx", ramMax->pointer);
	    free(ramMin->pointer);
	    free(ramMax->pointer);
	    //exec server.jar
	    char path_to_minecraft_server_jar[PATH_MAX+4];
	    strcpy(path_to_minecraft_server_jar, foodprefix);
	    strcat(path_to_minecraft_server_jar, "/minecraft/server.jar");
	    char foodprefix_minecraft[PATH_MAX+4];
	    strcpy(foodprefix_minecraft, argv[1]);
	    strcat(foodprefix_minecraft, "/minecraft");
	    foodprefix_minecraft[strlen(foodprefix_minecraft)] = '\0';
	    chdir(foodprefix_minecraft);
	    execl("/usr/bin/java", "/usr/bin/java", "-server", xms->pointer, xmx->pointer, "-jar", path_to_minecraft_server_jar, "nogui", (char *)0);
	}
	else
	{
	    //fork third child
	    //block parent with infinite loop, thus preventing orphaning and allowing systemd to track children
	    int forkreturn3 = fork();
	    if (forkreturn3 < 0)
	    {
		fprintf(stderr, "third fork failed on line %d\n", __LINE__);
		exit(1);
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
		//after all forks, this is original parent
		waitpid(forkreturn1, NULL, WNOHANG);
		waitpid(forkreturn2, NULL, WNOHANG);
		waitpid(forkreturn3, NULL, WNOHANG);
		return 0;
	    }
	}
    }
    return 1;	
}
