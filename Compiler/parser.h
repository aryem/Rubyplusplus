#ifndef PARSER_H
#define PARSER_H

#include<vector>
#include"lexical_analyzer.h"
#include"token_lexeme.h"



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
	void local_declaration();
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
	void simple_declaration();
	void output_statement();
	void input_statement();
	void return_statement();
	void return_choice();
	void conditional_statement();
	void boolean_expression_prime();
	void code_segment();
	void optional_condition();
	void optional_else();
	void optional_elsif();

	void print_function(std::string func_name);

}


#endif // !PARSER_H