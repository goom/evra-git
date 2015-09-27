#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include <algorithm>
#include "constants.h"
#include "pugixml.h"
using namespace std;

struct Token
{
	Token() : kind(0), value(0), name("") { }

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

	Token StrHandler(string& s);
	void Clear(string& s);
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
double calc_proc(string& s);
double calc_proc(TokenStream& ts, bool initial = false);
//Calc.cpp


//Track.cpp
int track_proc(TokenStream& ts);
//Track.cpp


//Notes.cpp
int notes_proc(TokenStream& ts);
//Notes.cpp


//Character.cpp
class Character;
//Character.cpp

