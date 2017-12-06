#include "translator.h"

std::vector<token_lexeme> translator::words;
std::vector<three_address_code> translator::intermediate_code;
std::vector<std::string> translator::data_segment;
std::unordered_map<std::string, std::string> translator::op_codes;
temp* translator::Temp = new temp();
symbol_table translator::_symbol_table;
std::string translator::lookahead = "";
int translator::index = 0;
int translator::data_segment_add = 0;
int translator::line_number = 0;
std::string translator::file_machine_code = "machine_code.txt";
std::string translator::file_symbol_table = "symbol_table.txt";

void translator::start_translator(std::vector<token_lexeme> _words)
{
	try {
	index = 0;
	words = _words;
	lookahead = words.at(index).token;
	intialize_op_code();
	program();
	write_intermediate_code();
	write_symbol_table();
	}
	catch(const std::invalid_argument& e){
		std::cout << e.what();
	}
}

void translator::intialize_op_code()
{
	op_codes["PRINT"] = "1";
	op_codes["GET"] = "2";
	op_codes["GOTO"] = "3";
	op_codes["IFGT"] = "4";
	op_codes["IFLT"] = "5";
	op_codes["="] = "6";
	op_codes["+"] = "7";
	op_codes["*"] = "8";
	op_codes["/"] = "9";
	op_codes["-"] = "10";
	op_codes["A_ASG"] = "11";
	op_codes["A_ASG_V"] = "12";
	op_codes["IFGE"] = "13";
	op_codes["IFLE"] = "14";
	op_codes["IFET"] = "15";
	
}

bool translator::is_number(std::string x) {
	std::regex e("^-?\\d+");
	if (std::regex_match(x, e)) return true;
	else return false;
}

void translator::program()
{
	if (lookahead == "DEF") {
		function_definition();
		program();
	}
	else {

	};
}

void translator::intialize_symbol(std::string type, std::string symbol)
{
	data_segment.push_back("$");
	bool isValid = _symbol_table.add_symbol(symbol, type, data_segment_add);
	if (!isValid) {
		error("symbol already defined");
	}
	data_segment_add++;

}

void translator::intialize_array(std::string type, std::string symbol, int size)
{
	int starting_address = data_segment_add;
	bool is_valid = _symbol_table.add_symbol(symbol, type, starting_address);
	if (!is_valid) {
		error("symbol already defined");
	}
	for (int i = 0; i < size-1; ++i) {
		data_segment.push_back("$");
		data_segment_add++;
	}
	data_segment.push_back("#");
	data_segment_add++;


}

std::string translator::get_temp(std::string type) {

	data_segment.push_back("$");
	std::string new_symbol;
	if (type == "INT") {
		new_symbol = Temp->new_int_temp();
	
	}
	else if (type == "CHAR") {

	}
	bool is_valid = _symbol_table.add_symbol(new_symbol, type, data_segment_add);
	if (!is_valid) {
		error("symbol already defined");
	}
	data_segment_add++;
	return new_symbol;
}

std::string translator::intialize_immediate_value(std::string value,std::string type)
{
	data_segment.push_back(value);
	std::string new_symbol;
	if (type == "INT") {
		new_symbol = Temp->new_int_temp();
	}
	else if(type == "CHAR"){
		// not handled
	}
	bool is_valid =  _symbol_table.add_symbol(new_symbol, type, data_segment_add);
	
	if (!is_valid) {
		error("symbol aleardy defined");
	}
	data_segment_add++;

	return new_symbol;
}

std::string translator::get_data_segment_value(std::string value)
{
	if (is_number(value)) {

		return intialize_immediate_value(value, "INT");
	}
	else if (value.find('$') != std::string::npos) {
		std::cout << "array type";
		std::string deli = "$";
		std::string str_id,str_arr_index;
		std::size_t pos = 0;
		pos = value.find(deli);
		str_id = value.substr(0, pos);
		value.erase(0, pos + deli.length());
		pos = value.find(deli);
		str_arr_index = value.substr(0, pos);
		std::cout << str_id << str_arr_index;
		 int address = stoi(_symbol_table.get_address(str_id));
		 int arr_index = address + stoi(str_arr_index);
		 std::string new_symbol = Temp->new_int_temp();
		 _symbol_table.add_symbol(new_symbol, "INT", arr_index);
		 
		 return new_symbol;
	}
	return value;
	
}

