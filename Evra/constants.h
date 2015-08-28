#pragma once



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