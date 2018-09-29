#include "Interpreter.hpp"
#include "Error.hpp"

#include <iostream>

#define EULER 2.718281828459045
#define PI 3.1415926535

double Interpreter::result = 0;
bool Interpreter::justNumber = false;
std::string Interpreter::numbers = "0123456789Aaep.,";
std::string Interpreter::operators = "+-*/^_";
std::string Interpreter::string = "";
std::map<char, unsigned int> Interpreter::operation_order = {
	{'+', 0},
	{'-', 0},
	{'*', 1},
	{'/', 1},
	{'^', 2},
	{'_', 2}
};

double Interpreter::interpret(std::string _string)
{
	string = _string;
	justNumber = false;

	if (!scanForErrors())
		return NULL;

	if (!getResult())
		return NULL;

	if (justNumber)
	{
		return result;
	}

	return result;
}


bool Interpreter::scanForErrors()
{
	for (char c : string)
	{
		if (std::find(std::begin(numbers), std::end(numbers), c) == std::end(numbers) &&
			std::find(std::begin(operators), std::end(operators), c) == std::end(operators))
		{
			UNKNOWN_CHAR_ERROR(c);
		}
	}

	return true;
}

bool Interpreter::getResult()
{
	std::vector<Symbol*> symbols;
	if (!createSymbolList(symbols)) {
		SYMBOL_LIST_ERROR;
	}

	if (justNumber)
	{
		return true;
	}

	std::vector<NonChar*> tokens;
	if (!createOrderedTokenList(symbols, tokens)) {
		TOKEN_LIST_ERROR;
	}

	result = tokens[tokens.size() - 1]->value();

	return true;
}

bool Interpreter::createSymbolList(std::vector<Symbol*>& symbols)
{
	bool number = false;
	bool hasOperator = false;
	bool expectOperator = false;
	std::string num = "";

	for (char c : string)
	{
		if (std::find(std::begin(numbers), std::end(numbers), c) != std::end(numbers))
		{
			if (expectOperator)
			{
				UNEXPECTED_SYMBOL;
			}

			if (number)
			{
				if (c == 'A' || c == 'a')
				{
					symbols.push_back(new Number(std::stod(num) * result));
					expectOperator = true;
				}

				if (c == 'e')
				{
					symbols.push_back(new Number(std::stod(num) * EULER));
					expectOperator = true;
				}

				if (c == 'p')
				{
					symbols.push_back(new Number(std::stod(num) * PI));
					expectOperator = true;
				}
			}
			else 
			{
				if (c == 'A' || c == 'a')
				{
					symbols.push_back(new Number(result));
					expectOperator = true;
				}

				if (c == 'e')
				{
					symbols.push_back(new Number(EULER));
					expectOperator = true;
				}

				if (c == 'p')
				{
					symbols.push_back(new Number(PI));
					expectOperator = true;
				}
			}

			if (c == '.' || c == ',')
			{
				num += '.';
			}
			else
			{
				num += c;
			}
			number = true;
		}

		if (std::find(std::begin(operators), std::end(operators), c) != std::end(operators))
		{
			
			hasOperator = true;
			if (number == true)
			{
				//std::cout << "++++++++++++" << num << "++++++++++++++" << std::endl;
				if (num != "" && !expectOperator)
				{
					try
					{
						symbols.push_back(new Number(std::stod(num)));
					}
					catch (...)
					{
						INTEGER_TOO_BIG(num);
					}
				}
				symbols.push_back(new Operator(c));
				number = false;
				num = "";
			}
			else
			{
				if (c == '-')
				{
					number = true;
					num += c;
				}
				else {
					TOO_MANY_OPERATORS;
				}
			}

			expectOperator = false;
			
		}
	}

	if (number != true)
	{
		ILLEGAL_OPERATOR_POSITION;
	}

	if (num != "" && !expectOperator)
	{
		try
		{
			if (number == true) symbols.push_back(new Number(std::stod(num)));
		}
		catch (...)
		{
			INTEGER_TOO_BIG(num);
		}
	}

	if (!hasOperator)
	{
		justNumber = true;
		result = symbols[0]->value();
		return true;
	}

	/*for (auto it : symbols)
	{
		if(it->isNumber())
			std::cout << it->value() << std::endl;
		else
			std::cout << (char)it->value() << std::endl;
	}*/

	return true;
}

bool Interpreter::createOrderedTokenList(std::vector<Symbol*> symbols, std::vector<NonChar*>& tokens)
{
	//std::cout << operation_order.find(43)->second << std::endl;

	while (true)
	{
		int currentOperation = 0;
		bool foundOperator = false;

		for (int i = 0; i < symbols.size(); i++)
		{
			if (!symbols[i]->isNumber())
			{
				if (currentOperation == 0) 
					currentOperation = i;

				foundOperator = true;
				if (operation_order.find((char)symbols[i]->value())->second > operation_order.find((char)symbols[currentOperation]->value())->second)
					currentOperation = i;
			}
		}

		if (foundOperator)
		{
			switch ((int)symbols[currentOperation]->value())
			{
			case '+':
				tokens.push_back(new AddToken(symbols[currentOperation - 1]->value(), symbols[currentOperation + 1]->value()));
				break;

			case '-':
				tokens.push_back(new SubToken(symbols[currentOperation - 1]->value(), symbols[currentOperation + 1]->value()));
				break;

			case '*':
				tokens.push_back(new MulToken(symbols[currentOperation - 1]->value(), symbols[currentOperation + 1]->value()));
				break;

			case '/':
				if (symbols[currentOperation + 1]->value() == 0) {
					DIVIDE_BY_ZERO;
				}
				tokens.push_back(new DivToken(symbols[currentOperation - 1]->value(), symbols[currentOperation + 1]->value()));
				break;

			case '^':
				tokens.push_back(new ExpToken(symbols[currentOperation - 1]->value(), symbols[currentOperation + 1]->value()));
				break;

			case '_':
				if (symbols[currentOperation - 1]->value() == 0) {
					DIVIDE_BY_ZERO;
				}
				if (symbols[currentOperation + 1]->value() < 0) {
					IMAGINARY_NUMBERS;
				}

				tokens.push_back(new RootToken(symbols[currentOperation - 1]->value(), symbols[currentOperation + 1]->value()));
				break;

			default:

				break;
			}

			symbols.erase(symbols.begin() + currentOperation + 1);
			symbols[currentOperation] = new Number(tokens[tokens.size() - 1]->value());
			symbols.erase(symbols.begin() + currentOperation - 1);
		}
		else {
			break;
		}

		foundOperator = false;
	}

	return true;
}