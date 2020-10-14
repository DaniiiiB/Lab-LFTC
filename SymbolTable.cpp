// SymbolTable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashTable.h"
#include <iostream>
#include <process.h>


int main()
{
	HashTable tbl;
	tbl.insert("a");
	tbl.insert("2");
	tbl.insert("word");
	tbl.insert("false");
	tbl.insert("\"word\"");
	tbl.insert("s"); //ascii code 115
	tbl.insert("A2"); // ascii codes 65 + 50 = 115

	std::cout << tbl.print();
	system("pause");
}

