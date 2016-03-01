# evra-git
Just a self project

//17 Feb 16
Finally solved the getStatValue crap; more issues with extra whitespaces at the beginning or end of the pugi::char_t strings. That is annoying.

//16 Feb 16
Solved some problems, found some others. One of the data structures (oData or xmldata) needs to have its PCDATA notes trimmed() in order for string comparison to work...
Also, getStatValue is returning incorrect stat. (not checking through effects)

//1 Nov 15
Some inherint difference between pugixml::char_t* and string.c_str().... They don't return the same values, even though they appear the same.

//28 Oct 15
Almost completely rewrote Character class; heavy implentation of XML data.
-Need to add <Conditions> field to Effects, and an evaluateConditions() function to the Character class
-Need to finish the testing module and ensure that effect checking is working as intended

//5 Sep 15
Ceompleted Track mode;
-Delete a range of tracks
-Edit multiple tracks at once using comma seperated commands

//3 Sep 15
Added more functionality to the Track mode;
-Add multiple tracks at once
-Remove tracks
-Re-initialize all tracks at once
Added functionality to the token system;
-Allows for numbers in a name or string
	-Any number immediately following a sole 'd' will be treated as a separate number, not a part of the string (for rolling)

//31 Aug 15
Modified the TokenStream class for greater extensibility, setup for future program modes
Planned modes:
-Track
-Calc
-Main
-Search
-Play
-Note