#pragma once
#include <iostream>

#define INTERPRETER_ERROR std::cout << "+++ INTERPRETER: "
#define INTEGER_ERROR std::cout << "+++ INTEGER: "
#define MATHEMATICAL_ERROR	std::cout << "+++ MATH: "

#define UNKNOWN_CHAR_ERROR(x)		INTERPRETER_ERROR	<< "Unknown character <" << (x) << "> found in string +++" << std::endl; return false
#define SYMBOL_LIST_ERROR			INTERPRETER_ERROR	<< "Failed to create Symbol list +++" << std::endl; return false
#define TOKEN_LIST_ERROR			INTERPRETER_ERROR	<< "Failed to create Token list +++" << std::endl; return false
#define TOO_MANY_OPERATORS			INTERPRETER_ERROR	<< "Found multiple operators in sequence +++" << std::endl; return false
#define ILLEGAL_OPERATOR_POSITION	INTERPRETER_ERROR	<< "An operator was found in an illegal position +++" << std::endl; return false

#define INTEGER_TOO_BIG(x)			INTEGER_ERROR		<< "Integer <" << (x) << "> cannot be converted to int +++" << std::endl; return false;
#define ENDS_ON_DECIMAL_POINT		INTEGER_ERROR		<< "Integers cannot end with a decimal point +++" << std::endl; return false

#define DIVIDE_BY_ZERO				MATHEMATICAL_ERROR	<< "Division by zero +++" << std::endl; return false
#define IMAGINARY_NUMBERS			MATHEMATICAL_ERROR	<< "Imaginary numbers are not supported +++" << std::endl; return false