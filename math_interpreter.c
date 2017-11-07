struct token{
	int type;
	double value;
};

double value_interpreter(char parameter_char, char input_string[], int *start_index)
{
	int i = *start_index;
	if (input_string[i] == parameter_char)	//parameter found
	{
		++i;
		int val;
		for(val = 0; input_string[i] >= 48 && input_string[i] <= 57; ++i)
		{
			val = 10 * val + (input_string[i] - 48);
		}
		*start_index = i;
		return val;
	}
	else	// value found 
	{	
		double val, power;
		for(val = 0.0; input_string[i] >= 48 && input_string[i] <= 57; ++i)
		{
			val = 10.0 * val + (input_string[i] - 48);
		}
		if (input_string[i] == 46)	// '.'
			++i;
		for(power = 1.0; input_string[i] >= 48 && input_string[i] <= 57; ++i)
		{
			val = 10.0 * val + (input_string[i] - 48);
			power *= 10;
		}
		*start_index = i;
		return (val / power);
	}
} 

void math_interpreter(double parameters[], char parameter_char, int count_parameters, char input_string[], int *start_index)
{
	extern const int maxline;
	
	int type_eof			=	0;		// ASCII versions of the respected string will be used the denote the respected token type

	int type_value			=	868576; // "VAL"
	int type_parameter 		=	806582;	// "PAR"

	int type_equals			=	698185;	// "EQU"

	int type_plus			=	656868;	// "ADD"
	int type_minus			=	838566;	// "SUB"
	int type_multiply		=	778576;	// "MUL"
	int type_divide			=	687386;	// "DIV"

	int type_sinus			=	837378;	// "SIN"
	int type_cosinus		=	677983;	// "COS"
	
	int token_limit = 64;
	int token_index = 0;
	struct token tokens[token_limit];
	
	int i, ii, iii;
	
	for(i = 0; i < token_limit; ++i)
	{
		tokens[i].type 	= 0;
		tokens[i].value = 0.0;
	}
	
	i = *start_index;
	while(i < maxline - 1 && input_string[i] != '\0' && token_index < token_limit)
	{
		ii 	= i + 1;
		iii = ii + 1;
		
		if (input_string[i] == 32)
		{
			++i;	// Space, move forward
		}
		else if (input_string[i] >= 48 && input_string[i] <= 57)	//Value found
		{
			tokens[token_index].value = value_interpreter(parameter_char, input_string, &i);
			tokens[token_index].type  = type_value;
			++token_index;
		}
		else if (input_string[i] == parameter_char)	//Value found
		{
			tokens[token_index].value = value_interpreter(parameter_char, input_string, &i);
			tokens[token_index].type  = type_parameter;
			++token_index;
		}
		else if (input_string[i] == 61 || input_string[i] == 69 && input_string[ii] == 81 && input_string[iii] == 85)	// '=' or EQU found
		{
			tokens[token_index].type  = type_equals;
			if (input_string[i] == 61) ++i;
			else i+=3;
			++token_index;
		}
		else if (input_string[i] == 43 || input_string[i] == 65 && input_string[ii] == 68 && input_string[iii] == 68)	// '+' or ADD found
		{
			tokens[token_index].type  = type_plus;
			if (input_string[i] == 43) ++i;
			else i+=3;
			++token_index;
		}
		else if (input_string[i] == 45 || input_string[i] == 83 && input_string[ii] == 85 && input_string[iii] == 66)	// '-' or SUB found
		{
			tokens[token_index].type  = type_minus;
			if (input_string[i] == 45) ++i;
			else i+=3;
			++token_index;
		}
		else if (input_string[i] == 42 || input_string[i] == 77 && input_string[ii] == 85 && input_string[iii] == 76)	// '*' or MUL found
		{
			tokens[token_index].type  = type_multiply;
			if (input_string[i] == 42) ++i;
			else i+=3;
			++token_index;
		}
		else if (input_string[i] == 47 || input_string[i] == 68 && input_string[ii] == 73 && input_string[iii] == 86)	// '/' or DIV found
		{
			tokens[token_index].type  = type_divide;
			if (input_string[i] == 47) ++i;
			else i+=3;
			++token_index;
		}
		else
		{
			*start_index = i;
			break;
		}
	}
	
	for (i = 0; i < token_index; ++i){
		
		printf("Type: %d	Value:%.0f\n", tokens[i].type, tokens[i].value);
		
	}
	return;
}