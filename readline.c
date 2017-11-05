int readline(char input_string[]){
	
	int c, i;
	extern const int maxline;
	
	for(i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; ++i){
		input_string[i] = c;
	}
	
	if (c == '\n'){
		input_string[i++] = c;
	}
	
	input_string[i] = '\0';
	
	return i;
}