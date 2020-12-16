#pragma once
#include <string>
#include <stack>
#include "Node.h"
#include "Grammar.h"

class Parser
{
private:
	Grammar grammar;
	//std::string cuvant;
	std::vector<std::string> cuvant;
	char state;
	int i;
	std::stack<std::string> working_stack;
	//std::stack<char> input_stack;
	std::stack<std::string> input_stack;
public:
	//Parser(Grammar g, std::string word);
	Parser(Grammar g, std::vector<std::string> word);

	void expand();
	void advance();
	void momentary_insuccess();
	void back();
	void another_try();
	void success();

	/*
	Pre: node and stack must exist and must be valid
	Post: node is not null
	Input: Node*&, stack&
	Output:
	It constructs the tree corresponding to the elements of stack. 
	The parent node of the tree is the given Node*& argument.
	*/
	void construct_tree(Node *& node, std::stack<std::string> & stack);

	void print_current_state();

	/*
	Pre:
	Post: returned value is valid
	Input:
	Output: string
	Checks if the sequence given in the Parser constructor is accepted or not
	*/
	std::string doamne_ajuta();

	~Parser();
};
