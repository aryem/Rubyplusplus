#pragma once
#include<ctime>
#include<iostream>
#include<unordered_map>
#include"lexical_analyzer.h"
#include "parser.h"
#include"translator.h"
#include"virtual_machine.h"
int main(int argc,char* argv[]) {



	const clock_t begin_time = clock();
	
	std::vector<token_lexeme> words =lexical_analyzer::run_lex("code.cm");
	parser::run_parser(words);
	
	/*translator::start_translator(words);
	 std::cout << "do tranlation";
	virtual_machine::data_segment = translator::data_segment;
	virtual_machine::_symbol_table = translator::_symbol_table;
	virtual_machine::intermediate_code = translator::intermediate_code;
	virtual_machine::op_codes = translator::op_codes;
	virtual_machine::run_vm();*/

	std::cout <<"\n" << float(clock() - begin_time) / CLOCKS_PER_SEC;
	system("pause");

	return 0;

}