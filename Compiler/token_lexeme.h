#ifndef TOKEN_LEXEME
#define TOKEN_LEXEME

#include<string>
#include<iostream>
#include<fstream>
class token_lexeme{
public:
	std::string token, lexeme;
	token_lexeme();
	bool is_valid();
	void print();
	std::ofstream& operator<<(std::ofstream& stream);
	~token_lexeme();
};

#endif // !TOKEN_LEXEME
