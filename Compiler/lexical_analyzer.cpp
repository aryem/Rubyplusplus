#include"lexical_analyzer.h"

void lexical_analyzer::analyze_code()
{
	while (index < code.length()) {
		if (code[index] != SPC && code[index] != TAB && code[index] != '\n' && code[index] != EOF) {
			int backtrack = index;
			token_lexeme tokenLexeme = is_keyword();

			if (!tokenLexeme.is_valid()) {
				index = backtrack;	
				tokenLexeme = is_identifier();
			}

			if (!tokenLexeme.is_valid()) {
				index = backtrack;
				tokenLexeme = is_literal_const();
			}

			if (!tokenLexeme.is_valid()) {
				index = backtrack;
				tokenLexeme = is_numeric_const();
			}

			if (!tokenLexeme.is_valid()) {
				index = backtrack;
				tokenLexeme = is_arithmetic_op();
			}

			if (!tokenLexeme.is_valid()) {
				index = backtrack;
				tokenLexeme = is_relational_op();
			}

			if (!tokenLexeme.is_valid()) {
				index = backtrack;
				tokenLexeme = is_punctuation();
			}

			if (!tokenLexeme.is_valid()) {
				index = backtrack;
				tokenLexeme = is_comment();
			}
			if (tokenLexeme.token == "ID")
				table.insert(tokenLexeme.lexeme);

			// Invalid character or symbol
			if (!tokenLexeme.is_valid())
			{
				error();
			}
			words.push_back(tokenLexeme);
		}
		else {
			index++;
		}

	}
}

void lexical_analyzer::error()
{
	std::cout << "Invalid symbol or character" << "\n";
	// terminating
	system("pause");
	std::exit(0);
}

void lexical_analyzer::define_keywords()
{
	key_words.insert(std::pair<std::string, std::string>("int", "INT"));
	key_words.insert(std::pair<std::string, std::string>("char", "CHAR"));
	key_words.insert(std::pair<std::string, std::string>("def", "DEF"));
	key_words.insert(std::pair<std::string, std::string>("if", "IF"));
	key_words.insert(std::pair<std::string, std::string>("else", "ELSE"));
	key_words.insert(std::pair<std::string, std::string>("elsif", "ELSIF"));
	key_words.insert(std::pair<std::string, std::string>("while", "WHILE"));
	key_words.insert(std::pair<std::string, std::string>("return", "RETURN"));
	key_words.insert(std::pair<std::string, std::string>("print", "PRINT"));
	key_words.insert(std::pair<std::string, std::string>("get", "GET"));
}

void lexical_analyzer::write_lex_files()
{
	std::ofstream writer;
	std::ofstream tableWriter;
	writer.open("words.txt");

	for (int i = 0; i < words.size(); i++) {
		writer << words[i].token << "\t" << ((words[i].lexeme == "") ? "^" : words[i].lexeme) << "\n";
	}

	writer.close();
	tableWriter.open("table.txt");

	std::set<std::string> ::iterator itr;
	for (itr = table.begin(); itr != table.end(); ++itr) {
		std::string str = *itr;
		tableWriter << str << "\n";
	}


	tableWriter.close();
}

bool lexical_analyzer::is_alphabet(char chr)
{
	return (((chr >= char(65) && chr <= char(90)) || (chr >= char(97) && chr <= char(122))) ? true : false);
}

bool lexical_analyzer::is_numeric(char chr)
{
	return (chr >= char(48) && chr <= char(57)) ? true : false;
}

bool lexical_analyzer::is_alpha_numeric(char chr)
{
	return (is_alphabet(chr) || is_numeric(chr)) ? true : false;
}

token_lexeme lexical_analyzer::is_punctuation()
{
	char ch;
	if (index < code.length())
		ch = code[index];
	else
		ch = ' ';

	token_lexeme tokenLexeme;

	switch (ch) {
	case '{':
		tokenLexeme.token = "{";
		index++;
		break;
	case '}':
		tokenLexeme.token = "}";
		index++;
		break;
	case '(':
		tokenLexeme.token = "(";
		index++;
		break;
	case ')':
		tokenLexeme.token = ")";
		index++;
		break;
	case '[':
		tokenLexeme.token = "[";
		index++;
		break;
	case ']':
		tokenLexeme.token = "]";
		index++;
		break;
	case ',':
		tokenLexeme.token = ",";
		index++;
		break;
	default:
		break;
	}

	return tokenLexeme;
}

token_lexeme lexical_analyzer::is_identifier()
{
	int state = 1;
	token_lexeme tokenLexeme;
	std::string str = "";
	while (true) {
		char ch;
		if (index < code.length())
			ch = code[index];
		else
			ch = ' ';

		switch (state) {
		case 1:
			if (is_alphabet(ch)) {
				state = 2;
				str += ch;
				index++;
				break;
			}
			else {
				return tokenLexeme;
			}
		case 2:
			if (is_alpha_numeric(ch)) {
				state = 2;
				str += ch;
				index++;
				break;
			}
			else {
				tokenLexeme.token = "ID";
				tokenLexeme.lexeme = str;
				return tokenLexeme;
			}
		}
	}
}

token_lexeme lexical_analyzer::is_literal_const()
{
	int state = 1;
	token_lexeme tokenLexeme;
	std::string str = "";

	while (true) {
		char ch;
		if (index < code.length())
			ch = code[index];
		else
			ch = ' ';
		switch (state) {
		case 1:
			if (ch == '\'') {
				state = 2;
				index++;
				break;
			}
			else {
				return tokenLexeme;
			}
		case 2:
			if (is_alphabet(ch)) {
				state = 3;
				str += ch;
				index++;
				break;
			}
			else {
				return tokenLexeme;
			}
		case 3:
			if (ch == '\'') {
				state = 4;
				index++;
				break;
			}
			else {
				return tokenLexeme;
			}
		case 4:
			tokenLexeme.token = "LC";
			tokenLexeme.lexeme = str;
			return tokenLexeme;


		}


	}

	return tokenLexeme;
}

