#include "main.h"

namespace
{
	mt19937 rng;
	int STATE;
}


int Keywords::inList(int i)
{
	for (auto &x : l)
	{
		if (x == i)
			return 1;
	}

	return 0;
}

void Keywords::add(int i)
{
	l.push_back(i);
}

void Keywords::remove(int x)
{
	for (int i = 0; i < l.size(); i++)
	{
		if (l.at(i) == x)
		{
			l.erase(l.begin() + i);
			return;
		}
	}
}

long long genID()
{
	static long long x = 0;
	return x++;
}

int State(int i)
{
	if (STATE == i)
		return 1;
	else
		return 0;
}

int State()
{
	return STATE;
}

void SetState(int i)
{
	STATE = i;
}

void init_utilities()
{
	rng.seed(time(NULL));
	SetState(States::MAIN);
	load();
}

string prompt()
{
	switch(State())
	{
	case States::MAIN:
		return string("Main> ");
	case States::CALC:
		return string("Calc> ");
	case States::TRACKER:
		return string("Trck> ");
	case States::TEST:
		return string("Test> ");
	default:
		return string("> ");
	}
}


int random(int hi, int lo)
{
	uniform_int_distribution<uint32_t> distro(0, (hi - lo));
	return distro(rng) + lo;
}

int roll(int left, int right)
{
	int sum = 0;
	int single = 0;
	int neg = 0;

	if (left < 0)
		neg = 1;

	for (int i = 0; i < left; i++)
	{
		single = random(right);
/*		if (single == right)
		{
			cout << "Critical on d" << right << endl;
			//critical
		}
		else if (single == 1)
		{
			cout << "Fumble on d" << right << endl;
			//fumble
		}*/
		sum += single;
		single = 0;
	}

	if (neg)
		return -sum;

	return sum;
}