#include "main.h"

using namespace Tokens;

namespace
{
	stringstream tstream;
}

Token TokenStream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}
	char ch;
	tstream >> ch;
	if (tstream.fail())
		ch = eof;
	switch (ch)
	{
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case ',':
	case '!':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		tstream.unget();
		double val;
		tstream >> val;
		return Token(number, val);
	}
	case eof:
		return Token(eof);
	default:
		if (ch < 1)
		{
			cout << "Bad value passed in TokenStream.get()" << ch << "(" << int(ch) << ")" << endl;
			ch = skip;
			return Token(eof);
		}
		if (isalpha(ch))
		{
			string s, test;
			s = ch;
			while (tstream.get(ch))
			{
				if (isalpha(ch))
					s += ch;
				else
					if (isalnum(ch))
					{
						if (s == "d")
							break;
						s += ch;
					}
					else
						break;
			}
			tstream.unget();
			return StrHandler(s);
		}
		cout << "Error: Bad token" << endl;
		return Token(unknown);
	}
}

void TokenStream::Clear(string& s)
{
	tstream.clear();
	tstream.str(s);
	tstream.seekg(0, ios::beg);
	full = false;
}

void TokenStream::ignore(char c)
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	char ch;
	while (tstream >> ch)
		if (ch == c) return;
}

Token TokenStream::StrHandler(string &s)
{
	using namespace Tokens;
	if (s == "quit" || s == "q" || s == "exit") return Token(quit);
	if (s == "qq") return Token(full_quit);
	if (s == "calc") return Token(calc);
	if (s == "state") return Token(state);
	if (s == "track" || s == "tracker") return Token(track);
	if (s == "clear" || s == "cls") return Token(clear);
	if (s == "add") return Token(add);
	if (s == "list") return Token(list);
	if (s == "sort") return Token(Tokens::sort);
	if (s == "reinit") return Token(reinit);
	if (s == "init") return Token(init);
	if (s == "reset") return Token(reset);
	if (s == "remove" || s == "del" || s == "delete") return Token(Tokens::remove);
	if (s == "d") return Token(dice);
	if (s == "let") return Token(let);
	if (s == "create") return Token(create);
	return Token(name, s);
}