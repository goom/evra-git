#include "main.h"
#include "pugixml.h"
using namespace pugi;

xml_node xmldata;
xml_document xmldoc;

namespace
{
	//Just so the document doesn't get deleted. Or maybe it does.
}

void load()
{
	try
	{
		static xml_parse_result r = xmldoc.load_file("Data.xml");
		xmldata = xmldoc.child("Data");

		if (!r)
		{
			stringstream t;
			t << r.description() << " at offset " << r.offset;
			throw runtime_error(t.str());
		}
	}
	catch (exception &e)
	{
		cerr << e.what() << endl;
	}
	catch (...)
	{
		cerr << "unhandled exception in load()" << endl;
	}
}