void translator::function_definition()
{
		if (lookahead == "DEF") {
			match("DEF");

			if (lookahead == "ID") {
				match("ID");
				std::string str_emit = "FUNC" +std::string("\t")+ words.at(index - 1).lexeme + std::string("\n");
				emit(str_emit);
	
				if (lookahead == "(") {
					match("(");
					parameter_list();

					if (lookahead == ")") {
						match(")");

						compound_statement();
					}
				}
			}
		}
	
}

void translator::parameter_list()
{
	std::string str_data_type = data_type();
	std::string str_array_type = array_type();
	if (lookahead == "ID") {
		match("ID");
		std::string str_emit;
		if (str_array_type == "") {
			str_emit = "S_ARG" + std::string("\t") + str_data_type + "\t" + words.at(index - 1).lexeme + std::string("\n");
		}
		else {
			str_emit = "A_ARG" + std::string("\t") + str_data_type + "\t" + words.at(index - 1).lexeme + std::string("\n");
		}
			emit(str_emit);
		additional_parameters();
	}
	else;  // No parameters
}

std::string translator::data_type()
{
	if (lookahead == "INT") {
		match("INT");
		return "INT";
	}
	else if (lookahead == "CHAR") {
		match("CHAR");
		return "CHAR";
	}
	return std::string();
}

std::string translator::array_type()
{
	if (lookahead == "[") {
		match("[");
		
		if (lookahead == "]") {
			match("]");

			return "[]";
		}
	}
	else {
		return "";
	}

}

std::string translator::term_prime(std::string input)
{
	if (lookahead == "*") {
		match("*");
		std::string str_factor = factor();
		std::string t = get_temp("INT");
		emit(t + "=" + str_factor + "*" + input);
		emit("*", get_data_segment_value(str_factor), get_data_segment_value(input), t);
		return term_prime(t);
	}
	else if (lookahead == "/") {
		match("/");
		std::string str_factor = factor();
		std::string t = get_temp("INT");
		emit(t + "=" + input + "/" + str_factor);
		emit("/", get_data_segment_value(input), get_data_segment_value(str_factor), t);

		return term_prime(t);
	}
	else;

	return input;
}

std::string translator::expression_prime(std::string input)
{
	if (lookahead == "+") {
		match("+");
		std::string str_term = term();
		std::string t = get_temp("INT");
		emit(t + "=" + str_term + "+" + input);
		emit("+", get_data_segment_value(str_term), get_data_segment_value(input), t);
		return expression_prime(t);
	}
	else if (lookahead == "-") {
		match("-");
		std::string str_term = term();
		std::string t = get_temp("INT");
		emit(t + "=" + str_term + "-" + input);
		emit("-", get_data_segment_value(str_term), get_data_segment_value(input), t);
		return expression_prime(t);
	}
	else;
	return input;
}

bool translator::valid_symbol(std::string symbol);
void translator::id_statement()
{
	if (lookahead == "ID") {
		match("ID");
		
		if (!_symbol_table.is_symbol(words.at(index - 1).lexeme)) {
			throw std::invalid_argument("variable not declared");
		}


		std::string str_id = words.at(index - 1).lexeme;
		std::string str_array_index = array_index();
		if (str_array_index != "") {
			if (is_number(str_array_index)) {
				std::string t_0 = intialize_immediate_value(str_array_index, "INT");
				std::string t_1 = get_temp("INT");
				emit("A_ASG", str_id, t_0, t_1);
				str_id = t_1;
			}
			else {
				std::string t_1 = get_temp("INT");
				emit("A_ASG", str_id, str_array_index, t_1);
				str_id = t_1;
			}
		}

		id_statement_type(str_id);
	}
}



void translator::id_statement_type(std::string str_id)
{
	if (lookahead == "=") {
		assignment_statement(str_id);
	}
	else {
		error("invalid id statement");
	}

}

