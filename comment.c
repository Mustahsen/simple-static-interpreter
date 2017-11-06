int comment(char input_string[], char comment_string[], int *start_index){
	
	int i, len = 0;
	extern const int maxline;
	
	if (input_string[*start_index] == ';')
	{
		++(*start_index);
		for(i = (*start_index); i < maxline - 1 && input_string[i] != '\0' && input_string[i] != '\n'; ++i)
		{
			comment_string[i - (*start_index)] = input_string[i];
		}			
		comment_string[i] = '\0';
		
		len = i - (*start_index);
		*start_index = i;
	}
	
	else if (input_string[*start_index] == '(')
	{
		++(*start_index);
		for(i = (*start_index); i < maxline - 1 && input_string[i] != ')'; ++i)	
		{
			comment_string[i - (*start_index)] = input_string[i];
		}
		if (input_string[i] == ')')
		{
			comment_string[i] = '\0';
			len = i - (*start_index);
			*start_index = i;
		}
		else
		{
			len = -1;	// comment finisher character hasn't been found error
		}
	}
	
	return len;
}