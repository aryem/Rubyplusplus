#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER
#include"token_lexeme.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<set>

#define SPC char(32)
#define TAB char(9)
#define NL char(10)
#define PLUS_OP '+'
#define MINUS_OP '-'
#define MUL_OP '*'
#define DIV_OP '/'
#define NE '='


namespace lexical_analyzer {
	static int index = 0;
	static std::string code;
	static std::set<std::string> table;
	static std::vector<token_lexeme> words;
	static std::map<std::string, std::string> key_words;


	void error();
	void analyze_code();
	void define_keywords();
	void write_lex_files();

	 bool is_alphabet(char chr);
	 bool is_numeric(char chr);
	 bool is_alpha_numeric(char chr);
	 
	 token_lexeme is_keyword();
	 token_lexeme is_comment();
	 token_lexeme is_identifier();
	 token_lexeme is_punctuation();
	 token_lexeme is_literal_const();
	 token_lexeme is_numeric_const();
	 token_lexeme is_arithmetic_op();
	 token_lexeme is_relational_op();
	 
	 std::string get_file(std::string file_name);
	 
	 std::vector<token_lexeme> run_lex(std::string code_file);
	 
}

#endif