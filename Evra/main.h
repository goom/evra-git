#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include "defines.h"
using namespace std;

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

//Actor.cpp
class Actor;
void scene(Actor *player);
int combat(Actor *player, Actor *enemy);

struct Packet
{
	Actor *owner;
	//spell/effect/item owner as well

	int hit, damage, crit;
	int post_damage, post_hit;

	int dam_type;
};

class Actor
{
	string name;
	int health_current, health_max;
	int level, experience;

	int str, dex, intel, wis, cha, con;
	int defense, hit, multi, armor;


public:
	Actor();
	Actor(string n);
	~Actor() { }

	int getStat(int stat, int flag = COMPOSITE);
	int getMod(int x, int flag = COMPOSITE);
	string getName() { return name; }

	void defend(Packet *p);
	void attack(Packet *p);
};



//File Input/Output
int save(Actor *a);
Actor load(string path = "save.xml");
//Actor.cpp