void translator::assignment_statement(std::string str_id)
{
	match("=");
	std::string str_exp = expression();
	
	emit("=", get_data_segment_value(str_exp), get_data_segment_value(str_id));
}

void translator::return_statement()
{
	match("RETURN");
	return_choice();
}

void translator::return_choice()
{
	if (lookahead == "ID" || lookahead == "LC" || lookahead == "NC" || lookahead == "(") {
	std::string str_exp = expression();
	emit("RETURN",get_data_segment_value(str_exp));
	}
	else {
		emit("RETURN");
	}
}

void translator::loop()
{
	match("WHILE");
	boolean_expression();
	int if_line = line_number - 1;
	emit("GOTO");
	int goto_line_1 = line_number - 1;
	code_segment();
	emit("GOTO");
	int goto_line_2 = line_number - 1;
	back_patch(goto_line_2 , if_line);
	back_patch(goto_line_1, line_number);
}

void translator::boolean_expression()
{
	std::string str_exp_1 = expression();
	if (lookahead == "RO") {
		match("RO");
		std::string str_ro = words.at(index - 1).lexeme;
		std::string str_exp_2 = expression();
		emitC("IF" + str_ro, get_data_segment_value(str_exp_1),
			get_data_segment_value(str_exp_2), line_number);
		
	}
}

void translator::code_segment()
{
	if (lookahead == "{") {
		compound_statement();
	}else if (lookahead == "INT" || lookahead == "CHAR" || lookahead == "WHILE"
		|| lookahead == "RETURN" || lookahead == "PRINT" || lookahead == "GET"
		|| lookahead == "IF" || lookahead == "ID") {
		statement();
	}
	else;
}

void translator::additional_parameters()
{
	if (lookahead == ",") {
		match(",");
		parameter_list();
	}
	else;
}

void translator::match(std::string token)
{
	if (lookahead == token) {

		++index;
		if (index < words.size()) {
			lookahead = words.at(index).token;
		}
	}
		else {
			error("Invalid token");	
		}
	
}

void translator::input_statement()
{
	match("GET");
	match("(");
	match("ID");
	if (!_symbol_table.is_symbol(words.at(index - 1).lexeme)) {
		throw std::invalid_argument("variable not declared");
	}
	std::string str_id = words.at(index - 1).lexeme;
	std::string str_array_index = array_index();
	if (str_array_index != "") {
		if (is_number(str_array_index)) {
			std::string t_0 = intialize_immediate_value(str_array_index, "INT");
			std::string t_1 = get_temp("INT");
			emit("A_ASG", str_id, t_0, t_1);
			str_id = t_1;
		}
		else {
			std::string t_1 = get_temp("INT");
			emit("A_ASG", str_id, str_array_index, t_1);
			str_id = t_1;
		}

	}
	match(")");
	emit("GET", str_id);
}

void translator::conditional_statement()
{
	match("IF");
	boolean_expression();
	int if_line = line_number - 1;
	emit("GOTO");
	int goto_line = line_number - 1;
	code_segment();
	back_patch(goto_line, line_number);
	optional_condition();
}

void translator::optional_condition() {
	if (lookahead == "ELSE") {
		match("ELSE");
		code_segment();
	}
	else if (lookahead == "ELSIF") {
		match("ELSIF");
		boolean_expression();
		int if_line = line_number - 1;
		emit("GOTO");
		int goto_line = line_number - 1;
		code_segment();
		back_patch(goto_line, line_number);
		optional_condition();
	}
	else;

}

void translator::compound_statement()
{
	match("{");
	local_declaration();
	match("}");
}

