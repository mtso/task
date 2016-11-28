// FileStore.cpp
// Task
// CIS 22C F2016: Jinzhu Shen

#include "FileStore.h"
#include "TaskEntryStatus.h"

#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

namespace task {

    string FileStore::getUser(const string& filePath) {
        vector<string> fields;
        split(filePath, "\\/-", fields);
        return fields[fields.size() - 1];
    }

    void FileStore::split(string str, const string& delim, vector<string>& fileds) {
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

    bool FileStore::load(const string& filePath, vector<TaskEntry>& tasks) {
        string user = getUser(filePath);

        ifstream input(filePath.c_str(), ios::in);

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

            if (fields.size() >= 5) {
                uint64_t time_created;
                uint64_t time_due;
                stringstream converter;
                converter << fields[1];
                converter >> time_created;
                converter.clear();
                converter << fields[2];
                converter >> time_due;

                TaskEntryStatus status = getStatus(fields[4]);

                TaskEntry task(user, fields[3], time_created, time_due, status);
                tasks.push_back(task);

                ++i;
            }
        }
        input.close();

        return true;
    }

    bool FileStore::store(const string& filePath, const vector<TaskEntry>& tasks) {
        ofstream output(filePath.c_str(), ios::out | ios::trunc);

        if (!output) {
            return false;
        }

        // header line
        output << getHeader() << endl;

        int size = tasks.size();
        for (int i = 0; i < size; i++) {
            TaskEntry task = tasks[i];

            string id = task.getId();
            uint64_t time_created = task.getTimeCreatedMs();
            uint64_t time_due = task.getTimeDueMs();
            string status_str = getStatusString(task.getStatus());
            string description = task.getDescription();

            output << id << "," << time_created << "," << time_due << ",\"" << description << "\"," << status_str << endl;
        }

        output.close();

        return true;
    }
}