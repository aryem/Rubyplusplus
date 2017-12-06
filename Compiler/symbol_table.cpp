#include "symbol_table.h"



symbol_table::symbol_table()
{
	
}



bool symbol_table::add_symbol(std::string symbol, std::string type,int address)
{
	if (address_table.find(symbol) != address_table.end()) {
		return false;
	}

	address_table[symbol] = std::to_string(address);
	type_table[symbol] = type;
	return true;
}



bool symbol_table::is_symbol(std::string symbol)
{
	if (this->address_table.find(symbol) != this->address_table.end()) {
		return true;
	}
	return false;
}

std::string symbol_table::get_address(std::string symbol)
{
	if (address_table.find(symbol) != address_table.end()) {
		return address_table.at(symbol);
	}
	return "";
}

std::unordered_map<std::string, std::string> symbol_table::get_address_table()
{
	return address_table;
}

std::unordered_map<std::string, std::string> symbol_table::get_type_table()
{
	return type_table;
}


symbol_table::~symbol_table()
{
}
