#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
using namespace std;

constexpr short DEBUG = 1;

//Util.cpp
int roll(int left, int right);
int random(int hi, int lo = 1);
void init_utilities();
//Util.cpp


//Token.cpp
void calculate();
double statement();
double declaration();
double expression();
double term();
double primary();

struct Token
{
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string st) :kind(ch), name(st) { }
};

class Token_stream
{
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

struct Variable
{
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};
//Token.cpp