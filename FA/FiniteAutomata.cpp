#include "stdafx.h"
#include "FiniteAutomata.h"
#include <iostream>



FiniteAutomata::FiniteAutomata(std::string filename)
{
	std::ifstream infile(filename);
	std::string line;
	std::string delimiter = ", ";
	size_t pos = 0;
	std::string token;

	std::getline(infile, line);
	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		states.push_back(token);
		line.erase(0, pos + delimiter.length());
	}
	states.push_back(line);

	pos = 0;
	std::getline(infile,line);
	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		alphabet.push_back(token);
		line.erase(0, pos + delimiter.length());
	}
	alphabet.push_back(line);

	std::getline(infile, line);
	startState = line;

	pos = 0;
	std::getline(infile, line);
	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		finalStates.push_back(token);
		line.erase(0, pos + delimiter.length());
	}
	finalStates.push_back(line);

	while (std::getline(infile, line)) {
		std::string start,val;
		pos = line.find(delimiter);
		start = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		std::string eq = " = ";
		pos = line.find(eq);
		val = line.substr(0, pos);
		line.erase(0, pos + eq.length());
		transitions[start][val].push_back(line);
	}
}

std::string FiniteAutomata::toString()
{
	std::string res = "";
	res += "States: ";
	for (std::string state : states) res = res + state + ", ";
	res += "\nAlphabet: ";
	for (std::string alph : alphabet) res = res + alph + ", ";
	res += "\nInitial State: ";
	res += startState;
	res += "\nFinal States";
	for (std::string state : finalStates) res = res + state + ", ";
	res += "\nTransitions: ";
	for (std::map<std::string, std::map<std::string, std::vector<std::string>>>::iterator iter = transitions.begin(); 
		iter != transitions.end(); ++iter)
	{
		std::string start = iter->first;
		for (std::map<std::string, std::vector<std::string>>::iterator iterVal = iter->second.begin();
			iterVal != iter->second.end(); ++iterVal)
		{
			std::string val = iterVal->first;
			for (std::string finish : iterVal->second) res = res + start + ", " + val + " = " + finish + "\n";
		}
	}
	return res;
}

std::string FiniteAutomata::menu() {
	std::string res = "";
	res += "1. Set of states\n";
	res += "2. Alphabet\n";
	res += "3. Initial state\n";
	res += "4. Final states\n";
	res += "5. Transitions\n";
	res += "6. Check if a state is accepted\n";
	res += "0. Exit\n";
	return res;
}

std::string FiniteAutomata::menuOption(int opt, std::string seq)
{
	std::string res = "";
	switch (opt) {
	case 1: {
		for (std::string state : states) res = res + state + " ";
		res += "\n";
		break;
	}
	case 2: {
		for (std::string alph : alphabet) res = res + alph + " ";
		res += "\n";
		break;
	}
	case 3: {
		res = startState;
		res += "\n";
		break;
	}
	case 4: {
		for (std::string state : finalStates) res = res + state + " ";
		res += "\n";
		break;
	}
	case 5: {
		for (std::map<std::string, std::map<std::string, std::vector<std::string>>>::iterator iter = transitions.begin();
			iter != transitions.end(); ++iter)
		{
			std::string start = iter->first;
			for (std::map<std::string, std::vector<std::string>>::iterator iterVal = iter->second.begin();
				iterVal != iter->second.end(); ++iterVal)
			{
				std::string val = iterVal->first;
				for (std::string finish : iterVal->second) res = res + start + ", " + val + " = " + finish + "\n";
			}
		}
		break;
	}
	case 6:
	{
		if (verifySequence(seq)) res = "True\n";
		else res = "False\n";
		break;
	}
	default: {res = ""; break; }
	}
	return res;
}

bool FiniteAutomata::verifySequence(std::string seq)
{
	if(isDFA()){
		std::string currentState = startState;
		for (char& c : seq) {
			if (transitions[currentState].find(std::string(1, c)) == transitions[currentState].end()) {
				return false;
			}
			currentState = transitions[currentState][std::string(1, c)][0];
		}
		if (std::find(finalStates.begin(), finalStates.end(), currentState) != finalStates.end()) return true;
		return false;
	}
	return false;
}

bool FiniteAutomata::isDFA(){
	for (std::map<std::string, std::map<std::string, std::vector<std::string>>>::iterator iter = transitions.begin();
			iter != transitions.end(); ++iter)
		{
			for (std::map<std::string, std::vector<std::string>>::iterator iterVal = iter->second.begin();
				iterVal != iter->second.end(); ++iterVal)
			{
				if(iterVal->second.size() != 1) return false;
			}
		}
	return true;
}

FiniteAutomata::~FiniteAutomata()
{
}
