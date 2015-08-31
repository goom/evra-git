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
				ts.Assign(CalcToken);
				t = ts.get();
				if (t.kind == eof)
				{
					SetState(States::CALC);
				}
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
			default:
				switch (State())
				{
				case States::TRACKER:
					track_proc(ts, s);
					break;
				case States::CALC:
					calc_proc(ts, s);
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

Token MainToken(string &s)
{
	using namespace Tokens;
	if (s == "quit" || s == "q" || s == "exit") return Token(quit);
	if (s == "qq") return Token(full_quit);
	if (s == "calc") return Token(calc);
	if (s == "state") return Token(state);
	if (s == "track" || s == "tracker") return Token(track);
	return Token(unknown);
}