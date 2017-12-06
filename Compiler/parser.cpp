#include"token_lexeme.h"
#include "parser.h"


std::vector<token_lexeme> parser::words;
std::string parser::lookahead = "";
int parser::space_count = 0;
int parser::index = 0;


void parser::error()
{
	if (index == words.size()) {
		std::cout << "Program ended\n";
		std::system("pause");
	}

	std::cout << "error()";
	std::exit(0);
}

void parser::run_parser(std::vector<token_lexeme> pr_words)
{
	index = space_count = 0;
	words = pr_words;
	lookahead = words.at(index).token;
	program();
}

void parser::program()
{
	++space_count;
	 print_function("program");
	if (lookahead == "DEF") {
		function_definition();
		program();
	}
	else; // no code in file
	--space_count;
}

void parser::match(std::string token)
{
	++space_count;
	if (lookahead == token) {

		if (words.at(index).lexeme == "") {
			print_function(token);
		}else 
		{
			print_function(words.at(index).lexeme);
		}
			++index;

		if (index < words.size()) {
			lookahead = words.at(index).token;
		}
		else {
			error();
		}
	}
	--space_count;
}

void parser::function_definition()
{
	++space_count;
	print_function("function def");
	if (lookahead == "DEF"){
		match("DEF");

			if (lookahead == "ID") {
				match("ID");

				if (lookahead == "(") {
					match("(");
					parameter_list();

					if (lookahead == ")") {
						match(")");

						compound_statement();
					}
				}
			}
		}
	--space_count;
}

void parser::parameter_list()
{
	++space_count;
	print_function("parameter list");
	data_type();
	array_type();
	if (lookahead == "ID") {
		match("ID");
		additional_parameters();
	}
	else;
	--space_count;
}

void parser::data_type()
{

	if (lookahead == "INT") {
		match("INT");
	}
	else if (lookahead == "CHAR") {
		match("CHAR");
	}

}

void parser::array_type()
{

	if (lookahead == "[") {
		match("[");

		if (lookahead == "]") {
			match("]");
		}
	}
	else; // null

}

void parser::additional_parameters()
{
	++space_count;

	print_function("addition parameters");
	
	if (lookahead == ",") {
		match(",");
		parameter_list();
	}
	else;

	--space_count;

}

void parser::compound_statement()
{
	++space_count;
	print_function("Compound Statement");
		
	match("{");
	local_declaration();
	match("}");
	
	--space_count;
}

void parser::local_declaration()
{
	++space_count;
	print_function("Local Declaration");
	if (lookahead == "INT" || lookahead == "CHAR" || lookahead == "WHILE"
		|| lookahead == "RETURN" || lookahead == "PRINT" || lookahead == "GET"
		|| lookahead == "IF" || lookahead == "ID") {
		statement();
		local_declaration();
	}
	else;
	--space_count;
}

void parser::statement()
{
	++space_count;
	print_function("Statement");
	if (lookahead == "INT" || lookahead == "CHAR") {
		variable_declaration();
	}
	else if (lookahead == "ID") {
		id_statement();
	}
	else if (lookahead == "WHILE") {
			loop();
	}
	else if (lookahead == "IF") {
		conditional_statement();
	}
	else if (lookahead == "RETURN") {
		return_statement();
	}
	else if (lookahead == "PRINT") {
		output_statement();
	}
	else if (lookahead == "GET") {
		input_statement();
	}
	--space_count;
}

void parser::variable_declaration()
{
	++space_count;
	print_function("Variable Declaration");
	data_type();
	if (lookahead == "ID") {
		match("ID");
		simple_declaration();
	}
	else if (lookahead == "[") {
		match("[");
		match("NC");
		match("]");
		match("ID");
	}

	--space_count;
	
}

void parser::id_statement()
{
	++space_count;
	print_function("Id Statement");
	if (lookahead == "ID") {
		match("ID");
		id_statement_type();
	}
	--space_count;
}

void parser::id_statement_type()
{
	++space_count;
	print_function("Id Statement Type");
	if (lookahead == "=") {
		assignment_statement();
	}
	else if (lookahead == "(") {
		function_call();
	}
	else if (lookahead == "[") {
		//array_assignment_statement();
	}
	--space_count;
}

void parser::function_call()
{
	++space_count;
	print_function("Function Call");
	match("(");
	argument_list();
	match(")");
	--space_count;
}

void parser::argument_list()
{
	++space_count;

	print_function("Argument List");
	if (lookahead == "ID") {
		match("ID");
		additional_argument();
	}
	else; // No argument
	--space_count;
}

