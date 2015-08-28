#include "main.h"
#include "pugixml.h"
using namespace pugi;

/* For future reference
int save(Actor *a)
{
	xml_document doc;
	xml_node n;

	n = doc.append_child("SAVE");
		n.append_attribute("VER");
		n.attribute("VER") = 1;
		n = n.append_child("NAME");
			n = n.append_child(node_pcdata);
				n.set_value(a->getName().c_str());
				n = n.parent().parent();
		n = n.append_child("XP");
				n.append_attribute("LVL");
				n.attribute("LVL") = a->getStat(LEVEL);
				n = n.append_child(node_pcdata);
					n.set_value(to_string(a->getStat(XP)).c_str());
					n = n.parent().parent();
		n = n.append_child("STATS");
			n = n.append_child("STRENGTH");
				n = n.append_child(node_pcdata);
					n.set_value(to_string(a->getStat(STR)).c_str());
					n = n.parent().parent();
			n = n.append_child("DEXTERITY");
				n = n.append_child(node_pcdata);
					n.set_value(to_string(a->getStat(DEX)).c_str());
					n = n.parent().parent();
			n = n.append_child("INTELLIGENCE");
				n = n.append_child(node_pcdata);
					n.set_value(to_string(a->getStat(INT)).c_str());
					n = n.parent().parent();
			n = n.append_child("WISDOM");
				n = n.append_child(node_pcdata);
					n.set_value(to_string(a->getStat(WIS)).c_str());
					n = n.parent().parent();
			n = n.append_child("CHARISMA");
				n = n.append_child(node_pcdata);
					n.set_value(to_string(a->getStat(CHA)).c_str());
					n = n.parent().parent();
			n = n.append_child("CONSTITUTION");
				n = n.append_child(node_pcdata);
					n.set_value(to_string(a->getStat(CON)).c_str());
					n = n.parent().parent();

	doc.save_file("save.xml", "\t", format_default | format_no_declaration);

	return 1;
}
*/