token_lexeme lexical_analyzer::is_numeric_const()
{
	int state = 1;
	token_lexeme tokenLexeme;
	std::string str;
	while (true) {

		char ch;
		if (index < code.length())
			ch = code[index];
		else
			ch = ' ';

		switch (state) {
		case 1:
			if (is_numeric(ch)) {
				state = 2;
				str += ch;
				index++;
				break;
			}
			else {
				return tokenLexeme;
			}
		case 2:
			if (is_numeric(ch)) {
				state = 2;
				str += ch;
				index++;
				break;
			}
			else if (is_alphabet(ch) && ch != SPC) {
				error();
			}
			else {
				tokenLexeme.token = "NC";
				tokenLexeme.lexeme = str;
				return tokenLexeme;
			}
		}

	}

}

token_lexeme lexical_analyzer::is_arithmetic_op()
{
	int state = 1;
	token_lexeme tokenLexeme;
	while (true) {
		char ch;
		if (index < code.length())
			ch = code[index];
		else
			ch = ' ';

		switch (state) {
		case 1:
			if (ch == char(PLUS_OP)) {
				state = 2;
				index++;
				break;
			}
			else if (ch == char(MINUS_OP)) {
				state = 3;
				index++;
				break;
			}
			else if (ch == char(MUL_OP)) {
				state = 4;
				index++;
				break;
			}
			else if (ch == char(DIV_OP)) {
				state = 5;
				index++;
				break;
			}
			else
				return tokenLexeme;

		case 2:
			tokenLexeme.token = PLUS_OP;
			return tokenLexeme;
		case 3:
			tokenLexeme.token = MINUS_OP;
			return tokenLexeme;
		case 4:
			tokenLexeme.token = MUL_OP;
			return tokenLexeme;
		case 5:
			tokenLexeme.token = DIV_OP;
			return tokenLexeme;

		}

	}
}

token_lexeme lexical_analyzer::is_relational_op()
{
	int state = 1;
	token_lexeme tokenLexeme;
	while (true) {

		char ch;
		if (index < code.length())
			ch = code[index];
		else
			ch = ' ';

		switch (state) {
		case 1:
			if (ch == '<') {
				state = 2;
				index++;
				break;
			}
			else if (ch == '>') {
				state = 5;
				index++;
				break;
			}
			else if (ch == '=') {
				state = 8;
				index++;
				break;
			}
			else {
				return tokenLexeme;
			}

		case 2:
			if (ch == '=') {
				state = 3;
				index++;
				break;
			}
			else {
				state = 4;
				break;
			}
		case 3:
			tokenLexeme.token = "RO";
			tokenLexeme.lexeme = "LE";
			return tokenLexeme;
		case 4:
			tokenLexeme.token = "RO";
			tokenLexeme.lexeme = "LT";
			return tokenLexeme;
		case 5:
			if (ch == '=') {
				state = 6;
				index++;
				break;
			}
			else {
				state = 7;
				index++;
				break;
			}
		case 6:
			tokenLexeme.token = "RO";
			tokenLexeme.lexeme = "GE";
			return tokenLexeme;
		case 7:
			tokenLexeme.token = "RO";
			tokenLexeme.lexeme = "GT";
			return tokenLexeme;
		case 8:
			if (ch == '=') {
				state = 9;
				index++;
				break;
			}
			else {
				tokenLexeme.token = "=";
				return tokenLexeme;
			}
		case 9:
			tokenLexeme.token = "RO";
			tokenLexeme.lexeme = "ET";
			return tokenLexeme;
		}
	}

}

token_lexeme lexical_analyzer::is_keyword()
{
	int state = 1;
	token_lexeme tokenLexeme;
	std::string str = "";

	while (true) {
		char ch;
		if (index < code.length())
			ch = code[index];
		else
			ch = ' ';

		switch (state)
		{
		case 1:
			if (is_alphabet(ch)) {
				state = 2;
				str += ch;
				index++;
				break;
			}
			else {
				return tokenLexeme;
			}
		case 2:
			if (is_alphabet(ch)) {
				state = 2;
				str += ch;
				index++;
				break;
			}
			else {
				if (key_words.find(str) != key_words.end()) {
					//cout << str;
					tokenLexeme.token = key_words.at(str);
					return tokenLexeme;
				}

				else {
					return tokenLexeme;
				}
			}

		}
	}
}

token_lexeme lexical_analyzer::is_comment()
{
	int state = 1;
	token_lexeme tokenLexeme;
	std::string str;
	while (true) {
		char ch;
		if (index < code.length())
			ch = code[index];
		else
			ch = ' ';

		switch (state) {
		case 1:
			if (ch == '#') {
				state = 2;
				index++;
				break;
			}
			else {
				return tokenLexeme;
			}
		case 2:
			if (ch == char(10) || ch == EOF) {
				tokenLexeme.token = "CM";
				tokenLexeme.lexeme = str;
				return tokenLexeme;
			}
			else {
				state = 2;
				index++;
				str += ch;
				break;
			}
		}
	}
}

std::string lexical_analyzer::get_file(std::string file_name)
{
	std::ifstream in;
	in.open(file_name);
	std::string  str = static_cast< std::stringstream const&>(std::stringstream() << in.rdbuf()).str();
	in.close();
	return str;
}

std::vector<token_lexeme> lexical_analyzer::run_lex(std::string code_file)
{
	code = get_file(code_file);
	define_keywords();
	analyze_code();
	write_lex_files();
	
	return words;
}
