#include "three_address_code.h"



three_address_code::three_address_code()
{
	this->op_code = this->arg_1 = this->arg_2 =this->result = "";
}

three_address_code::three_address_code(std::string op_code, std::string arg_1, std::string arg_2, std::string result)
{
	this->op_code = op_code;
	this->arg_1 = arg_1;
	this->arg_2 = arg_2;
	this->result = result;
}

std::string three_address_code::to_string()
{
	std::string _op_code = this->op_code == "" ? "null" : this->op_code;
	std::string _arg_1 = this->arg_1 == "" ? "null" : this->arg_1;
	std::string _arg_2 = this->arg_2 == "" ? "null" : this->arg_2;
	std::string _result = this->result == "" ? "null" : this->result;
	std::string str = _op_code + "\t" + _arg_1 + "\t" + _arg_2 + "\t" + _result;
	return str;
}


three_address_code::~three_address_code()
{
}
