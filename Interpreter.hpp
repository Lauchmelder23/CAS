#pragma once
#include <vector>
#include <map>
#include <string>

#include "Token.hpp"

class Interpreter
{
public:
	static double interpret(char* _string);

private:
	static bool scanForErrors();
	static bool getResult();

	static bool createSymbolList(std::vector<Symbol*>& symbols);
	static bool createOrderedTokenList(std::vector<Symbol*> symbols, std::vector<NonChar*>& tokens);

	static std::string string;
	static std::string numbers;
	static std::string operators;
	static std::map<char, unsigned int> operation_order;

	static double result;
	static bool justNumber;
};

