//returns length of given string

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef struct char_array{
	int* pointer;
	size_t size;
}dynamic_array;

int main(int argc, char **argv){
	clock_t start = clock();
	dynamic_array input;
	input.pointer = malloc(1 * sizeof(int));
	input.size = sizeof(int);
	int c;
	for (int i = 0; (c = fgetc(stdin)) != EOF; i++){
		if ((int)(input.size < (int)((sizeof(int)*(i+1))))){
			int *input_tmp = realloc(input.pointer, input.size+sizeof(int));
			input.size += sizeof(int);
			if (input_tmp == NULL){
				exit(1);
			}
			else{
				input.pointer = input_tmp;
			}
		}
		input.pointer[i] = c;
		//printf("%c", input.pointer[i]);
	}
	printf("%d\n", (int)(input.size/sizeof(int))-1);
	free(input.pointer);
	clock_t end = clock();
	printf("%lf\n", (double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}
