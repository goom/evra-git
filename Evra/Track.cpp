#include "main.h"

Token TrackToken(string& s)
{
	using namespace Tokens;
	if (s == "quit" || s == "q" || s == "exit") return Token(quit);
	if (s == "qq") return Token(full_quit);
	return Token(unknown);
}

int track_proc(TokenStream& ts, string& s, bool b)
{
	try
	{
		using namespace Tokens;
		ts.Init(TrackToken, s);
		Token t = ts.get();
		switch (t.kind)
		{
		case quit:
			return 0;
		case full_quit:
			return -1;
			break;
		default:
			cout << "No such type in track_proc()" << endl;
			return 1;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
}