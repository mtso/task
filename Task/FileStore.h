// FileStore.h
// Task
// CIS 22C F2016: Jinzhu Shen

#ifndef TASK_FILESTORE_H
#define TASK_FILESTORE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "TaskEntry.h"

namespace task {

    class FileStore {

    private:

        // extract user from file path
        string getUser(const string& filePath);
        const string& getHeader();
        void split(string str, const string& delim, vector<string>& fileds);

    public:

        bool load(const string& filePath, vector<TaskEntry>& tasks);
        bool store(const string& filePath, const vector<TaskEntry>& tasks);
    };

}
#endif