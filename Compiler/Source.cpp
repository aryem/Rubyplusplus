#pragma once
#include<ctime>
#include<iostream>
#include"lexical_analyzer.h"
#include "parser.h"

int main(int argc,char* argv[]) {

	const clock_t begin_time = clock();
	
	std::vector<token_lexeme> words =lexical_analyzer::run_lex("code.cm");
	parser::run_parser(words);
	std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC;
	system("pause");

	return 0;

}