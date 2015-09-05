#include "main.h"


namespace
{
	struct Track
	{
		Track() : name("NONAME"), initiative(0), hp(0), order(0) {}

		string name;
		int initiative;
		int hp;
		int order;
	};

	vector<Track> l, l_sorted;

	struct
	{
		bool operator()(Track& a, Track& b)
		{
			return a.initiative > b.initiative;
		}
	} cSort;

	void List(bool sorted = false)
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
				cout << c.name << " (Init " << c.initiative << ") " << c.hp << endl;
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
				cout << i + 1 << ") " << c.name << " (Init " << c.initiative << ") " << c.hp << endl;
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
				if (l.size() < 1)
					temp.order = 1;
				else
					temp.order = l.back().order + 1;
				break;
			case Tokens::number:
			case Tokens::dice:
				ts.unget(t);
				temp.initiative = calc_proc(ts);
				break;
			case ',':
				cout << temp.name << " added." << endl;
				l.push_back(temp);
				temp.initiative = 0;
				temp.name = "NONAME";
				break;
			case Tokens::eof:
				cout << temp.name << " added." << endl;
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
		int track = --t.value;
		if (t.value >= l.size())
		{
			cout << "Number in EditTrack() > number of elements in list" << endl;
			return;
		}
		temp = l[t.value];
		while (true)
		{
			t = ts.get();
			switch (t.kind)
			{
			case '(':
			case '+':
			case '-':
				ts.unget(t);
				temp.hp += calc_proc(ts);
				break;
			case Tokens::number:
			case Tokens::dice:
				ts.unget(t);
				temp.hp = calc_proc(ts);
				break;
			case Tokens::clear:
				temp.initiative = temp.hp = 0;
				break;
			case Tokens::reinit:
			case Tokens::init:
				temp.initiative = calc_proc(ts);
				break;
			case Tokens::remove:
				l.erase(l.begin() + track);
				return;
			case ',':
				l[track] = temp;
				t = ts.get();
				if (t.kind != Tokens::number)
				{
					cout << "Invalid commant format in EditTrack()" << endl;
					return;
				}
				track = --t.value;
				if (t.value >= l.size())
				{
					cout << "Number in EditTrack() > number of elements in list" << endl;
					return;
				}
				temp = l[track];
				break;
			case Tokens::eof:
				l[track] = temp;
				return;
			default:
				cout << "Unknown token passed to EditTrack()" << endl;
			}
		}
	}

	void ResetList()
	{
		for (auto& i : l)
			i.hp = i.initiative = 0;
	}

	void ListSort(bool un = true)
	{
		l_sorted = l;
		std::sort(l_sorted.begin(), l_sorted.end(), cSort);
		if (un)
			List(true);
	}

	void ReInit(TokenStream& ts)
	{
		string s;
		for (auto& i : l)
		{
			cout << "Enter initiative for " << i.name << ": ";
			getline(cin, s);
			i.initiative = calc_proc(s);
		}
	}

	void DelTrack(TokenStream& ts)
	{
		using namespace Tokens;
		Token t;
		vector<int> vals;
		vector<Track> temp;
		int iter = 0;
		while (true)
		{
			t = ts.get();
			switch (t.kind)
			{
			case eof:
				for (auto z : l)
				{
					if (find(vals.begin(), vals.end(), z.order) == vals.end())
						temp.push_back(z);
				}
				iter = 1;
				for (auto& z : temp)
					z.order = iter++;
				l = temp;
				ListSort(false);
				return;
			case ',':
				break;
			case number:
				vals.push_back(t.value);
				t = ts.get();
				if (t.kind == '-')
				{
					t = ts.get();
					if (t.kind == number)
					{
						for (int i = vals.at(vals.size() - 1) + 1; i <= t.value; i++)
						{
							vals.push_back(i);
						}
					}
					else
						ts.unget(t);
				}
				else
					ts.unget(t);
				break;
			default:
				cout << "Unknown token in DelTrack()" << endl;
				break;
			}
		}
	}
}

int track_proc(TokenStream& ts)
{
	try
	{
		using namespace Tokens;
		Token t = ts.get();
		switch (t.kind)
		{
		case list:
			List();
			break;
		case Tokens::add:
			Add(ts);
			break;
		case Tokens::sort:
			ListSort();
			break;
		case number:
			ts.unget(t);
			EditTrack(ts);
			break;
		case reset:
			ResetList();
			break;
		case Tokens::remove:
			DelTrack(ts);
			break;
		case init:
			ReInit(ts);
			break;
		default:
			cout << "No such command in TRCK." << endl;
			break;
		}
		return 1;
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
}