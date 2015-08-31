#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include "constants.h"
using namespace std;

constexpr short DEBUG = 1;

struct Token
{
	int kind;
	double value;
	string name;
	Token(int ch) :kind(ch), value(0) { }
	Token(int ch, double val) :kind(ch), value(val) { }
	Token(int ch, string st) :kind(ch), name(st) { }
};

//Token.cpp
class TokenStream
{
protected:
	bool full;
	Token buffer;
public:
	TokenStream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	Token(*TokenRef)(string& s);
	void Init(Token(*p)(string&), string& s);
	void ignore(char);
};
//Token.cpp


//Util.cpp
int roll(int left, int right);
int random(int hi, int lo = 1);
void init_utilities();
int State(int i);
int State();
void SetState(int i);
string prompt();
//Util.cpp


//Calc.cpp
double calc_proc(TokenStream& ts, string& s, bool b = false);

struct Variable
{
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};
//Calc.cpp


//Track.cpp
int track_proc(TokenStream& ts, string& s);
//Track.cpp

//Main.cpp
int main_proc(TokenStream& ts, string& s);
//Main.cpp