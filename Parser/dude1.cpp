// dude1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Grammar.h"
#include "Parser.h"
#include "stdafx.h"
#include <fstream>
#include "HashTable.h"
#include "FiniteAutomata.h"

std::map<std::string, int> generate_token_map(std::string file) {
	std::map<std::string, int> tokens;
	std::ifstream infile(file);
	int value;
	std::string token;
	while (infile >> token >> value) {
		if (token.compare("<space>") == 0) {
			token = " ";
		}
		tokens[token] = value;
	}
	return tokens;
}

bool is_identifier(std::string token) {
	/*
	bool found_digit = false, found_underscore = false, first_letter = false, after_underscore = true;

	for (char& c : token) {
	if (c == '_') {
	if (!first_letter) return false; //if the first character is not a letter
	if (found_underscore) return false; //if we already found an underscore
	if (found_digit) return false; //if it follows a digit
	found_underscore = true;
	}
	else if (c >= '0' && c <= '9') {
	if (!first_letter) return false; //if the first character is not a letter
	if (found_underscore && after_underscore) return false; //if it comes right after an _
	found_digit = true;
	}
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
	if (!first_letter) first_letter = true; //the first character is a letter
	if (found_underscore && after_underscore) after_underscore = false; //the first character after _ is a letter
	if (found_digit) return false; //it follows a digit
	}
	else return false;
	}
	if (found_underscore && after_underscore) return false; //if the last character read was _
	return true;
	*/
	FiniteAutomata fa = FiniteAutomata("IdentifierFA.txt");
	return fa.verifySequence(token);
}

bool isIntegerConstant(std::string token) {
	FiniteAutomata fa = FiniteAutomata("IntegerConstantFA.txt");
	return fa.verifySequence(token);
}

bool isBoolenConstant(std::string token) {
	return (token.compare("TRUE") == 0 || token.compare("FALSE") == 0);
}

bool isStringConstant(std::string token) {
	char first_character = token.c_str()[0];
	if (first_character == '\"') {
		char last_character = '?';
		for (char& c : token.substr(1)) {
			if (last_character == '\"') return false;
			if ((c < '0' || c > '9') && (c < 'a' || c > 'z')
				&& (c < 'A' || c > 'Z') && c != ' ' && c != '\"')
				return false;
			last_character = c;
		}
		if (last_character != '\"') return false;
		return true;
	}
	return false;
}

bool isCharacterConstant(std::string token) {
	char first_character = token.c_str()[0];
	if (first_character == '\'') {
		if (token.length() != 3) return false;
		if (token.c_str()[2] != '\'') return false;
		if ((token.c_str()[1] < '0' || token.c_str()[1] > '9')
			&& (token.c_str()[1] < 'a' || token.c_str()[1] > 'z')
			&& (token.c_str()[1] < 'A' || token.c_str()[1] > 'Z')
			&& token.c_str()[1] != ' ')
			return false;
		return true;
	}
	return false;
}

/*
Pre: string must be valid
Post:
Input: string
Output: true or false
Checks if the given token can be a constant
*/
bool is_constant(std::string token) {
	/*
	if (token.compare("TRUE") == 0 || token.compare("FALSE") == 0) return true;
	if (token.compare("0") == 0) return true;

	char first_character = token.c_str()[0];

	if (first_character == 'n' && token.substr(0, 3).compare("neg") != 0) return false;

	if (first_character == '\"') {
	char last_character = '?';
	for (char& c : token.substr(1)) {
	if (last_character == '\"') return false;
	if ((c < '0' || c > '9') && (c < 'a' || c > 'z')
	&& (c < 'A' || c > 'Z') && c != ' ' && c != '\"')
	return false;
	last_character = c;
	}
	if (last_character != '\"') return false;
	return true;
	}

	if (first_character == '\'') {
	if (token.length() != 3) return false;
	if (token.c_str()[2] != '\'') return false;
	if ((token.c_str()[1] < '0' || token.c_str()[1] > '9')
	&& (token.c_str()[1] < 'a' || token.c_str()[1] > 'z')
	&& (token.c_str()[1] < 'A' || token.c_str()[1] > 'Z')
	&& token.c_str()[1] != ' ')
	return false;
	return true;
	}


	if (token.substr(0, 3).compare("neg") == 0) {
	if (token.substr(3).c_str()[0] == '0') return false;
	for (char& c : token.substr(3)) {
	if (c < '0' || c > '9') return false;
	}
	return true;
	}

	if (first_character >= '1' && first_character <= '9') {
	for (char& c : token.substr(1)) {
	if (c < '0' || c > '9') return false;
	}
	return true;
	}

	return false;
	*/
	return (isIntegerConstant(token) || isBoolenConstant(token) || isCharacterConstant(token) || isStringConstant(token));
}


/*
Pre: input must be character
Post:
Input: char
Output: true or false
Checks if a character is a separator
*/
bool is_separator(char c) {
	return (c == '[' || c == ']' || c == '{' || c == '}' || c == ';' || c == ',' || c == '-' || c == '(' || c == ')');
}

/*
Pre: input must be character
Post:
Input: char
Output: true or false
Checks if a character is an operator
*/
bool is_operator(char c) {
	return (c == '*' || c == '/');
}

