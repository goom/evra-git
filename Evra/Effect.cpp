#include "main.h"

using namespace Global;
using namespace pugi;

bool operator==(Effect& x, Effect& y)
{
	if (x.sName == y.sName)
		return true;
	return false;
}

int EffectList::has(Effect &e)
{
	int i = 0;

	for (auto &x : l)
		if (x == e)
			i++;

	return i;
}

int EffectList::has(string &s)
{
	int i = 0;

	for (auto &x : l)
		if (x.sName == s)
			i++;

	return i;
}

xml_node EffectList::getEffect(string &s)
{
	for (auto x : l)
	{
		if (x.sName == s)
			return x.oEffect;
	}
}

vector<xml_node> EffectList::findEffects(int id)
{
	vector<xml_node> nodes;

	for (auto &x : l)
	{
		for (xml_node &n : x.oEffect)
		{
			switch (id)
			{
			case EFFECT_Proficiency:
				if (n.name() == "Proficiency")
					nodes.push_back(n);
				break;
			case EFFECT_ModValue:
				if (n.name() == "ModValue")
					nodes.push_back(n);
				break;
			case EFFECT_Resist:
				if (n.name() == "Resist")
					nodes.push_back(n);
				break;
			case EFFECT_Advantage:
				if (n.name() == "Advantage")
					nodes.push_back(n);
				break;
			}
		}
	}

	return move(nodes);
}

void EffectList::addEffect(string &s)
{
	Effect x;
	x.sName = s;
	x.oEffect = xmldata.child("Effects").find_child_by_attribute("Effect", "name", s.c_str());
}

void EffectList::addEffect(Effect &e)
{
	l.push_back(e);
}

void EffectList::addEffect(xml_node &n)
{
	Effect x;
	x.sName = n.attribute("name").value();
	x.oEffect = n;
	l.push_back(x);
}

