#ifndef VIRTUAL_MACHINE_H	
#define VIRTUAL_MACHINE_H

#include<vector>
#include<unordered_map>
#include"three_address_code.h"
#include"symbol_table.h"
namespace virtual_machine {

	extern std::vector<std::string> data_segment;
	extern std::unordered_map<std::string, std::string> op_codes;
	extern std::vector<three_address_code> intermediate_code;
	extern symbol_table _symbol_table;
	extern int line_number;


	void run_vm();


}


#endif // !VIRTUAL_MACHINE_H

