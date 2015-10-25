#include "main.h"

using namespace Global;
using namespace pugi;

namespace
{
	bool stop_feedback_loop = false;
}


Character::Character()
{
	//Create stats, level, stuff.
	vStats.push_back(Stat("Strength"));
	vStats.push_back(Stat("Dexterity"));
	vStats.push_back(Stat("Constitution"));
	vStats.push_back(Stat("Intelligence"));
	vStats.push_back(Stat("Wisdom"));
	vStats.push_back(Stat("Charisma"));
	vStats.push_back(Stat("AC"));

	vStats.push_back(Stat("Level"));
	vStats.push_back(Stat("Experience"));

	vStats.push_back(Stat("Height"));
	vStats.push_back(Stat("Weight"));
	vStats.push_back(Stat("Speed"));
	vStats.push_back(Stat("Age"));
}

Stat& Character::findStat(const string &s)
{
	for (auto &x : vStats)
	{
		if (x.name == s)
			return x;
	}

	throw runtime_error("No such stat" + s + " in findStat()");
}

 int Character::hasStat(const string &s)
{
	for (const auto &x : vStats)
	{
		if (x.name == s)
			return 1;
	}

	return 0;
}

int Character::proficiencyBonus()
{
	return (((findStat("Level").val - 1) / 4) + 2);
}

int Character::proficient(string &s)
{
	vector<xml_node> nodes;
	nodes = oEffects.findEffects(EFFECT_Proficiency);

	for (auto &z : nodes)
	{
		if (z.attribute("on").value() == s)
			return calc_proc(z.attribute("val").value());
	}
}

Stat Character::getStat(string &s)
{
	if (hasStat(s))
	{
		for (auto x : vStats)
			if (x.name == s)
				return x;
	}
	else
		cout << "No such stat in getStat()" << endl;
}

long Character::getStatValue(string &s)
{
	long val = 0;
	if (hasStat(s))
	{
		for (auto x : vStats)
			if (x.name == s)
				val += x.val;
	}

	if (!stop_feedback_loop)
	{
		stop_feedback_loop = true;
		vector<xml_node> nodes;
		nodes = oEffects.findEffects(EFFECT_ModValue);

		for (auto &z : nodes)
		{
			if (z.attribute("id").value() == s)
				val += calcChar(z.attribute("value").value(), *this);
		}
	}

	stop_feedback_loop = false;
	return val;
}

int Character::getStatMod(string &s)
{
		return (getStatValue(s) - 10) / 2;
}