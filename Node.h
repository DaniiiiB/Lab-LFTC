#pragma once
#include "stdafx.h"
#include <string>

struct Node {
	std::string data;
	struct Node *next;
};
