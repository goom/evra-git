#include "main.h"

using namespace Global;
using namespace pugi;

namespace
{
	bool stop_feedback_loop = false;
}


Character::Character()
{
	xml_node &node = oData.append_child("Character");
	node.append_child("Name");
	node.append_child("Race");
	node.append_child("Stats");
	for (auto x : xmldata.child("Stats").children("Stat"))
		node.child("Stats").append_copy(x).remove_child("Short");
	node.append_child("Class");
	node.append_child("Traits");
	node.append_child("Feats");
	node.append_child("Items");
	node.append_child("Effects");
}

xml_node& Character::getStat(const string &s)
{
	return oData.child("Character").child("Stats").child(s.c_str());
}

int Character::proficiencyBonus()
{
	return (((calcChar(getStat("Level").child_value(), *this) - 1) / 4) + 2);
}

int Character::proficient(string &s)
{
	for (auto &x : oEffects)
		if (x.type == "Proficiency")
			for(auto &y : x.me.children("With"))
				if(y.child_value() == s.c_str())
					return 1;
	//Need to to have some way of check the <Against> keys
	//Possibly passing some sort of packet instead of a string?
	return 0;
}


long Character::getStatValue(string &s)
{
	long val = 0;
	val += calcChar(getStat(s).child_value(), *this);

	if (!stop_feedback_loop && hasEffect("Value"))
	{
		stop_feedback_loop = true;

		for (auto &x : oEffects)
			if (x.type == "Value")
				if (x.me.child_value("Stat") == s.c_str())
					val += calcChar(x.me.child_value("Value"), *this);
	}

	stop_feedback_loop = false;
	return val;
}

void Character::setStatValue(string &s, long val)
{
	for (auto &x : oData.child("Stats").children("Stat"))
		if (x.child("Name").value() == s)
		{
			x.child("Value").first_child().set_value(to_string(val).c_str());
			return;
		}
}

int Character::getStatMod(string &s)
{
		return (getStatValue(s) - 10) / 2;
}

void Character::save()
{
	if(!oData.save_file("save.xml", "\t", pugi::format_no_declaration | pugi::format_save_file_text | pugi::format_indent))
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