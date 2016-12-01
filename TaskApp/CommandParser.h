// CommandParser.h
// TaskApp
// CIS 22C F2016: Matthew Tso

#ifndef TASKAPP_COMMANDPARSER_H
#define TASKAPP_COMMANDPARSER_H

#include <string>
using namespace std;

#include "AppCommand.h"

namespace taskapp {

	class CommandParser
	{
	private:
		int firstOccurenceOf(const char& character, const string& in_string);
		int lastOccurenceOf(const char& character, const string& in_string);

	public:
		AppCommand parseCommandFrom(const string& raw_input);
		string parseArgumentsFrom(const string& raw_input);
	};

}

#endif