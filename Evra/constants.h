#pragma once


namespace States
{
	constexpr short CALC = 1;
	constexpr short TRACKER = 2;
	constexpr short MAIN = 3;
}

namespace Global
{
	namespace //Utility
	{
		constexpr short LO = 0;
		constexpr short LOW = LO;
		constexpr short MIN = LO;
		constexpr short BASE = LO;
		constexpr short HI = 1;
		constexpr short HIGH = HI;
		constexpr short MAX = HI;
		constexpr short COMP = 2;
		constexpr short COMPOSITE = COMP;
	}

	namespace //Character Sheet
	{
		namespace //Classes
		{
			constexpr short BARBARIAN = 1;
			constexpr short BARD = 2;
			constexpr short CLERIC = 3;
			constexpr short DRUID = 4;
			constexpr short FIGHTER = 5;
			constexpr short MONK = 6;
			constexpr short PALADIN = 7;
			constexpr short RANGER = 8;
			constexpr short ROGUE = 9;
			constexpr short SORCERER = 10;
			constexpr short WARLOCK = 11;
			constexpr short WIZARD = 12;
		}
		namespace //Stats
		{
			constexpr short STR = 0;
			constexpr short STRENGTH = STR;

			constexpr short DEX = 1;
			constexpr short DEXTERITY = DEX;

			constexpr short WIS = 2;
			constexpr short WISDOM = WIS;

			constexpr short INT = 3;
			constexpr short INTELLIGENCE = INT;

			constexpr short CON = 4;
			constexpr short CONSTITUTION = CON;

			constexpr short CHA = 5;
			constexpr short CHARISMA = CHA;

			constexpr short HP = 6;
			constexpr short HEALTH = HP;

			constexpr short AC = 7;
			constexpr short ARMORCLASS = AC;
		}
		namespace //Skills
		{
			constexpr short ACROBATICS = 100;
			constexpr short ANIMALHANDLING = 101;
			constexpr short ARCANA = 102;
			constexpr short ATHLETICS = 103;
			constexpr short DECEPTION = 104;
			constexpr short HISTORY = 105;
			constexpr short INSIGHT = 106;
			constexpr short INTIMIDATION = 107;
			constexpr short INVESTIGATION = 108;
			constexpr short MEDICINE = 109;
			constexpr short NATURE = 110;
			constexpr short PERCEPTION = 111;
			constexpr short PERFORMANCE = 112;
			constexpr short PERSUASION = 113;
			constexpr short RELIGION = 114;
			constexpr short SLEIGHTOFHAND = 115;
			constexpr short STEALTH = 116;
			constexpr short SURVIVAL = 117;
		}
	}
}

namespace Tokens
{
	namespace //Global tokens
	{
		constexpr short unknown = 0; //unused
		constexpr short quit = 1;
		constexpr short number = 2;
		constexpr short skip = 3; //mostly unused
		constexpr short eof = 4;
		constexpr short full_quit = 5; //mostly unused
		constexpr short sort = 6;
		constexpr short name = 7;
		constexpr short clear = 8;
		constexpr short init = 9;
		constexpr short remove = 10;
		constexpr short reset = 11;
	}

	namespace //Calc
	{
		constexpr short dice = 100;
		constexpr short let = 101;
	}

	namespace //Main
	{
		constexpr short calc = 200;
		constexpr short track = 201;
		constexpr short state = 202;
		constexpr short notes = 203;
	}

	namespace //Track
	{
		constexpr short list = 300;
		constexpr short add = 301;
		constexpr short reinit = 302;
		constexpr short unsort = 303;
	}
}