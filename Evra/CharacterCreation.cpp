#include "main.h"

namespace
{

}


Character createCharacter()
{
	Character newguy;
	int i = 0;
	string inp;

	cout << "This is a huge work in progress..." << endl;

	cout << "Select a race for your character. You have the following options:" << endl;
	for (const auto &node : xmldata.child("Races").children("Race"))
		cout << ++i << ") " << node.attribute("name").value() << endl;


	cout << "Ending here..." << endl;
	return newguy;
}