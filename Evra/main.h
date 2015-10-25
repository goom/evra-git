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
extern pugi::xml_document xmldata;
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


//Effect.cpp
struct Effect
{
	string sName;
	Keywords oKeys;
	pugi::xml_node oEffect;

	Effect() { }
	friend bool operator==(Effect& x, Effect& y);
};

class EffectList
{
public:
	vector<Effect> l;

	int has(Effect &e);
	int has(string &s);
	pugi::xml_node getEffect(string &s);
	vector<pugi::xml_node> findEffects(int id);
	void addEffect(string &s);
	void addEffect(Effect &e);
	void addEffect(pugi::xml_node &n);
};
//Effect.cpp


//Character.cpp
struct Stat
{
	long long val;
	string name;

	Stat() :val(0), name("") { }
	Stat(long long x, string &s) :val(x), name(s) { }
	Stat(string s) :val(0), name(s) { }
	Stat(Stat& s) { val = s.val; name = s.name; }
	Stat operator=(const Stat& s) { val = s.val; name = s.name; return *this; }
	Stat operator=(const string &s) { val = 0; name = s; return *this; }
};
class Character
{
	string sName;
	vector<Stat> vStats;
	Stat& findStat(const string &s);
	int hasStat(const string &s);

	string sRace, sClass;
	pugi::xml_node oRace, oClass;

	Keywords oKeys;
	EffectList oEffects;

	//Inventory, Effects
	//Personality Traits
	//Ideals, Bonds, Flaws

public:
	Character();
	
	int proficiencyBonus();
	int proficient(string &s);
	Stat getStat(string &s);
	long getStatValue(string &s);
	int getStatMod(string &s);
	//int savingThrow(int stat, Packet &p);
	//int skillCheck(int skill, SkillPacket &p);
};
//Character.cpp


//CharacterCreation.cpp
Character createCharacter();
//CharacterCreation.cpp


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