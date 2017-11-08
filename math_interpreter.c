
#define case_terminate	0
#define case_target		10
#define case_equals		20
#define case_expression	100
#define case_term		200
#define case_factor		300









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
	extern const int plimit;
	
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
	
	int case_operation			= -1;

	int count_call_term 		= 0;
	int count_return_term 		= 0;

	int count_call_factor		= 0;
	int count_return_factor		= 0;

	double result 				= 0;
	double result_expression 	= 0;
	double result_term 			= 0;
	double result_factor 		= 0;

	int expression_operation	= 0;
	int term_operation 			= 0;
	int target_parameter;
	int negate;
	bool assign;
	
	i = 0;
	
	case_operation = case_target;
	while (i < token_limit)
	{
		printf("%d\n", case_operation);
		switch(case_operation){
		
			case case_terminate:
			
				count_call_term = count_call_factor = 0;
				if (assign)
				{
					if (target_parameter >= 0 && target_parameter <= plimit)
					{
						parameters[target_parameter] = result;
						printf("Result: %c%d <-- %10.5f\n",parameter_char, target_parameter, result);
					}
					else
					{
						printf("Parameter is not in limit (You can choose between 0 - 1023)!\n");
						return;
					}
				}
				else
				{
					printf("Result: %10.5f\n", result);
				}
				
				if (tokens[i].type != type_eof)
				{
					case_operation = case_target;
					break;
				}
				else
				{
					i = token_limit;
					break;
				}
		
			case case_target:
				assign = 0;
				if (tokens[i].type == type_parameter)
				{
					target_parameter = tokens[i].value;
					++i;
					case_operation = case_equals;
				}
				else if (tokens[i].type == type_value)
				{
					case_operation = case_expression;
				}
				else
				{
					case_operation = case_terminate;
				}
				
				break;
		
			case case_equals:
				
				if (tokens[i].type == type_equals)
				{
					++i;
					assign = 1;
					case_operation = case_expression;
				}
				else if (tokens[i].type != type_value && tokens[i].type != type_parameter)
				{
					case_operation = case_expression;
				}
				else
				{
					case_operation = case_terminate;
				}
				
				break;
				
			case case_expression:
			
				if (count_return_term == 0)
				{
					case_operation = case_term;
					++count_call_term;
				}
				
				else if (count_return_term == 1)	
				{
					result_expression = result_term;
					
					if (tokens[i].type == type_plus || tokens[i].type == type_minus)
					{
						expression_operation = tokens[i].type;
						++i;
						case_operation = case_term;
						++count_call_term;
					}
					
					else
					{
						result = result_expression;
						case_operation = case_terminate;
					}
				}
		
				else if (count_return_term >= 2)
				{
					if (expression_operation == type_plus)
					{
						result_expression += result_term;
					}
					else 
					{
						result_expression -= result_term;
					}
					
					if (tokens[i].type == type_plus || tokens[i].type == type_minus)
					{
						expression_operation = tokens[i].type;
						++i;
						case_operation = case_term;
						++count_call_term;
					}
					
					else
					{
						result = result_expression;
						case_operation = case_terminate;
					}
					
				}
				
				break;
			
			case case_term:
			
				if (count_return_factor == 0)
				{
					case_operation = case_factor;
					++count_call_factor;
				}
				
				else if (count_return_factor == 1)	
				{
					result_term = result_factor;
					
					if (tokens[i].type == type_multiply || tokens[i].type == type_divide)
					{
						term_operation = tokens[i].type;
						++i;
						case_operation = case_factor;
						++count_call_factor;
					}
					
					else
					{
						case_operation = case_expression;
						count_call_factor = count_return_factor = 0;
						++count_return_term;
					}
				}
				
				else if (count_return_term >= 2)
				{
					if (expression_operation == type_multiply)
					{
						result_term *= result_factor;
					}
					else 
					{
						result_term /= result_factor;
					}
					
					if (tokens[i].type == type_multiply || tokens[i].type == type_divide)
					{
						term_operation = tokens[i].type;
						++i;
						case_operation = case_factor;
						++count_call_factor;
					}
					
					else
					{
						case_operation = case_expression;
						count_call_factor = count_return_factor = 0;
						++count_return_term;
					}
					
				}
				
				break;
			
			case case_factor:
				
				negate = 0;
				
				while(tokens[i].type == type_minus)
				{
					++negate;
					++i;
				}
				
				if (tokens[i].type == type_value)
				{
					result_factor = tokens[i].value;
					++i;
					++count_return_factor;
					case_operation = case_term;
				}
				else if (tokens[i].type == type_parameter)
				{
					if (tokens[i].value >= 0 && tokens[i].value <= plimit)
					{
						result_factor = parameters[(int)tokens[i].value];
						++i;
						++count_return_factor;
						case_operation = case_term;
					}
					else
					{
						printf("Syntax Error!\n");
						return;
					}
				}
			if (negate / 2)
			{
				result_factor *= -1;
			}
			
			break;
		}
	}
	
	
	
	return;
}