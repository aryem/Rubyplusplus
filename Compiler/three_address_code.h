#ifndef THREE_ADDRESS_CODE
#define THREE_ADDRESS_CODE
#include<iostream>
#include<string>
class three_address_code
{
public:
	std::string op_code;
	std::string arg_1;
	std::string arg_2;
	std::string result;
	three_address_code();
	three_address_code(std::string op_code, std::string arg_1,
						std::string arg_2, std::string result);
	std::string to_string();
	void replace(std::string address,std::string new_address);
	~three_address_code();
};


#endif // !THREE_ADDRESS_CODE
