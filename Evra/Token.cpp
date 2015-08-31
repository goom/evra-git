#include "main.h"

using namespace Tokens;

namespace
{
	stringstream tstream;
	TokenStream ts;
	vector<Variable> names;
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
			return Token(skip);
		}
		if (isalpha(ch))
		{
			string s;
			s = ch;
			while (tstream.get(ch) && isalpha(ch)) s += ch;
			tstream.unget();
			return TokenRef(s);
		}
		cout << "Error: Bad token" << endl;
	}
}

void TokenStream::Init(Token (*p)(string&), string& s)
{
	tstream.clear();
	tstream.str(s);
	tstream.seekg(0, ios::beg);
	TokenRef = p;
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