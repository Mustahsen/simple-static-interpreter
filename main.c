#include <stdio.h>

#include "readline.c"

const int pchar		=	82;
const int plimit 	=	1024;
const int maxline 	=	1024;

int main(){
	
	extern const int plimit;
	extern const int maxline;
	
	double 	parameters[plimit];
	char	line[maxline];
	
	for(int i = 0; i < plimit; ++i){
		parameters[i] = 0.0;
	}
	
	printf("Simple Static Interpreter(SSI) Version 1.0\n");
	printf("Press Ctrl+C to Exit\n");
	printf("SSI> ");
	
	while(readline(line) > 0){
		
		printf("\t%s", line);
		
		printf("SSI> ");
	}
	
	return 0;
}



