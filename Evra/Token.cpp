#include "main.h"

/*
Program flow:

The string gets passed to calculate(), which then attempts to break the string into tokens.
The tokens get passed up the chain: expression -> term -> primary
Each one either recursevely calling the chain, or return a value back down the chain.

*/



namespace
{
	const char let = 'L';
	const char quit = 'Q';
	const char number = '8';
	const char name = 'a';
	const char dice = 'd';
	const char skip = '`';
	const char eof = '\n';
	const string prompt = "> ";
	const string result = "= ";

	stringstream tstream;
	Token_stream ts;
	vector<Variable> names;
}

Token Token_stream::get()
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
			cout << "Bad value passed in Token_stream.get()" << ch << "(" << int(ch) << ")" << endl;
			ch = skip;
			return Token(skip);
		}
		if (isalpha(ch)) 
		{
			string s;
			s = ch;
			while (tstream.get(ch) && isalpha(ch)) s += ch;
			tstream.unget();
			if (s == "let") return Token(let);
			if (s == "quit" || s == "q" || s == "exit") return Token(quit);
			if (s == "d") return Token(dice);
			return Token(name, s);
		}
		cout << "Error: Bad token" << endl;
	}
}


void Token_stream::ignore(char c)
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


double get_value(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	cout << "get: undefined name " << s << endl;
	return 0;
}


void set_value(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) 
		{
			names[i].value = d;
			return;
		}
	cout << "set: undefined name " << s << endl;
}


bool is_declared(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}


double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != ')') cout << "')' expected" << endl;
		return d;
	}
	case '-':
		return -primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	case dice:
		ts.unget(t); //send 'd' back into buffer for term to handle
		return 1; //1d20 = d20
	case skip:
		return 0;
	case eof:
		cout << "EOF in primary" << endl;
		return 0;
	default:
		cout << "primary expected" << endl;
	}
}


double term()
{
	double left = primary();
	while (true) 
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '*':
			left *= primary();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) cout << "error, divide by zero" << endl;
			left /= d;
			break;
		}
		case 'd':
		{
			//get next token and roll
			return roll(left, primary());
			break;
		}
		case skip:
			return 0;
		case eof:
			return left;
		default:
			ts.unget(t);
			return left;
		}
	}
}


double expression()
{
	double left = term();

	while (true)
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		case skip:
			return 0;
		case eof:
			return left;
		default:
			ts.unget(t);
			return left;
		}
	}
}


double declaration()
{
	Token t = ts.get();
	if (t.kind != name) cout << "name expected in declaration" << endl;
	string name = t.name;
	if (is_declared(name)) cout << name << " declared twice" << endl;
	Token t2 = ts.get();
	if (t2.kind != '=') cout << "= missing in declaration of " << name << endl;
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}


double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration();
	case skip:
		return 0;
	case eof:
		cout << "Error: EOF in statement()" << endl;
		return 0;
	default:
		ts.unget(t);
		return expression();
	}
}

void calculate()
{
	string s;
	while (true) try
	{
		cout << prompt;
		getline(cin, s);
		tstream.clear();
		tstream.str(s);
		tstream.seekg(0, ios::beg);
		Token t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) 
	{
		cerr << e.what() << endl;
	}
}

