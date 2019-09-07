foo : foo.c
	gcc -o foo foo.c

clean : 
	rm foo
