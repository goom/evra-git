#include "main.h"


int main()
{
	try
	{
		string s;
		TokenStream ts;
		init_utilities();

		while (true)
		{
			cout << prompt();
			getline(cin, s);

			using namespace Tokens;
			ts.Clear(s);
			Token t = ts.get();
			switch (t.kind)
			{
			case full_quit:
			case quit:
				return 0;
				break;
			case calc:
				t = ts.get();
				if (t.kind == eof)
					SetState(States::CALC);
				else
				{
					ts.unget(t);
					cout << "Calc = " << calc_proc(ts) << endl;
				}
				break;
			case state:
				cout << "Current state: " << State() << endl;
				break;
			case track:
				SetState(States::TRACKER);
				break;
			case clear:
				//I know shouldn't do this. Go die.
				system("cls");
				break;
			case test:
				SetState(States::TEST);
				break;
			default:
				ts.Clear(s);
				switch (State())
				{
				case States::TRACKER:
					track_proc(ts);
					break;
				case States::CALC:
					calc_proc(ts, true);
					break;
				case States::MAIN:
					switch (t.kind)
					{
					case test:
						test_proc(ts);
						break;
					default:
						cout << "No such command usable in main menu." << endl;
						break;
					}
					break;
				default:
					cout << "Unknown STATE" << endl;
					break;
				}
				break;
			}
		}
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