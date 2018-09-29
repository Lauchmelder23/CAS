#pragma once
#include <math.h>

/////////////////////////////////////////////////////
/// \brief Abstract Token base class
///
/// A token contains an operation - this means it will
/// hold two numbers, as well as their result after
/// the according operation.
///
/////////////////////////////////////////////////////

class Token
{
public:
	virtual bool nonCharToken() = 0;
};








class NonChar : public Token
{
public:
	bool nonCharToken() override { return true; }
	double value() { return result; }

protected:
	double a, b, result;
};



class Symbol : public Token
{
public:
	bool nonCharToken() override { return false; }
	virtual bool isNumber() = 0;
	virtual double value() = 0;
};




class Operator : public Symbol
{
public:
	Operator(char _c)
	{
		c = _c;
	}

	bool isNumber() override { return false; }
	double value() { return c; }

private:
	char c;
};


class Number : public Symbol
{
public:
	Number(double _i)
	{
		i = _i;
	}

	bool isNumber() override { return true; }
	double value() { return i; }

private:
	double i;
};




class AddToken : public NonChar
{
public:
	AddToken(double _a, double _b)
	{
		a = _a;
		b = _b;

		result = a + b;
	}
};



class SubToken : public NonChar
{
public:
	SubToken(double _a, double _b)
	{
		a = _a;
		b = _b;

		result = a - b;
	}
};



class MulToken : public NonChar
{
public:
	MulToken(double _a, double _b)
	{
		a = _a;
		b = _b;

		result = a * b;
	}
};


class DivToken : public NonChar
{
public:
	DivToken(double _a, double _b)
	{
		a = _a;
		b = _b;

		result = a / b;
	}
};



class ExpToken : public NonChar
{
public:
	ExpToken(double _a, double _b)
	{
		a = _a;
		b = _b;

		result = pow(a, b);
	}
};


class RootToken : public NonChar
{
public:
	RootToken(double _a, double _b)
	{
		a = _a;
		b = _b;

		result = pow(b, 1.0 / a);
	}
};