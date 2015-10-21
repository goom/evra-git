#include "main.h"

using namespace Global;

bool operator==(Effect& x, Effect& y)
{
	if (x.iID == y.iID || x.sName == y.sName)
		return true;
	return false;
}

int EffectList::inList(Effect &e)
{
	int i = 0;

	for (auto &x : l)
		if (x == e)
			i++;

	return i;
}

int EffectList::inList(long long id)
{
	int i = 0;

	for (auto &x : l)
		if (x.iID == id)
			i++;

	return i;
}

int EffectList::inList(string &s)
{
	int i = 0;

	for (auto &x : l)
		if (x.sName == s)
			i++;

	return i;
}

int EffectList::keyInList(int key)
{
	int i = 0;

	for (auto &x : l)
		if (x.oKeys.inList(key))
			i++;

	return i;
}