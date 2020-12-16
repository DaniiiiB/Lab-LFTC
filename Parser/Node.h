#pragma once
#include<string>

class Node {
private:
	//char data;
	std::string data;
	Node * parent;
	Node * left_child;
	Node * right_sibling;
public:
	//Node(char data);
	Node(std::string data);

	//char getData();
	std::string getData();

	Node * getParent();

	Node * getLeftChild();

	Node * getRightSibling();

	//void setData(char newData);
	void setData(std::string newData);

	void setLeftChild(Node * newChild);

	void setRightSibling(Node * newSibling);

	void setParent(Node * newParent);

	void prettyPrint(std::string tab, std::string & res);

	~Node();
};