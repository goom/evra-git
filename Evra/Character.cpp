#include "main.h"

using namespace Global;
namespace
{
	
}

int Character::proficiencyBonus()
{
	if (iLevel < 5)
		return 2;
	if (iLevel < 9)
		return 3;
	if (iLevel < 13)
		return 4;
	if (iLevel < 17)
		return 5;
	else
		return 6;
}

int Character::proficient(int id)
{
	switch (iClass)
	{
	case BARBARIAN:
		if (id == STR || id == CON)
			return 1;
	case BARD:
		if (id == DEX || id == CHA)
			return 1;
	case CLERIC:
		if (id == WIS || id == CHA)
			return 1;
	case DRUID:
		if (id == INT || id == WIS)
			return 1;
	case FIGHTER:
		if (id == STR || id == CON)
			return 1;
	case MONK:
		if (id == STR || id == DEX)
			return 1;
	case PALADIN:
		if (id == WIS || id == CHA)
			return 1;
	case RANGER:
		if (id == STR || id == DEX)
			return 1;
	case ROGUE:
		if (id == DEX || id == INT)
			return 1;
	case SORCERER:
		if (id == CON || id == CHA)
			return 1;
	case WARLOCK:
		if (id == WIS || id == CHA)
			return 1;
	case WIZARD:
		if (id == INT || id == WIS)
			return 1;
	default:
		return 0;
	}
}

int Character::getStat(int stat, int arg)
{
	switch (stat)
	{
	case STR:
		if (arg == COMP)
			return iStrength + 0;
		else
			return iStrength;
	case DEX:
		if (arg == COMP)
			return iDexterity + 0;
		else
			return iDexterity;
	case CON:
		if (arg == COMP)
			return iConstitution + 0;
		else
			return iConstitution;
	case INT:
		if (arg == COMP)
			return iIntelligence + 0;
		else
			return iIntelligence;
	case WIS:
		if (arg == COMP)
			return iWisdom + 0;
		else
			return iWisdom;
	case CHA:
		if (arg == COMP)
			return iCharisma + 0;
		else
			return iCharisma;

	}
}

int Character::getStatMod(int stat, int arg)
{
		return (getStat(stat, arg) - 10) / 2;
}

int Character::savingThrow(int stat)
{
	int dice, save;
	dice = save = 0;

	if (proficient(stat))
		save = proficiencyBonus();

	save += getStatMod(stat);

	dice = calc_proc("d20");

	return dice + save;
}