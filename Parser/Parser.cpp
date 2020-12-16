#include "Parser.h"
#include<iostream>

//Parser::Parser(Grammar g, std::string word)
Parser::Parser(Grammar g, std::vector<std::string> word)
{
	grammar = g;
	cuvant = word;
	state = 'q';
	i = 0;
	working_stack = std::stack<std::string>();
	//input_stack.push(grammar.getInitialState());
	//input_stack.push(std::string(1, grammar.getInitialState()));
	input_stack.push(grammar.getInitialState());
}

void Parser::expand()
{
	//ma doare capul
	//char ch = input_stack.top();
	std::string ch = input_stack.top();
	input_stack.pop();
	std::vector<std::string> prods = grammar.getProdForNonT(ch);

	std::string res = "";
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;
	while ((pos = prods[0].find(delimiter)) != std::string::npos) {
		token = prods[0].substr(0, pos);
		res = token + " " + res;
		prods[0].erase(0, pos + delimiter.length());
	}
	res = prods[0] + " " + res;
	
	while ((pos = res.find(delimiter)) != std::string::npos) {
		token = res.substr(0, pos);
		input_stack.push(token);
		res.erase(0, pos + delimiter.length());
	}
	//std::cout << "res is: " << res << std::endl;
	//input_stack.push(res);
	/*std::reverse(prods[0].begin(), prods[0].end());
	for (auto c : prods[0]) {
		input_stack.push(c);
	}
	*/
	std::string string_ch = ch + "~0";
	working_stack.push(string_ch);
}

void Parser::advance()
{
	i++;
	//char ch = input_stack.top();
	std::string ch = input_stack.top();
	input_stack.pop();
	//std::string string_ch = std::string(1, ch);
	//working_stack.push(string_ch);
	working_stack.push(ch);
}

void Parser::momentary_insuccess()
{
	state = 'b';
}

void Parser::back()
{
	i--;
	std::string string_ch = working_stack.top();
	working_stack.pop();

	//char ch = string_ch[0];
	//input_stack.push(ch);
	input_stack.push(string_ch);
}

void Parser::another_try()
{
	std::string string_ch_full = working_stack.top();
	working_stack.pop();

	char chr;
	std::string string_ch = "";
	if (string_ch_full.find('~') != std::string::npos) {
		char chr;
		do {
			chr = string_ch_full[0];
			string_ch_full.erase(string_ch_full.begin(), string_ch_full.begin() + 1);
			if (chr != '~') string_ch += chr;
		} while (chr != '~');
	}

	//char ch = string_ch[0];
	//if (i == 0 && ch == grammar.getInitialState()) {
	if (i == 0 && string_ch.compare(grammar.getInitialState()) == 0){
		state = 'e';
	}
	//std::vector<std::string> prods = grammar.getProdForNonT(ch);
	std::vector<std::string> prods = grammar.getProdForNonT(string_ch);

	//string_ch.erase(string_ch.begin(), string_ch.begin() + 1);

	int nr = std::stoi(string_ch_full);

	int dec = 0;
	for (int counter = 0; counter < prods[nr].size(); counter++)
	{
		if (prods[nr][counter] == ' ')
		{
			dec++;
		}
	}
	dec++;
	while (dec != 0) {
		input_stack.pop();
		dec--;
	}

	if (nr + 1 < prods.size()) {
		// ne-am dat seama mai tarziu de state = 'q' decat de mai sus
		//	|
		//	|
		//	V
		state = 'q';
		//std::string new_ch = std::string(1, ch) + std::to_string((nr + 1));
		std::string new_ch = string_ch + "~" + std::to_string((nr + 1));
		working_stack.push(new_ch);
		std::string another_prod = prods[nr + 1];
		/*
		std::reverse(another_prod.begin(), another_prod.end());
		for (auto c : another_prod) {
			input_stack.push(c);
		}
		*/
		std::string res = "";
		std::string delimiter = " ";
		size_t pos = 0;
		std::string token;
		while ((pos = another_prod.find(delimiter)) != std::string::npos) {
			token = another_prod.substr(0, pos);
			res = token + " " + res;
			another_prod.erase(0, pos + delimiter.length());
		}
		res = another_prod + " " + res;
		//std::cout << res << std::endl;
		while ((pos = res.find(delimiter)) != std::string::npos) {
			token = res.substr(0, pos);
			input_stack.push(token);
			res.erase(0, pos + delimiter.length());
		}
		//input_stack.push(res);
	}
	else {
		//input_stack.push(ch);
		input_stack.push(string_ch);
	}
}

void Parser::success()
{
	state = 'f';
}

