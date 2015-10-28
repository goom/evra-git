#include "main.h"

namespace
{
	Character characterTest;

	void makeCharacter()
	{
		string sI;
		long iI;
		double dI;
	}
}

void test_proc(TokenStream &ts)
{
	using namespace Tokens;
	Token t;
	t = ts.get();
	switch (t.kind)
	{
		case make:
			makeCharacter();
			break;
	default:
		return;
	}
}