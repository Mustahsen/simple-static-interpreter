#include <stdio.h>
#include <stdbool.h>

const int pchar		=	82;
const int plimit 	=	1024;
const int maxline 	=	1024;

#include "readline.c"
#include "comment.c"
#include "math_interpreter.c"

int main()
{
	extern const int pchar;
	extern const int plimit;
	extern const int maxline;
	double parameters[plimit];
	
	char	line[maxline];
	char	comment_string[maxline];
	int len_line = 0, len_comment = 0;
	bool error;
	
	for(int i = 0; i < plimit; ++i)
	{
		parameters[i] = 0.0;
	}
	error = 0;
	
	printf("Simple Static Interpreter(SSI) Version 1.0\n");
	printf("Press Ctrl+C to Exit\n");
	printf("SSI> ");
	
	while((len_line = readline(line)) > 0 && !error)
	{
		
		int index = 0;
		while (index < len_line){
			
			if (line[index] == ' ') ++index;	// Space, move forward
			
			else if (line[index] == ';' || line[index] == '(')// ; or (, comment has been found
			{
				len_comment = comment(line, comment_string, &index);
			}
			else if (line[index] == pchar || line[index] >= '0' && line[index] <= '9')	//Parameter has found
			{
				math_interpreter(parameters, pchar, plimit, line, &index);
			}
			else ++index;
		}
		
		if (len_comment > 0) printf("Comment: %s\n", comment_string);
		
		printf("SSI> ");
	}
	
	return 0;
}



