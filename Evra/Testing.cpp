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
		
		characterTest.setName(sI);
		characterTest.setRace(string("Dwarf"));
		characterTest.setRace(string("Hill Dwarf"), true);

		characterTest.save();
		cout << "Success?" << endl;
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