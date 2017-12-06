#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include<vector>
#include<fstream>
#include<stdexcept>
#include<unordered_map>
#include<regex>
#include"lexical_analyzer.h"
#include"token_lexeme.h"
#include"symbol_table.h"
#include"temp.h"
#include"three_address_code.h"
#include"virtual_machine.h"
namespace translator {
	extern std::vector<token_lexeme> words;
	extern symbol_table _symbol_table;
	extern std::string lookahead;
	extern int index;
	extern temp* Temp;
	extern int line_number;
	extern int data_segment_add;
	extern std::vector<three_address_code> intermediate_code;
	extern std::vector<std::string> data_segment;
	extern std::unordered_map<std::string, std::string> op_codes;
	extern std::string file_machine_code;
	extern std::string file_symbol_table;
	extern std::string file_address_table;

	void start_translator(std::vector<token_lexeme> _words);
	void intialize_op_code();

	bool is_number(std::string x);
	void program();
	
	std::string get_temp(std::string type);
	void intialize_symbol(std::string type, std::string symbol);
	void intialize_array(std::string type, std::string symbol, int size);
	std::string intialize_immediate_value(std::string value,std::string type);
	std::string get_data_segment_value(std::string value);

	void function_definition();
	void parameter_list();
	std::string data_type();
	std::string array_type();
	void additional_parameters();

	bool valid_symbol(std::string symbol);
	void conditional_statement();
	void optional_condition();
	void compound_statement();
	void local_declaration();
	void statement();
	void simple_declaration(std::string& type, std::string& str_emit);
	void variable_declaration();
	void variable_declaration_type(std::string& type, std::string& str_emit);
	void match(std::string token);
	void input_statement();
	void error(std::string message);
	void output_statement();
	std::string expression();
	std::string term();
	std::string factor();
	std::string array_index();
	std::string term_prime(std::string input);
	std::string expression_prime(std::string input);
	void id_statement();
	void id_statement_type(std::string str_id);
	void assignment_statement(std::string str_id);
	void return_statement();
	void return_choice();
	void loop();
	void boolean_expression();
	void code_segment();



	void write_symbol_table();
	void write_intermediate_code();
	void back_patch(int s, int e);
	void emit(std::string op_code,std::string result);
	void emit(std::string op_code, std::string arg_1, std::string result);
	void emit(std::string op_code, std::string arg_1, std::string arg_2
		, std::string result);
	void emitC(std::string op_code, std::string arg_1, std::string arg_2,
		int line_number);
	void emit(std::string op_code);
	
}



#endif 