void Parser::construct_tree(Node *& node, std::stack<std::string> & stack)
{
	Node * tata = nullptr;
	Node * current = nullptr;

	std::stack<std::string> aux = std::stack<std::string>();

	//std::cout << stack.top() << std::endl;
	while (grammar.getTerminals().find(stack.top()) != std::string::npos) {
		stack.pop();
	}

	std::string string_ch = stack.top();
	stack.pop();

	//std::vector<std::string> prods = grammar.getProdForNonT(string_ch[0]);
	//if (node == nullptr) {
	//	node = new Node(string_ch[0]);
	//}
	char c;
	std::string working_string = "";
	do {
		c = string_ch[0];
		string_ch.erase(string_ch.begin(), string_ch.begin() + 1);
		if (c != '~') working_string += c;
	} while (c != '~');
	//std::cout << string_ch << std::endl;
	int nr = std::stoi(string_ch);


	std::vector<std::string> prods = grammar.getProdForNonT(working_string);
	if (node == nullptr) {
		node = new Node(working_string);
	}

	//string_ch.erase(string_ch.begin(), string_ch.begin() + 1);
	//int nr = std::stoi(string_ch);


	/*node->setLeftChild(new Node(prods[nr][0]));
	current = node->getLeftChild();

	for (auto c : prods[nr].substr(1)) {
		current->setRightSibling(new Node(c));
		current = current->getRightSibling();
	}*/
	std::string res = "";
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token = "";
	while ((pos = prods[nr].find(delimiter)) != std::string::npos) {
		//std::cout << prods[nr] << std::endl;
		if (token.compare("") == 0) {
			token = prods[nr].substr(0, pos);
			node->setLeftChild(new Node(token));
			current = node->getLeftChild();
			prods[nr].erase(0, pos + delimiter.length());
		}
		else {
			token = prods[nr].substr(0, pos);
			current->setRightSibling(new Node(token));
			current = current->getRightSibling();
			prods[nr].erase(0, pos + delimiter.length());
		}
	}
	if (token.compare("") == 0) {
		token = prods[nr].substr(0, pos);
		node->setLeftChild(new Node(token));
		current = node->getLeftChild();
		prods[nr].erase(0, pos + delimiter.length());
	}
	else {
		current->setRightSibling(new Node(prods[nr]));
		current = current->getRightSibling();
	}


	current = node->getLeftChild();
	while (current != nullptr) {
		if (grammar.getNonTerminals().find(current->getData()) != std::string::npos && 
			grammar.getTerminals().find(current->getData()) == std::string::npos) {
			construct_tree(current, stack);
		}
		current = current->getRightSibling();
	}
}

void Parser::print_current_state()
{
	std::cout << "state: " << state << "   ";
	std::cout << "i: " << i << "   ";
	//std::stack<char> copy_input_stack = std::stack<char>(input_stack);
	std::stack<std::string> copy_input_stack = std::stack<std::string>(input_stack);
	std::string iss = "";
	while (!copy_input_stack.empty()) {
		auto top = copy_input_stack.top();
		copy_input_stack.pop();
		//iss += std::string(1, top);
		iss = iss + "<-" + top;
	}
	if(iss != "") iss.erase(iss.begin(), iss.begin() + 2);
	std::cout << "input stack: " << iss << "   ";
	std::stack<std::string> copy_working_stack = std::stack<std::string>(working_stack);
	std::string wss = "";
	while (!copy_working_stack.empty()) {
		auto top = copy_working_stack.top();
		copy_working_stack.pop();
		wss = wss + "->" + top;
	}
	if(wss != "") wss.erase(wss.begin(), wss.begin() + 2);
	std::cout << "working stack: " << wss << std::endl;
}

std::string Parser::doamne_ajuta()
{
	print_current_state();
	while (state != 'f' && state != 'e') {
		if (state == 'q') {
			std::cout << "cuv size: " << cuvant.size() << std::endl;
			std::cout << "i: " << i << std::endl;
			if (input_stack.empty() && i == cuvant.size()) {
				std::cout << "calling success()" << std::endl;
				success();
				print_current_state();
				break;
			}
			//char ch = input_stack.top();
			std::string ch = input_stack.top();
			std::cout << input_stack.top() << std::endl;
			if (grammar.getTerminals().find(ch) != std::string::npos) {
				//if (ch == cuvant[i]) {
				if (i < cuvant.size() && ch.compare(cuvant[i]) == 0){
					std::cout << "calling advance()" << std::endl;
					advance();
					print_current_state();
				}
				else {
					std::cout << "calling momentary_insuccess()" << std::endl;
					momentary_insuccess();
					print_current_state();
				}
			}
			else if (grammar.getNonTerminals().find(ch) != std::string::npos) {
				std::cout << "calling expand()" << std::endl;
				expand();
				print_current_state();
			}
		}
		else if (state == 'b') {
			std::string string_ch = working_stack.top();
			std::cout << string_ch << std::endl;
			std::string working_string = "";
			if (string_ch.find('~') != std::string::npos) {
				char c;
				do {
					c = string_ch[0];
					string_ch.erase(string_ch.begin(), string_ch.begin() + 1);
					if (c != '~') working_string += c;
				} while (c != '~');
				string_ch = working_string;
			}
			if(grammar.getTerminals().find(string_ch) != std::string::npos) {
				std::cout << "calling back()" << std::endl;
				back();
				print_current_state();
			}
			else if (grammar.getNonTerminals().find(string_ch) != std::string::npos) {
				std::cout << "calling another_try()" << std::endl;
				another_try();
				print_current_state();
			}
		}
	}
	if (state == 'f') {
		std::stack<std::string> aux = std::stack<std::string>();
		while (!working_stack.empty()) {
			std::string string_ch = working_stack.top();
			working_stack.pop();
			aux.push(string_ch);
		}
		std::cout << '\n';
		Node * tata = nullptr;
		construct_tree(tata, aux);
		std::string res = "";
		tata->prettyPrint("", res);
		std::cout << res;
		return "accepted sequence\n";
	}
	if (state == 'e') {
		return "error\n";
	}
	return std::string("cu ce ai gresit ma nene ma");
}

Parser::~Parser()
{
}
