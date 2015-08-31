#include "main.h"


int main()
{
	try
	{
		string s;
		init_utilities();
		TokenStream ts;
		while (true)
		{
			cout << prompt();
			getline(cin, s);

			switch(State())
			{
			case States::MAIN:
				if (!main_proc(ts, s))
					return 1;
				break;
			case States::TRACKER:
			case States::CALC:
				switch (int(calc_proc(ts, s)))
				{
				case 0:
					SetState(States::MAIN);
					break;
				case -1:
					return 0;
					break;
				default:
					break;
				}
				break;
			default:
				cout << "Unknown STATE" << endl;
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

Token MainToken(string &s)
{
	using namespace Tokens;
	if (s == "quit" || s == "q" || s == "exit") return Token(quit);
	if (s == "qq") return Token(full_quit);
	if (s == "calc") return Token(calc);
	if (s == "state") return Token(state);
	return Token(unknown);
}

int main_proc(TokenStream& ts, string& s)
{
	try
	{
		using namespace Tokens;
		ts.Init(MainToken, s);
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
			{
				SetState(States::CALC);
				return 1;
			}
			else
			{
				s.erase(0, 5);
				cout << "Calc = " << calc_proc(ts, s, true) << endl;
			}
			break;
		case state:
			cout << "Current state: " << State() << endl;
			break;
		default:
			cout << "Unknown case in proc_main()" << endl;
			break;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
}