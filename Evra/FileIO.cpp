#include "main.h"
#include "pugixml.h"
using namespace pugi;

xml_document xmldata;

namespace
{
	//Just so the document doesn't get deleted. Or maybe it does.
}

void load()
{
	try
	{
		static xml_parse_result r = xmldata.load_file("Data.txt");

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