#include "main.h"

namespace
{
	typedef mt19937 RNG;
	uint32_t seed_value;
	RNG rng;
}

void init_utilities()
{
	rng.seed(seed_value);
}

void printDebug(stringstream& db)
{
	if(DEBUG)
		cout << db.str() << endl;
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
	for (int i = 0; i < left; i++)
	{
		single = random(right);
		if (single == right)
		{
			//critical
		}
		else if (single == 1)
		{
			//fumble
		}
		sum += single;
		single = 0;
	}

	return sum;
}