void translator::local_declaration() {
	if (lookahead == "INT" || lookahead == "CHAR" || lookahead == "WHILE"
		|| lookahead == "RETURN" || lookahead == "PRINT" || lookahead == "GET"
		|| lookahead == "IF" || lookahead == "ID") {
		statement();
		local_declaration();
	}
	else;
}
void translator::statement()
{
	if (lookahead == "INT" || lookahead == "CHAR") {
		variable_declaration();
	}
	else if (lookahead == "ID") {
		id_statement();
	}
	else if (lookahead == "WHILE") {
			loop();
	}
	else if (lookahead == "IF") {
		conditional_statement();
	}
	else if (lookahead == "RETURN") {
		return_statement();
	}
	else if (lookahead == "PRINT") {
		output_statement();
	}
	else if (lookahead == "GET") {
			input_statement();
	}
	else {
		throw std::invalid_argument("invalid token");
	}

}
void translator::variable_declaration()
{
	std::string type = data_type();
	std::string str_emit = "";
	if (lookahead == "ID") {
		match("ID");
		std::string _symbol = words.at(index - 1).lexeme;
		str_emit += words.at(index - 1).lexeme;
		variable_declaration_type(type,str_emit);
	}

}
void translator::variable_declaration_type(std::string& type,std::string& str_emit) {
	
	if (lookahead == "[") {
		match("[");
		match("NC");
		std::string arr_size = words.at(index - 1).lexeme;
		match("]");
		if (type == "INT") {
			intialize_array("A_INT", str_emit, stoi(arr_size));
		}
		else if (type == "CHAR") {
			intialize_array("A_CHAR", str_emit, stoi(arr_size));
		}
	}
	else {

		intialize_symbol(type, str_emit);
		simple_declaration(type,str_emit);
	}
}
void translator::simple_declaration(std::string& type, std::string& str_emit) {
	if (lookahead == ",") {
		match(",");
		match("ID");
		std::string _symbol = words.at(index - 1).lexeme;
		intialize_symbol(type, _symbol);
		simple_declaration(type,str_emit);
	
	}

}

void translator::error(std::string message)
{

	if (index == words.size()) {
		write_intermediate_code();
		write_symbol_table();
		virtual_machine::data_segment = translator::data_segment;
		virtual_machine::_symbol_table = translator::_symbol_table;
		virtual_machine::intermediate_code = translator::intermediate_code;
		virtual_machine::op_codes = translator::op_codes;
		virtual_machine::run_vm();
		std::cout << "program ended\n";
		std::system("pause");

	}
	else {
		throw std::invalid_argument(message);
	}

}

void translator::output_statement()
{
	match("PRINT");
	match("(");
	std::string str_exp = expression();
	match(")");

	std::string symbol;
	if (is_number(str_exp)) {
	symbol	= intialize_immediate_value(str_exp, "INT");
	}
	else {
		symbol = str_exp;
	}
	emit("PRINT", symbol);
}

std::string translator::expression()
{
	std::string str_term = term();
	std::string str_exp_prime = expression_prime(str_term);
	return str_exp_prime;
}

std::string translator::term()
{
	std::string str_factor = factor();
	std::string str_term_prime = term_prime(str_factor);
	return str_term_prime;
}

std::string translator::factor()
{
	if (lookahead == "ID") {
		match("ID");
		if (!_symbol_table.is_symbol(words.at(index - 1).lexeme)) {
			throw std::invalid_argument("variable not declared");
		}
		std::string str_ID = words.at(index - 1).lexeme;
		std::string str_array_index = array_index();
		if (str_array_index != "") {
			if (is_number(str_array_index)) {
				std::string t_0 = intialize_immediate_value(str_array_index, "INT");
				std::string t_1 = get_temp("INT");
				emit("A_ASG", str_ID, t_0, t_1);
				str_ID = t_1;
			}
			else {
				std::string t_1 = get_temp("INT");
				emit("A_ASG", str_ID, str_array_index, t_1);
				str_ID = t_1;
			}

		}
		return str_ID;
	}
	else if (lookahead == "NC") {
		match("NC");
		return words.at(index - 1).lexeme;
	}
	else if (lookahead == "(") {
			match("(");
		std::string str_exp = expression();
		if (lookahead == ")") {
			match(")");
			return str_exp;
		}
	}
	else {
		throw std::invalid_argument("invalid expression");
	}


	
}
std::string translator::array_index() {

		 if (lookahead == "[") {
			match("[");
			std::string str_NC_ID;
			if (lookahead == "NC") {
				match("NC");
				std::string str_NC = words.at(index - 1).lexeme;
				if (lookahead == "]") {
					match("]");
					return  str_NC;
				}
			}
			else if (lookahead == "ID") {
				match("ID");
				if (!_symbol_table.is_symbol(words.at(index - 1).lexeme)) {
					throw std::invalid_argument("variable not declared");
				}
				std::string str_ID = words.at(index - 1).lexeme;
				if (lookahead == "]") {
					match("]");
					return  str_ID ;
				}
			}
		 }
		 else return "";
}
void translator::write_symbol_table()
{
	std::ofstream symbol_table_file(file_symbol_table);
	if (symbol_table_file.is_open()) {
		for (auto it : _symbol_table.type_table) {
			symbol_table_file << it.second << "\t" << it.first << "\t" << _symbol_table.address_table[it.first] <<"\n";
		}
	}
	else std::cout << "can't open file\n";
}

