#pragma once


namespace States
{
	constexpr int CALC = 1;
	constexpr int TRACKER = 2;
	constexpr int MAIN = 3;
}

namespace Global
{
	namespace //Utility
	{
		constexpr short LO = 0;
		constexpr short LOW = LO;
		constexpr short MIN = LO;
		constexpr short HI = 1;
		constexpr short HIGH = HI;
		constexpr short MAX = HI;
	}

	namespace //Character Sheet
	{
		namespace //Stats
		{
			constexpr int STR = 0;
			constexpr int STRENGTH = STR;

			constexpr int DEX = 1;
			constexpr int DEXTERITY = DEX;

			constexpr int WIS = 2;
			constexpr int WISDOM = WIS;

			constexpr int INT = 3;
			constexpr int INTELLIGENCE = INT;

			constexpr int CON = 4;
			constexpr int CONSTITUTION = CON;

			constexpr int CHA = 5;
			constexpr int CHARISMA = CHA;
		}
	}
}

namespace Tokens
{
	namespace //Global tokens
	{
		constexpr int unknown = 0;
		constexpr int quit = 1;
		constexpr int number = 2;
		constexpr int skip = 3;
		constexpr int eof = 4;
		constexpr int full_quit = 5;
		constexpr int sort = 6;
		constexpr int name = 7;
		constexpr int clear = 8;
		constexpr int init = 9;
		constexpr int remove = 10;
		constexpr int reset = 11;
	}

	namespace //Calc
	{
		constexpr int dice = 100;
		constexpr int let = 101;
	}

	namespace //Main
	{
		constexpr int calc = 200;
		constexpr int track = 201;
		constexpr int state = 202;
	}

	namespace //Track
	{
		constexpr int list = 300;
		constexpr int add = 301;
		constexpr int reinit = 302;
		constexpr int unsort = 303;
	}
}