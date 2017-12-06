#ifndef TEMP_H
#define TEMP_H
#include<iostream>
#include<string>
class temp{
public:
	int int_count;
	int char_count;
	temp();
	std::string new_int_temp();
	std::string new_char_temp();
	~temp();
};

#endif // TEMP_H
