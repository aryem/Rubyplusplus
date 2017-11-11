#include "token_lexeme.h"



token_lexeme::token_lexeme()
{
}

bool token_lexeme::is_valid()
{
	return (this->token == "" && this->lexeme == "") ? false : true;
}

void token_lexeme::print()
{
	if (this->is_valid())std::cout << "Token:" << this->token << "\t" << "lexeme:" << ((this->lexeme == "") ? "NULL" : this->lexeme + "\n");
	else std::cout << "Invalid";
}

std::ofstream & token_lexeme::operator<<(std::ofstream & stream)
{
	stream << this->lexeme << "\n";
	return stream;
}


token_lexeme::~token_lexeme()
{
}
