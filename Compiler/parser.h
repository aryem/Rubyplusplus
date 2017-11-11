#ifndef PARSER_H
#define PARSER_H

#include<vector>
#include"token_lexeme.h"

/* not the right way to declare ??*/


namespace parser {
	extern std::vector<token_lexeme> words;
	extern std::string lookahead;
	extern int space_count;
	extern int index;
	void error();
	void run_parser(std::vector<token_lexeme> pr_words);
	void program();
	void match(std::string token);
	void function_definition();
	void parameter_list();
	void data_type();
	void array_type();
	void additional_parameters();
	void compound_statement();
	void statement();
	void variable_declaration();
	void id_statement();
	void id_statement_type();
	void function_call();
	void argument_list();
	void additional_argument();
	void assignment_statement();
	void expression();
	void expression_prime();
	void term();
	void term_prime();
	void factor();
	void loop();
	void boolean_expression();
	
	void print_function(std::string func_name);

}


#endif // !PARSER_H