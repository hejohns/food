//returns length of given string

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct char_array{
	int* pointer;
	size_t size;
}string;

int main(){
	string nginx_input;
	nginx_input.pointer = malloc(1 * sizeof(int));
	nginx_input.size = sizeof(int);
	int c;
	for (int i = 0; (c = fgetc(stdin)) != EOF; i++){
		if ((int)(nginx_input.size < (int)((sizeof(int)*(i+1))))){
			int *nginx_input_tmp = realloc(nginx_input.pointer, nginx_input.size+sizeof(int));
			nginx_input.size += sizeof(int);
			if (nginx_input_tmp == NULL){
				exit(1);
			}
			else{
				nginx_input.pointer = nginx_input_tmp;
			}
		}
		nginx_input.pointer[i] = c;
		//printf("%c", nginx_input.pointer[i]);
	}
	printf("%d", (int)(nginx_input.size/sizeof(int))-1);
	free(nginx_input.pointer);
	return 0;
}
