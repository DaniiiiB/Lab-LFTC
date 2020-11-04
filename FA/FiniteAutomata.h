#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>

class FiniteAutomata
{
private:
	std::vector<std::string> states;
	std::vector<std::string> alphabet;
	std::string startState;
	std::vector<std::string> finalStates;
	std::map<std::string, std::map<std::string, std::vector<std::string>>> transitions;
public:
	FiniteAutomata(std::string filename);
	std::vector<std::string> getStates() { return states; }
	std::vector<std::string> getAlphabet() {return alphabet; }
	std::string getStartState() { return startState; }
	std::vector<std::string> getFinalStates() { return finalStates; }
	std::map<std::string, std::map<std::string, std::vector<std::string>>> getTransitions() { return transitions; }
	std::string toString();
	std::string menu();
	std::string menuOption(int opt, std::string seq="");
	bool verifySequence(std::string seq);
	~FiniteAutomata();
};

