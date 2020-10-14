#pragma once
#include "stdafx.h"
#include <string>

struct Node {
	private std::string data;
	private struct Node *next;
};