/*
Pre: filename is a valid file name, st, pif and tokens must exist
Post: st and pif must be both empty or non empty
Input: string, HashTable, vector of pairs of string and integer, map<string,int>
Output: true or false
Splits the content of the input file into tokens, classify those tokens
(operator, separator, reserved word, constant, ientifier) and fills st
and pif in the following way:
-if it's an operator, separator or reserved word, the pair consisting the token and
it's value from tokens is added to pif
-if it's an identifier or constant, the token is added to st if it's not there already;
the interaction of a token with st return a value; a pair consisting of
IDENTIFIER / CONST together with the value got from the st for that token is added to pif
-if none of the above, print the error
The function returns false if we have an error, true otherwise
*/
bool parse_file(std::string filename, HashTable &st,
	std::vector<std::pair<std::string, int>> &pif, std::map<std::string, int> tokens, std::vector<std::string> &sequence) {
	bool res = true;
	std::ifstream infile(filename);
	std::string line;
	bool in_string = false;
	int line_count = 0;
	while (std::getline(infile, line)) {
		std::cout << line << std::endl;
		line_count++;
		std::string current_string = "";
		for (char& c : line) {
			if ((c == '\"' || c == '\'') && in_string) {
				in_string = false;
				current_string += c;
				continue;
			}
			if ((c == '\"' || c == '\'') && !in_string)
				in_string = true;

			if (in_string) current_string += c;
			else {
				if (!(c == ' ' || is_separator(c) || is_operator(c)))
					current_string += c;
				else {
					if (tokens.count(current_string)) {
						pif.push_back(std::make_pair(current_string, tokens[current_string]));
						sequence.push_back(std::to_string(tokens[current_string]));
					}
					else {
						if (!current_string.empty()) {
							if (is_constant(current_string) || is_identifier(current_string)) {
								int value = st.search(current_string);
								if (value == -1) value = st.insert(current_string);
								if (is_constant(current_string)) {
									pif.push_back(std::make_pair("CONST", value));
									sequence.push_back("402");
								}
								else if (is_identifier(current_string)) {
									pif.push_back(std::make_pair("IDENTIFIER", value));
									sequence.push_back("401");
								}
							}
							else {
								std::cout << "Erorr on line " << line_count << " : " << current_string << " is not defined" << std::endl;
								res = false;
							}
						}
					}
					if (is_separator(c) || is_operator(c)) {
						pif.push_back(std::make_pair(std::string(1, c), tokens[std::string(1, c)]));
						sequence.push_back(std::to_string(tokens[std::string(1, c)]));
					}
					current_string = "";
				}
			}
		}
		if (!current_string.empty()) {
			if (tokens.count(current_string)) {
				pif.push_back(std::make_pair(current_string, tokens[current_string]));
				sequence.push_back(std::to_string(tokens[current_string]));
			}
			else {
				if (is_constant(current_string) || is_identifier(current_string)) {
					int value = st.search(current_string);
					if (value == -1) value = st.insert(current_string);
					if (is_constant(current_string))
					{
						pif.push_back(std::make_pair("CONST", value)); 
						sequence.push_back("402");
					}
					else if (is_identifier(current_string)) {
						pif.push_back(std::make_pair("IDENTIFIER", value));
						sequence.push_back("401");
					}
				}
				else {
					std::cout << "Erorr on line " << line_count << " : " << current_string << " is not defined" << std::endl;
					res = false;
				}
			}
		}
	}
	return res;
}

std::string pif_to_string(std::vector<std::pair<std::string, int>> pif) {
	std::string res = "";
	for (std::vector<std::pair<std::string, int>>::iterator it = pif.begin(); it != pif.end(); ++it) {
		res = res + (*it).first + " " + std::to_string((*it).second) + "\n";
	}
	return res;
}


int main()
{
	Grammar * grammar = new Grammar();
	//grammar->readFile("theg.txt");
	grammar->readFile("theg.txt");
	std::cout << grammar->prettyPrint();
	std::cout << "-----------------";
	//std::cout << "\n" << grammar->production_for_nonterminal('S') << "\n---------------\n";// << grammar->production_for_nonterminal('A');

	
	std::map<std::string, int> tokens = generate_token_map("token.in");
	std::vector<std::pair<std::string, int>> pif;
	HashTable st;
	std::vector<std::string> sequence = std::vector<std::string>();
	bool do_print = parse_file("p1.lmao", st, pif, tokens, sequence);
	if (do_print) {
		std::cout << std::endl;
		std::cout << "----PIF----" << std::endl;
		std::cout << std::endl;
		std::cout << pif_to_string(pif) << std::endl;
		for (auto s : sequence) {
			std::cout << s << " ";
		}
		std::cout << std::endl;

		Parser * parser = new Parser(*grammar, sequence);
		if (!grammar->isLeftRecursive()) {
			std::cout << parser->doamne_ajuta();
		}
	}
	
	//Parser * parser = new Parser(*grammar, std::vector<std::string>({"a","a","cz","b","cz"}));
	//std::cout << parser->doamne_ajuta();
}

