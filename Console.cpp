#include "Console.hpp"
#include "Interpreter.hpp"

#include <iostream>
#include <iomanip>

char* Console::input = new char[INPUT_BUFFER_SIZE];


void Console::run()
{
	while (true)			// Main loop, runs until process is terminated
	{
		awaitInput();		// Waits for input
		handleInput();		// Handles input
	}

	delete[] input;			// After process is terminated, release the pointer
}



void Console::awaitInput()
{
	std::cout << ">>>";										
	std::cin >> std::setw(INPUT_BUFFER_SIZE) >> input;		// Await input
}



void Console::handleInput()
{
	double result = Interpreter::interpret(input);
	std::cout << result << std::endl << std::endl;
}
