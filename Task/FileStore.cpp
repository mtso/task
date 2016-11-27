// FileStore.cpp
// Task
// CIS 22C F2016: Jinzhu Shen

#include "FileStore.h"
#include <string.h>

#include <fstream>
#include <iostream>
using namespace std;

namespace task {

	string FileStore::getUser(const string& filePath) {
		vector<string> fields;
		split(filePath, "/-", fields);
		return fields[fields.size() - 1];
	}

	void FileStore::split(const string &str, const string& delim, vector<string>& fileds) {
		char *input = const_cast<char *>(str.c_str());
		char *next_token = nullptr;
		char *token = strtok_s(input, delim.c_str(), &next_token);
		while (token != nullptr) {
			// remove double quotes, if any
			string field(token);
			if (field.length() > 1
				&& field[0] == '\"'
				&& field[field.length() - 1] == '\"') {
				field = field.substr(1, field.length() - 2);
			}
			fileds.push_back(field);

			token = strtok_s(nullptr, delim.c_str(), &next_token);
		}
	}

	const string& FileStore::getHeader() {
		static const string header("Unique ID,Time Created,Time Due,Description,Status");
		return header;
	}

	//FileStore::FileStore(EntryManager *visitor)
	//	: visitor(visitor) {
	//}

	bool FileStore::load(const string& filePath) {
		ifstream input(filePath.c_str(), ifstream::in);

		if (!input) {
			return false;
		}

		string line;
		int i = 0;
		while (getline(input, line)) {
			// skip header line
			if (i == 0) {
				++i;
				continue;
			}

			vector<string> fields;
			split(line, ",", fields);

			// visitor->loadEntry();

			++i;
		}
		return true;
	}

	bool FileStore::store(const string& filePath) {
		ofstream output(filePath.c_str(), ofstream::out | ofstream::trunc);

		if (!output) {
			return false;
		}

		// header line
		output << getHeader() << endl;

		// TODO: visitor->getAllEntry();
		string id("b74c33f995843a5f53c256e196098fcce0338783");
		long time_created = 0l;
		long time_due = 0l;
		string description("Implement TaskEntry data model");
		// TaskEntryStatus status(BACKLOG);

		output << id << "," << time_created << "," << time_due << "\"" << description << "\"" << endl;

		return true;
	}
}