void parser::additional_argument()
{
	++space_count;
	print_function("Additional Argument");
	if (lookahead == ",") {
		match(",");
		argument_list();
	}
	else;

	--space_count;
}

void parser::assignment_statement()
{
	++space_count;
	print_function("Assignment_statement");
	match("=");
	expression();

	--space_count;
}

void parser::expression()
{
	++space_count;
	print_function("Expression");
	term();
	expression_prime();
	--space_count;
}

void parser::expression_prime()
{
	++space_count;
	print_function("Expression Prime");
	if (lookahead == "+") {
		match("+");
		term();
		expression_prime();
	}
	else if (lookahead == "-") {
		match("-");
		term();
		expression_prime();
	}
	else;

	--space_count;
}

void parser::term()
{
	++space_count;
	print_function("Term");
	factor();
	term_prime();
	--space_count;
}

void parser::term_prime()
{
	// Both conditions are same ??
	++space_count;
	print_function("Term prime");
	if (lookahead == "*") {
		match("*");
		factor();
		term_prime();
	}
	else if (lookahead == "/") {
		match("/");
		factor();
		term_prime();
	}
	else;
	--space_count;
}

void parser::factor()
{
	++space_count;
	
	print_function("Factor");
	
	if (lookahead == "ID") {
		match("ID");
	}
	else if (lookahead == "NC") {
		match("NC");
	}
	else if (lookahead == "(") {
		match("(");
		expression();
		match(")");
	}

	--space_count;
}

void parser::loop()
{
	++space_count;
	print_function("Loop");
	
	match("WHILE");
	boolean_expression();
	code_segment();
	--space_count;
}

void parser::boolean_expression()
{
	++space_count;
	print_function("Boolean Expression");
	expression();
	boolean_expression_prime();
	--space_count;
}

void parser::simple_declaration()
{
	++space_count;
	print_function("Simple Declaration");
	if (lookahead == ",") {
		match(",");
		match("ID");
		simple_declaration();
	}
	else;
	--space_count;
}

void parser::output_statement()
{
	++space_count;
	print_function("Output Statement");
	match("PRINT");
	match("(");
	expression();
	match(")");
	--space_count;
}

void parser::input_statement()
{
	++space_count;
	print_function("Input Statement");
	match("GET");
	match("(");
	match("ID");
	match(")");
	--space_count;
}

void parser::return_statement()
{
	++space_count;
	print_function("Return Statement");
	match("RETURN");
	return_choice();
	--space_count;
}

void parser::return_choice()
{
	++space_count;
	print_function("Return Choice");
	if (lookahead == "ID" || lookahead == "LC" || lookahead == "(") {
		expression();
	}
	else; // simple return
	--space_count;
}

void parser::conditional_statement()
{
	++space_count;
	print_function("Conditional Statement");
	match("IF");
	boolean_expression();
	code_segment();
	optional_condition();
	--space_count;
}

void parser::boolean_expression_prime()
{
	++space_count;
	print_function("Boolean Expression Prime");
	if (lookahead == "RO") {
		match("RO");
		expression();
	}
	else;
	--space_count;
}

void parser::code_segment()
{
	++space_count;
	print_function("Code Segment");
	if (lookahead == "{") {
		compound_statement();
	}
	else if (lookahead == "INT" || lookahead == "CHAR" || lookahead == "WHILE"
		|| lookahead == "RETURN" || lookahead == "PRINT" || lookahead == "GET"
		|| lookahead == "IF" || lookahead == "ID") {
		statement();
	}
	else; // If without body
	--space_count;
}

void parser::optional_condition()
{
	++space_count;
	print_function("Optional Condition");
	if (lookahead == "ELSE") {
		optional_else();
	}
	else if (lookahead == "ELSIF") {
		optional_elsif();
	}
	else;
	--space_count;
}

void parser::optional_else()
{
	++space_count;
	print_function("Optional Else");
	match("ELSE");
	code_segment();
	--space_count;
}

void parser::optional_elsif()
{
	++space_count;
	print_function("Optional Elsif");
	match("ELSIF");
	boolean_expression();
	code_segment();
	--space_count;
}





void parser::print_function(std::string func_name)
{
	std::string spaces = "    ";
	std::string bars = "____";

	for (int i = 0; i < space_count; ++i) {
		std::cout << spaces;
	}
	std::cout << "|";
	std::cout << bars;
	std::cout << func_name;
	std::cout << "\n";
}

