#pragma once

//Enum max (int) is ~2.1b

namespace States
{
	enum
	{
		CALC,
		TRACKER,
		MAIN,
		TEST,
	};
}

namespace Effects
{
	constexpr char Proficieny[] = "Proficiency";
	constexpr char Value[] = "Value";
	constexpr char Advantage[] = "Advantage";
	constexpr char Resist[] = "Resist";
	constexpr char AllowUse[] = "AllowUse";
	constexpr char AllowEquip[] = "AllowEquip";
}

namespace Global
{
	enum
	{
		//Normal Globals
		LO, LOW = LO, MIN = LO, BASE = LO,
		HI, HIGH = HI, MAX = HI,
		COMP, COMPOSITE = COMP,

		//Character Sheet
		STR, STRENGTH = STR,
		DEX, DEXTERITY = DEX,
		WIS, WISDOM = WIS,
		INT, INTELLIGENCE = INT,
		CON, CONSTITUTION = CON,
		CHA, CHARISMA = CHA,
		HP, HEALTH = HP,
		AC, ARMORCLASS = AC,
		SIZE,
		HEIGHT,
		WEIGHT,
		SPEED,

		//Misc
		BACKGROUND,
		ALIGNMENT,
		FEAT,
		TRAIT,
		PASSIVE,
		MAGIC, MAGICAL = MAGIC,
		PHYSICAL,
		ARCANE,
		DIVINE,
		RACE,
		CLASS,
		ITEM,

		//Damage Types
		BLUDGEONING, BLUNT = BLUDGEONING, BLUDGEON = BLUNT, CRUSH = BLUNT, CRUSHING = BLUNT,
		SLASHING, SLASH = SLASHING,
		PIERCING, PIERCE = PIERCING,
		FIRE, FLAME = FIRE, HEAT = FIRE,
		COLD, ICE = COLD,
		ELECTRIC, ELECTRICITY = ELECTRIC, LIGHTNING = ELECTRIC,
		FORCE,
		RADIANT, HOLY = RADIANT,
		NECROTIC, UNHOLY = NECROTIC,
		POISON,
		SONIC, THUNDER = SONIC, SOUND = SONIC,

		//Alignments
		TN, TRUENEUTRAL = TN,
		LN, LAWFULNEUTRAL = LN,
		CN, CHAOTICNEUTRAL = CN,
		NE, NEUTRALEVIL = NE,
		LE, LAWFULEVIL = LE,
		CE, CHAOTICEVIL = CE,
		NG, NEUTRALGOOD = NG,
		LG, LAWFULGOOD = LG,
		CG, CHAOTICGOOD = CG,

		//Effects
		EFFECT_Proficiency,
		EFFECT_ModValue,
		EFFECT_Resist,
		EFFECT_Advantage,
	};
}

namespace Tokens
{
	enum //Global tokens
	{
		unknown, //unused
		quit,
		number,
		skip, //mostly unused
		eof,
		full_quit, //mostly unused
		sort,
		name,
		clear,
		init,
		remove,
		reset,

		//Calc
		dice,
		let,

		//Main
		calc,
		track,
		state,
		notes,
		create,
		test,

		//Test
		make,

		//Track
		list,
		add,
		reinit,
		unsort,
	};
}