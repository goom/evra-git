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

//Token.cpp
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


//FileIO.cpp
extern pugi::xml_node xmldata;
void load();
//FileIO.cpp

//Util.cpp
int roll(int left, int right);
int random(int hi, int lo = 1);
void init_utilities();
int State(int i);
int State();
long long genID();
void SetState(int i);
string prompt();

class Keywords
{
public:
	vector<short> l;

	int inList(int i); 
	void add(int i);
	void remove(int i);
};
//Util.cpp


//Character.cpp
struct Effect
{
	string type;
	pugi::xml_node me;
	pugi::xml_node *owner;
};
class Character
{
private:
	pugi::xml_document oData;
	vector<Effect> oEffects;

public:
	Character();
    Character& operator=(Character c) { oData.reset(c.oData); return *this; }


	int proficiencyBonus();
	int proficient(string &s);

	int hasEffect(string &s);
	int hasEffect(char *t);
	Effect& addEffect(pugi::xml_node &e, pugi::xml_node *own = NULL);

	pugi::xml_node& getStat(const string &s);
	long getStatValue(string &s);
	void setStatValue(string &s, long val);
	int getStatMod(string &s);

	void save();
	//int savingThrow(int stat, Packet &p);
	//int skillCheck(int skill, SkillPacket &p);
};
//Character.cpp


//Testing
void test_proc(TokenStream &ts);
//Testing


//Calc.cpp
double calc_proc(string s);
double calc_proc(const char* c);
double calc_proc(TokenStream& ts, bool initial = false);
double calcChar(const string s, Character &c);
//Calc.cpp


//Track.cpp
int track_proc(TokenStream& ts);
//Track.cpp


//Notes.cpp
int notes_proc(TokenStream& ts);
//Notes.cpp