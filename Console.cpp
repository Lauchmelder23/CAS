#include "Console.hpp"
#include "Interpreter.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>

std::string Console::input = "";


void Console::run()
{
	while (true)			// Main loop, runs until process is terminated
	{
		awaitInput();		// Waits for input
		handleInput();		// Handles input
	}
}



void Console::awaitInput()
{
	std::cout << ">>>";										
	std::cin >> input;		// Await input
}



void Console::handleInput()
{
	for (char c : input)
	{
		c = tolower(c);
	}

	if (input == "help")
	{
		std::cout << "This is a CAS in the Windows Console. You can enter any valid mathematical expression and it will print the answer." << std::endl;
		std::cout << "This program follows PEMDAS, but does not support parantheses." << std::endl << std::endl;
		std::cout << "Any expression like <4-7+42.6*7> is valid. No need to put a <=>. The program can't solve for variables" << std::endl << std::endl;
		std::cout << "Available operations:" << std::endl;
		std::cout << "+ ~ Addition" << std::endl
			<< "- ~ Subtraction" << std::endl
			<< "* ~ Multiplication" << std::endl
			<< "/ ~ Division" << std::endl
			<< "^ ~ Exponents" << std::endl
			<< "_ ~ Roots" << std::endl << std::endl;
		std::cout << "You can use the following symbols as well: " << std::endl;
		std::cout << "a ~ Result of the last calculation" << std::endl
			<< "p ~ Pi" << std::endl
			<< "e ~ Euler's number" << std::endl << std::endl;
		return;
	}

	double result = Interpreter::interpret(input);
	std::cout << result << std::endl << std::endl;
}
