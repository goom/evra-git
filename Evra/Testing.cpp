#include "main.h"

namespace
{
	void makeCharacter()
	{
		Character characterTest;
		string sI;
		long iI;
		double dI;

		cout << "Enter a name: ";
		cin >> sI;
		
		characterTest.setRace(string("Dwarf"));
		characterTest.setRace(string("Hill Dwarf"), true);
		cout << "You are a Hill Dwarf." << endl;

		cout << "You have " << characterTest.getStatValue(string("CON")) << " constitution." << endl;
	}
}

void test_proc(TokenStream &ts)
{
	using namespace Tokens;
	Token t;
	t = ts.get();
	switch (t.kind)
	{
	case create:
		makeCharacter();
		break;
	default:
		cout << "No command" << endl;
		return;
	}
}