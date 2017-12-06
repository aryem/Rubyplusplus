#include "temp.h"



temp::temp()
{
	int_count = 0;
}

std::string temp::new_int_temp()
{
	std::string symbol = "t" + std::to_string(int_count);
	int_count++;
	return symbol;
}

std::string temp::new_char_temp()
{
	std::string symbol = "c" + std::to_string(char_count);
	char_count++;


	return symbol;
}


temp::~temp()
{
}
