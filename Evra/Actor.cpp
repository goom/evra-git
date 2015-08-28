#include "main.h"

Actor::Actor()
{
	name = "NONAME";
	level = 1;
	experience = 0;
	health_current = health_max = 10;

	str = dex = intel = wis = cha = con = 10;

	hit = defense = armor = 0;
}

Actor::Actor(string n)
{
	name = n;
	level = 1;
	experience = 0;
	health_current = health_max = 10;

	str = dex = intel = wis = cha = con = 10;

	hit = defense = armor = 0;
}

void Actor::attack(Packet *p)
{
	p->owner = this;

	p->damage = random(3, 10);

	p->hit = hit + random(1, 20);
}

void Actor::defend(Packet *p)
{
	p->post_hit = p->hit - defense;

	if (p->post_hit >= 10)
	{
		//crit?
		if (p->post_hit >= 20 || p->crit)
		{
			p->post_damage = (p->damage * 2) - armor;
			p->crit = 1;
		}
		p->post_damage = p->damage - armor;
		
		health_current -= p->post_damage;
		p->hit = 1;
	}
	else
	{
		p->hit = p->post_hit = 0;
		p->crit = 0;
		p->damage = p->post_damage =  0;
	}
}

int Actor::getStat(int stat, int flag)
{
	switch (stat)
	{
	case HP:
		if (flag == BASE || flag == COMPOSITE)
			return health_current;
		else
			return health_max;
	case STR:
		return str;
		break;
	case DEX:
		return dex;
		break;
	case INT:
		return intel;
		break;
	case WIS:
		return wis;
		break;
	case CHA:
		return cha;
		break;
	case CON:
		return con;
		break;
	case ARMOR:
		return armor;
		break;
	case DEFENSE:
		return defense;
		break;
	case HIT:
		return hit;
		break;
	case MULTI:
		return multi;
		break;
	case XP:
		return experience;
		break;
	case LVL:
		return level;
		break;
	default:
		cout << "No such value " << stat << " in getStat()" << endl;
		return -1;
	}

	return -1;
}

int Actor::getMod(int x, int flag)
{
	int mod = 0;
	if (x == STR || x == DEX || x == INT || x == WIS || x == CHA || x == CON)
	{
		int temp = getStat(x);
		// Query the effect list and apply mod
		if (temp < 10)
			mod = (5 - (temp / 2));
		else if (temp < 20)
			mod = (temp - 10) / 2;
		else
			mod = (temp - 10) / 3;
	}
	else
		cout << "invalid stat " << x << " in getMod()";

	return mod;
}
