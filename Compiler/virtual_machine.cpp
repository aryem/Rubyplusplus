#include "virtual_machine.h"

std::vector<std::string> virtual_machine::data_segment;
std::vector<three_address_code> virtual_machine::intermediate_code;
std::unordered_map<std::string,std::string> virtual_machine::op_codes;
symbol_table virtual_machine::_symbol_table;
int virtual_machine::line_number = 0;


void virtual_machine::replace_address(std::string address,std::string new_address, int pc) 
{

	for (int i = pc; i < intermediate_code.size(); ++i) {

		intermediate_code[i].replace(address, new_address);
	}
	
}
void virtual_machine::error(std::string message) {

	std::cout <<std::endl<< message<<std::endl;
	system("pause");
	exit(0);
}
bool virtual_machine::is_valid(int ds_index) {

	if (data_segment[ds_index] == "$" || data_segment[ds_index] =="#")return false;
	
	return true;

}
void virtual_machine::run_vm()
{
	for (int pc = 0; pc < intermediate_code.size(); ++pc) {

		std::string op_code = intermediate_code[pc].op_code;

		if (op_code == op_codes.at("PRINT")) {

			int result = stoi(intermediate_code[pc].result);
				if (is_valid(result)) {
					std::cout << data_segment.at(result) << std::endl;
				}
				else {
					error("variable not intialized");
				}
			

		 }
		else if (op_code == op_codes.at("IFGT")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);
			
			if (!(is_valid(arg_1) && is_valid(arg_2))) error("variable not intialized");
			
			int val_1 = stoi(data_segment[arg_1]);
			int val_2 = stoi(data_segment[arg_2]);
			if (val_1 > val_2) {
				pc = result;
				--pc;
			}
		}
		else if (op_code == op_codes.at("IFLT")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);

			if (!(is_valid(arg_1) && is_valid(arg_2))) error("variable not intialized");

			int val_1 = stoi(data_segment[arg_1]);
			int val_2 = stoi(data_segment[arg_2]);
			if (val_1 < val_2) {
				pc = result;
				--pc;
			}
		}
		else if (op_code == op_codes.at("IFET")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);

			if (!(is_valid(arg_1) && is_valid(arg_2))) error("variable not intialized");

			int val_1 = stoi(data_segment[arg_1]);
			int val_2 = stoi(data_segment[arg_2]);
			if (val_1 == val_2) {
				pc = result;
				--pc;
			}

		}
		else if (op_code == op_codes.at("IFLE")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);

			if (!(is_valid(arg_1) && is_valid(arg_2))) error("variable not intialized");

			int val_1 = stoi(data_segment[arg_1]);
			int val_2 = stoi(data_segment[arg_2]);
			if (val_1 <= val_2) {
				pc = result;
				--pc;
			}

		}
		else if (op_code == op_codes.at("IFGE")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);

			if (!(is_valid(arg_1) && is_valid(arg_2))) error("variable not intialized");

			int val_1 = stoi(data_segment[arg_1]);
			int val_2 = stoi(data_segment[arg_2]);
			if (val_1 >= val_2) {
				pc = result;
				--pc;
			}
		}
		else if (op_code == op_codes.at("GET")) {

			int value; 
			std::cin >> value;

			int result = stoi(intermediate_code[pc].result);
	
			data_segment[result] = std::to_string(value);
		}
		else if (op_code == op_codes.at("GOTO")) {
			int result = stoi(intermediate_code[pc].result);
			pc = result;
			--pc;
		}
		else if (op_code == op_codes.at("=")) {

 			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			if(!is_valid(arg_1)) error("variable not intialized");

			data_segment[result] = data_segment[arg_1];
		}
		else if (op_code == op_codes.at("+")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);

			if (!(is_valid(arg_1) && is_valid(arg_2))) error("variable not intialized");
			
			int add = std::stoi(data_segment[arg_1]) + std::stoi(data_segment[arg_2]);
			data_segment[result] = std::to_string(add);
		}
		else if (op_code == op_codes.at("-")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);
			
			if (!(is_valid(arg_1) && is_valid(arg_2))) error("variable not intialized");

			int add = std::stoi(data_segment[arg_1]) - std::stoi(data_segment[arg_2]);
			data_segment[result] = std::to_string(add);
		}
		else if (op_code == op_codes.at("*")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);
			
			if (!(is_valid(arg_1) && is_valid(arg_2))) error("variable not intialized");

			int add = std::stoi(data_segment[arg_1]) * std::stoi(data_segment[arg_2]);
			data_segment[result] = std::to_string(add);
		}
		else if (op_code == op_codes.at("/")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);
			
			if (!(is_valid(arg_1) && is_valid(arg_2))) error("variable not intialized");

			if (stoi(data_segment[arg_2]) == 0) {
				std::cout << "divide by zero";
				system("pause");
				std::exit(0);
			}
			int add = std::stoi(data_segment[arg_1]) / std::stoi(data_segment[arg_2]);
		
			data_segment[result] = std::to_string(add);
		}
		else if (op_code == op_codes.at("A_ASG")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);
			int arr_address = arg_1 + std::stoi(data_segment[arg_2]);
			data_segment[result] = std::to_string(arr_address);
			replace_address(std::to_string(result), std::to_string(arr_address), pc);
		}
		else if (op_code == op_codes.at("A_ASG_V")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);
			int arr_address = arg_1 + std::stoi(data_segment[arg_2]);
				
		}


	}

}
