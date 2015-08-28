#include "main.h"

int main()
{
	try
	{
		init_utilities();

		//calculate();
		cout << Global::CON << endl;
		
		
		cin.clear();
		cout << "Press enter to continue...";
		getchar();
		return 0;
	}
	catch (exception& e)
	{
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >> c&& c != ';');
		return 1;
	}
	catch (...)
	{
		cerr << "exception\n";
		char c;
		while (cin >> c && c != ';');
		return 2;
	}
}