#pragma once
#include <string>
#include "Node.h"

class HashTable
{
private:
	Node* table[26];

public:
	HashTable();

	/*
	Pre: the string must be valid
	Post:
	Input: string
	Output: integer 
	Functionality: hashes the value of the input to an integer between 0 and 25
	*/
	int hash(std::string token);

	/*
	Pre: the string must be valid
	Post:
	Input string
	Output: integer
	Functionality: inserts the given input into the hash table and returns the hash value that the input was given
	*/
	int insert(std::string token);

	/*
	Input:
	Output: string
	Functionality: turns the hash table into a readable form
	*/
	std::string print();


	~HashTable();
};

