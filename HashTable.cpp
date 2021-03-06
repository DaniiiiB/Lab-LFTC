#include "stdafx.h"
#include "HashTable.h"


HashTable::HashTable()
{
	for (int i = 0; i < 23; i++)
		table[i] = nullptr;
}


int HashTable::hash(std::string token)
{
	int sum = 0;
	for (char& c : token)
		sum += c;
	return sum % 23;
}

int HashTable::insert(std::string token)
{
	int hash_value = hash(token);
	Node *node_value = new Node;
	node_value->data = token;
	node_value->next = nullptr;
	Node *current = table[hash_value];
	if (current == nullptr)
		table[hash_value] = node_value;
	else
	{
		while (current->next != nullptr)
			current = current->next;
		current->next = node_value;
	}
	return hash_value;
}

int HashTable::search(std::string token)
{
	int hash_value = hash(token);
	Node *current = table[hash_value];
	if (current == nullptr)
		return -1;
	while (current != nullptr) {
		if (current->data.compare(token) == 0) return hash_value;
		current = current->next;
	}
	return -1;
}

std::string HashTable::print()
{
	std::string res = "";
	for (int i = 0; i < 23; i++)
	{
		res = res + std::to_string(i) + ": ";
		Node *current = table[i];
		while (current != nullptr) {
			res = res + current->data;
			if (current->next != nullptr)
				res = res + " -> ";
			current = current->next;
		}
		res = res + "\n";
	}
	return res;
}


HashTable::~HashTable()
{
}