void translator::write_intermediate_code()
{
	std::ofstream code_file(file_machine_code);
	if (code_file.is_open()) {
		for (int i = 0; i < intermediate_code.size(); ++i) {
			code_file << intermediate_code[i].to_string()<< "\n";
		}
	}
	else std::cout << "can't open file\n";
}
void translator::emit(std::string op_code, std::string result)
{
	three_address_code tmp_code;
	tmp_code.op_code = op_codes.at(op_code);
	std::string symbol_address = _symbol_table.get_address(result);
	if (symbol_address != "") {
		tmp_code.result = symbol_address;
	}
	else if (symbol_address == "") {
		error("Symbol not defined");
	}
	intermediate_code.push_back(tmp_code);
	line_number++;
}
void translator::emit(std::string op_code, std::string arg_1, std::string result) 
{
	three_address_code tmp_code;
	tmp_code.op_code = op_codes.at(op_code);
	std::string arg1_address = _symbol_table.get_address(arg_1);
	std::string result_address = _symbol_table.get_address(result);
	if (arg1_address != "" && result_address != "") {
		tmp_code.arg_1 = arg1_address;
		tmp_code.result = result_address;
	}
	else if (arg1_address == "" || result_address == "") {

	}
	intermediate_code.push_back(tmp_code);
	line_number++;
}
void translator::emit(std::string op_code, std::string arg_1, std::string arg_2
	, std::string result) {

	three_address_code tmp_code;
	tmp_code.op_code = op_codes.at(op_code);
	std::string arg1_address = _symbol_table.get_address(arg_1);
	std::string arg2_address = _symbol_table.get_address(arg_2);
	std::string result_address = _symbol_table.get_address(result);
	if (arg1_address != "" && result_address != "") {
		tmp_code.arg_1 = arg1_address;
		tmp_code.arg_2 = arg2_address;
		tmp_code.result = result_address;
	}
	else if (arg1_address == ""|| arg2_address == "" || result_address == "" ) {

	}
	intermediate_code.push_back(tmp_code);
	line_number++;
}

void translator::emit(std::string op_code) {

	if (op_code == "GOTO") {
		three_address_code tmp_code;
		tmp_code.op_code = op_codes.at(op_code);

		intermediate_code.push_back(tmp_code);
		
		line_number++;
	}
}


void translator::emitC(std::string op_code, std::string arg_1, std::string arg_2,
	int _line_number) {


	three_address_code tmp_code;
	tmp_code.op_code = op_codes.at(op_code);
	std::string arg1_address = _symbol_table.get_address(arg_1);
	std::string arg2_address = _symbol_table.get_address(arg_2);
	std::string result_address = std::to_string(_line_number + 1 + 1);

	if (arg1_address != "" && result_address != "") {
		tmp_code.arg_1 = arg1_address;
		tmp_code.arg_2 = arg2_address;
		tmp_code.result = result_address;
	}
	else if (arg1_address == "" || arg2_address == "" || result_address == "") {

	}
	intermediate_code.push_back(tmp_code);
	line_number++;

}
void translator::back_patch(int s,int  e) {

	intermediate_code[s].result = std::to_string(e);

}