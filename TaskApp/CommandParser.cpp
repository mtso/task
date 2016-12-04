// CommandParser.cpp
// TaskApp
// CIS 22C F2016: Matthew Tso

#include "CommandParser.h"

namespace taskapp {

	int CommandParser::firstOccurenceOf(const char& character, const string& in_string)
	{
		for (int i = 0; i < (int)in_string.length(); i++) {
			if (in_string[i] == character) {
				return i;
			}
		}
		return -1;
	}
	int CommandParser::lastOccurenceOf(const char& character, const string& in_string)
	{
		int potential_index = -1;
		for (int i = 0; i < (int)in_string.length(); i++) {
			if (in_string[i] == character) {
				potential_index = i;
			}
		}
		return potential_index;
	}

	AppCommand CommandParser::parseCommandFrom(const string& raw_input)
	{
		string command = raw_input.substr(0, firstOccurenceOf(' ', raw_input));

		if (command == "list") {
			return CMD_LIST;
		}
		else if (command == "new") {
			return CMD_CREATE;
		}
		else if (command == "update") {
			return CMD_UPDATE;
		}
		else if (command == "delete") {
			return CMD_DELETE;
		}
		else if (command == "history") {
			return CMD_HISTORY;
		}
		else if (command == "undo") {
			return CMD_UNDO;
		}
		else if (command == "test") {
			return CMD_TEST;
		}
		else if (command == "quit") {
			return CMD_QUIT;
		}
		else if (command == "help") {
			return CMD_HELP;
		}
		else if (command == "search") {
			return CMD_SEARCH;
		}
		else {
			return CMD_UNRECOGNIZED;
		}
	}
	string CommandParser::parseArgumentsFrom(const string& raw_input)
	{
		// Example command:> create something
		// len: 16, space_index: 6, `something`: from index 7 and length of 9
		// 16 - 6 - 1 = 9
		int space_index = firstOccurenceOf(' ', raw_input);
		if (space_index == -1) {
			return "";
		}
		else {
			return raw_input.substr(space_index + 1, raw_input.length() - space_index - 1);
		}
	}
}