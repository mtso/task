// FileStore.h
// Task
// CIS 22C F2016: Jinzhu Shen

#ifndef TASK_FILESTORE_H
#define TASK_FILESTORE_H

#include <string>
#include <vector>

using std::string;
using std::vector;
#include "EntryManager.h"

namespace task {

    class FileStore {

    private:

        EntryManager *visitor;

        // extract user from file path
        string getUser(const string& filePath);
        const string& getHeader();
        void split(const string &str, const string& delim, vector<string>& fileds);

    public:

        FileStore(EntryManager *visitor);

        bool load(const string& filePath);
        // Proposed new interface: bool load(const string& filePath, vector<TaskEntry *> tasks);
        bool store(const string& filePath);
        // Proposed new interface: bool store(const string& filePath, vector<TaskEntry *> tasks);
    };

}
#endif