#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include<unordered_map>
#include<string>
class symbol_table
{
public:
	std::unordered_map<std::string, std::string> type_table;
	std::unordered_map<std::string, std::string> address_table;
	

	symbol_table();
	bool add_symbol(std::string symbol,std::string type,int address);
	bool is_symbol(std::string symbol);
	std::string get_address(std::string symbol);
	std::unordered_map<std::string, std::string> get_address_table();
	std::unordered_map<std::string, std::string> get_type_table();
	~symbol_table();
};

#endif // !SYMBOL_TABLE_H