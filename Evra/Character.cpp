#include "main.h"

using namespace Global;
using namespace pugi;

namespace
{
	bool stop_feedback_loop = false;
}


Character::Character()
{
	oData = oDoc.append_child("Character");
	oData.append_child("Name");
	oData.append_child("Race");
	oData.append_child("Subrace");
	oData.append_child("Stats");
	for (auto x : xmldata.child("Stats").children("Stat"))
		oData.child("Stats").append_copy(x);
	oData.append_child("Class");
	oData.append_child("Effects");
}

xml_node Character::getStat(const string &s)
{
	xml_node t = oData.child("Stats").find_child_by_attribute("id", s.c_str());
	if (t)
		return t;
	else
		for (auto &x : oData.child("Stats").children("Stat"))
			if (x.child_value("Name") == s.c_str())
				return x;
	
	throw runtime_error("No such stat in getStat");
	return t;
}

int Character::proficiencyBonus()
{
	return (((calcChar(getStat("LVL").child_value(), *this) - 1) / 4) + 2);
}

void Character::setRace(string &s, bool sub)
{
	int i = 1;

	if (sub)
	{
		for (auto &x : xmldata.child("Races").children("Race"))
		{
			for (auto &y : x.child("Subraces").children("Subrace"))
			{
				if (s == y.child_value("Name"))
				{
					if (oData.child("Subrace").first_child().type() == xml_node_type::node_pcdata)
						oData.child("Subrace").first_child().set_value(x.child_value("Name"));
					else
						oData.child("Subrace").append_child(xml_node_type::node_pcdata).set_value(y.child_value("Name"));
					reloadEffects();
					return;
				}
			}
		}
	}
	else
	{
		for (auto &x : xmldata.child("Races").children("Race"))
		{
			if (s == string(x.child_value("Name")))
			{
				if (oData.child("Race").first_child().type() == xml_node_type::node_pcdata)
					oData.child("Race").first_child().set_value(x.child_value("Name"));
				else
					oData.child("Race").append_child(xml_node_type::node_pcdata).set_value(x.child_value("Name"));
					if (s == oData.child_value("Race"))
				reloadEffects();
				return;
			}
		}
	}

	cout << "No such race... dumb dumb." << endl;
}

void Character::reloadEffects()
{
	oEffects.clear();
	Effect t;
	xml_node *e;

	for (auto &x : xmldata.child("Races").children("Race"))
	{
		if (x.child_value("Name") == oData.child_value("Race"))
		{
			for (auto &y : x.child("Passives").children("Passive"))
			{
				e = &xmldata.child("Passives").find_child_by_attribute("id", y.attribute("id").value());
				for (auto &z : e->children("Effect"))
				{
					t.type = z.attribute("type").value();
					t.me = z;
					t.owner = e;
					oEffects.push_back(t);
				}
			}

			//subrace
			for (auto &a : x.child("Subraces").children("Subrace"))
			{
				if (a.child_value("Name") == oData.child_value("Subrace"))
				{
					for (auto &b : a.child("Passives").children("Passive"))
					{
						e = &xmldata.child("Passives").find_child_by_attribute("id", b.attribute("id").value());
						for (auto &c : e->children("Effect"))
						{
							t.type = c.attribute("type").value();
							t.me = c;
							t.owner = e;
							oEffects.push_back(t);
						}
					}
					break;
				}
			}
			break;
		}
	}
	//load from other places?
}

int Character::proficient(string &s)
{
	for (auto &x : oEffects)
		if (x.type == "Proficiency")
			for(auto &y : x.me.children("With"))
				if(y.child_value() == s)
					return 1;
	//Need to to have some way of check the <Against> keys
	//Possibly passing some sort of packet instead of a string?
	return 0;
}


long Character::getStatValue(string &s)
{
	long val = 0;
	xml_node &temp = getStat(s);
	val += calcChar(temp.child_value("Value"), *this);

	if (!stop_feedback_loop && hasEffect("Value"))
	{
		stop_feedback_loop = true;

		for (auto &x : oEffects)
			if (x.type == "Value")
				if (x.me.child_value("Stat") == temp.attribute("id").value() || x.me.child_value("Stat") == temp.child_value("Name"))
					val += calcChar(x.me.child_value("Value"), *this);
	}

	stop_feedback_loop = false;
	return val;
}

void Character::setStatValue(string &s, long val)
{
	oData.child("Stat").find_child_by_attribute("id", s.c_str()).child("Value").first_child().set_value(to_string(val).c_str());
}

int Character::getStatMod(string &s)
{
		return (getStatValue(s) - 10) / 2;
}

void Character::save()
{
	if(!oDoc.save_file("save.xml", "\t", pugi::format_no_declaration | pugi::format_save_file_text | pugi::format_indent))
		cout << "Character save unsuccessful" << endl;
}

int Character::hasEffect(string &s)
{
	for (auto &x : oEffects)
		if (x.type == s)
			return 1;

	return 0;
}

int Character::hasEffect(char *t)
{
	return hasEffect(string(t));
}

Effect& Character::addEffect(xml_node &e, xml_node *own)
{
	//assumes that &e is a base node <Effect>
	Effect temp;
	temp.type = e.first_attribute().value();
	temp.owner = own;
	temp.me = e;

	oEffects.push_back(temp);
	return oEffects.back();
}

void Character::setName(string &s)
{
	if (oData.child("Name").first_child().type() == xml_node_type::node_pcdata)
		oData.child("Race").first_child().set_value(s.c_str());
	else
		oData.child("Name").append_child(xml_node_type::node_pcdata).set_value(s.c_str());
}