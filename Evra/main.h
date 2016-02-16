#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include <algorithm>
#include <cctype>
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
string trim(const string &s);

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

	// Returns the value of (Level -10) / 4 + 2
	int proficiencyBonus();

	// Compares s to the name of a skill, returns level of proficiency (1 is proficient, 2 is expert, 3 is master)
	int proficient(string &s);

	// Returns 1 is specified effect is stored in the oEffects list
	int hasEffect(string &s);
	int hasEffect(char *t);

	// Add an effect to the oEffects list. Returns a reference to that effect
	Effect& addEffect(pugi::xml_node &e, pugi::xml_node *own = NULL);

	// Clears oEffects list and rebuilds it based on race, class, actives
	void reloadEffects();

	pugi::xml_node getStat(const string &s);
	long getStatValue(string &s);
	void setStatValue(string &s, long val);
	int getStatMod(string &s);

	//Saves the character to save.xml
	void save();

	//Sets race to s. Set sub to true to set subrace.
	void setRace(string &s, bool sub = false);

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