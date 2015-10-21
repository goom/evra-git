#include "main.h"

/*
Program flow:

The string gets passed to calculate(), which then attempts to break the string into tokens.
The tokens get passed up the chain: expression -> term -> primary
Each one either recursevely calling the chain, or return a value back down the chain.

*/

using namespace Tokens;

namespace
{
	struct Variable
	{
		string name;
		double value;
		Variable(string n, double v) :name(n), value(v) { }
	};

	vector<Variable> names;

	double declaration(TokenStream& ts);
	double expression(TokenStream& ts);
	double term(TokenStream& ts);
	double primary(TokenStream& ts);

	double get_value(string s)
	{
		for (int i = 0; i < names.size(); ++i)
			if (names[i].name == s) return names[i].value;
		cout << "get_value(): undefined name " << s << endl;
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
		for (int i = 0; i < names.size(); ++i)
			if (names[i].name == s) return true;
		return false;
	}


	double primary(TokenStream& ts)
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '(':
		{
			double d = expression(ts);
			t = ts.get();
			if (t.kind != ')') cout << "')' expected" << endl;
			return d;
		}
		case '-':
			return -primary(ts);
		case '+':
			return primary(ts);
		case number:
			return t.value;
		case name:
			return get_value(t.name);
		case dice:
			ts.unget(t); //send 'd' back into buffer for term to handle
			return 1; //1d20 = d20
		case skip:
		case quit:
			return 0;
		case eof:
			cout << "EOF in primary" << endl;
			return 0;
		default:
			cout << "primary expected" << endl;
			return 0;
		}
	}


	double term(TokenStream& ts)
	{
		double left = primary(ts);
		while (true)
		{
			Token t = ts.get();
			switch (t.kind)
			{
			case '*':
				left *= primary(ts);
				break;
			case '/':
			{
				double d = primary(ts);
				throw runtime_error("divide by zero in term()");
				left /= d;
				break;
			}
			case dice:
			{
				//get next token and roll
				return roll(left, primary(ts));
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


	double expression(TokenStream& ts)
	{
		double left = term(ts);

		while (true)
		{
			Token t = ts.get();
			switch (t.kind)
			{
			case '+':
				left += term(ts);
				break;
			case '-':
				left -= term(ts);
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


	double declaration(TokenStream& ts)
	{
		Token t = ts.get();
		if (t.kind != name) cout << "name expected in declaration" << endl;
		string name = t.name;
		if (is_declared(name)) cout << name << " declared twice" << endl;
		Token t2 = ts.get();
		if (t2.kind != '=') cout << "= missing in declaration of " << name << endl;
		double d = expression(ts);
		names.push_back(Variable(name, d));
		return 1;
	}
}

double calc_proc(const char* c)
{
	return calc_proc(string(c));
}

double calc_proc(string& s)
{
	TokenStream ts;
	ts.Clear(s);
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration(ts);
	case eof:
		cout << "Error: EOF in calculate()" << endl;
		return 1;
	default:
		ts.unget(t);
		return expression(ts);
	}
}

double calc_proc(TokenStream& ts, bool initial)
{
	try
	{
		double val = 1;
		Token t = ts.get();
		switch (t.kind)
		{
		case let:
			declaration(ts);
			break;
		case skip:
			break;
		case eof:
			cout << "Error: EOF in calculate()" << endl;
			break;
		default:
			ts.unget(t);
			val = expression(ts);
			if(initial)
				cout << "= " << val << endl;
			break;
		}
		return val;
	}
	catch (runtime_error& e) 
	{
		cerr << e.what() << endl;
	}
}