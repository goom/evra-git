#include "main.h"



namespace
{
	bool sorted = false;
	struct Track
	{
		Track() : name(""), initiative(0), hp(0) {}

		string name;
		int initiative;
		int hp;
	};

	vector<Track> l, l_sorted;

	struct
	{
		bool operator()(Track& a, Track& b)
		{
			return a.initiative > b.initiative;
		}
	} cSort;

	void List()
	{
		if (sorted)
		{
			if (l_sorted.size() <= 0)
			{
				cout << "No tracks to list." << endl;
				return;
			}
			int i = 0;
			for (auto c : l_sorted)
			{
				cout << i << ") " << c.name << " (Init " << c.initiative << ") " << c.hp << endl;
				i++;
			}
		}
		else
		{
			if (l.size() <= 0)
			{
				cout << "No tracks to list." << endl;
				return;
			}
			int i = 0;
			for (auto c : l)
			{
				cout << i << ") " << c.name << " (Init " << c.initiative << ") " << c.hp << endl;
				i++;
			}
		}
	}

	void Add(TokenStream& ts)
	{
		Token t;
		Track temp;
		while (true)
		{
			t = ts.get();
			switch (t.kind)
			{
			case Tokens::name:
				temp.name = t.name;
				break;
			case Tokens::number:
				temp.initiative = t.value;
				break;
			case Tokens::eof:
				cout << temp.name << " added." << endl;
				if (sorted)
					l_sorted.push_back(temp);
				else
					l.push_back(temp);
				return;
			default:
				cout << "Unknown value passed in Add()" << endl;
				return;
			}
		}
	}

	void EditTrack(TokenStream& ts)
	{
		Token t = ts.get();
		Track temp;
		int track = t.value;
		if (sorted)
		{
			if (t.value >= l_sorted.size())
			{
				cout << "Number in EditTrack() > number of elements in l_sorted" << endl;
				return;
			}
			temp = l_sorted[t.value];
		}
		else
		{
			if (t.value >= l.size())
			{
				cout << "Number in EditTrack() > number of elements in l" << endl;
				return;
			}
			temp = l[t.value];
		}
		t = ts.get();
		switch (t.kind)
		{
		case Tokens::number:
		case '-':
			ts.unget(t);
			temp.hp += calc_proc(ts);
			break;;
		case Tokens::clear:
			temp.initiative = temp.hp = 0;
			break;
		case Tokens::reinit:
		case Tokens::init:
			temp.initiative = calc_proc(ts);
			break;
		}
		if (sorted)
			l_sorted[track] = temp;
		else
			l[track] = temp;
	}
}

Token TrackToken(string& s)
{
	using namespace Tokens;
	if (s == "add") return Token(add);
	if (s == "list") return Token(list);
	if (s == "sort") return Token(Tokens::sort);
	if (s == "unsort") return Token(unsort);
	if (s == "reinit") return Token(reinit);
	if (s == "init") return Token(init);
	if (s == "clear") return Token(clear);
	return Token(name, s);	
}

int track_proc(TokenStream& ts, string& s)
{
	try
	{
		using namespace Tokens;
		ts.Init(TrackToken, s);
		Token t = ts.get();
		switch (t.kind)
		{
		case list:
			List();
			return 1;
		case Tokens::add:
			Add(ts);
			return 1;
		case Tokens::sort:
			l_sorted = l;
			std::sort(l_sorted.begin(), l_sorted.end(), cSort);
			sorted = true;
			List();
			return 1;
		case unsort:
			l = l_sorted;
			sorted = false;
			List();
			return 1;
		case number:
			ts.unget(t);
			EditTrack(ts);
			return 1;
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