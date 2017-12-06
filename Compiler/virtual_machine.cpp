#include "virtual_machine.h"

std::vector<std::string> virtual_machine::data_segment;
std::vector<three_address_code> virtual_machine::intermediate_code;
std::unordered_map<std::string,std::string> virtual_machine::op_codes;
symbol_table virtual_machine::_symbol_table;
int virtual_machine::line_number = 0;



void virtual_machine::run_vm()
{
	for (int pc = 0; pc < intermediate_code.size(); ++pc) {

		std::string op_code = intermediate_code[pc].op_code;

		if (op_code == op_codes.at("PRINT")) {

			int result = stoi(intermediate_code[pc].result);
			std::cout << data_segment.at(result) << std::endl;

		 }
		else if (op_code == op_codes.at("IFGT")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);
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
			if (data_segment[arg_1] > data_segment[arg_2]) {
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
			data_segment[result] = data_segment[arg_1];
		}
		else if (op_code == op_codes.at("+")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);
			int add = std::stoi(data_segment[arg_1]) + std::stoi(data_segment[arg_2]);
			data_segment[result] = std::to_string(add);
		}
		else if (op_code == op_codes.at("-")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);
			int add = std::stoi(data_segment[arg_1]) - std::stoi(data_segment[arg_2]);
			data_segment[result] = std::to_string(add);
		}
		else if (op_code == op_codes.at("*")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);
			int add = std::stoi(data_segment[arg_1]) * std::stoi(data_segment[arg_2]);
			data_segment[result] = std::to_string(add);
		}
		else if (op_code == op_codes.at("/")) {
			int result = stoi(intermediate_code[pc].result);
			int arg_1 = stoi(intermediate_code[pc].arg_1);
			int arg_2 = stoi(intermediate_code[pc].arg_2);
			int add = std::stoi(data_segment[arg_1]) / std::stoi(data_segment[arg_2]);
			data_segment[result] = std::to_string(add);
		}


	}

}
