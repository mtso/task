// Visual Studio Boilerplate
#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include "FileStore.h"
#include "TaskEntryStatus.h"
using namespace task;

// Namespace of Assert::
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileIoTests // Testing Project namespace
{
    TEST_CLASS(FileIoTests) // Groups the method tests together
    {
    public:

        TEST_METHOD(TestLoadAndStore) 
        {
            FileStore fileIo;
            std::vector<TaskEntry> tasks;

            string user("test");
            string description("Test task");
            uint64_t time_created = 1479694012629l;
            uint64_t time_due = 1480298812629l;
            TaskEntryStatus status = TaskEntryStatus::BACKLOG;
            TaskEntry task(user, description, time_created, time_due, status);

            tasks.push_back(task);

            Assert::AreEqual(true, fileIo.store("..\\.task\\tasklog-test", tasks));

            std::vector<TaskEntry> loadedTasks;
            Assert::AreEqual(true, fileIo.load("..\\.task\\tasklog-test", loadedTasks));
            Assert::AreEqual((size_t) 1, loadedTasks.size());
            Assert::AreEqual(user, loadedTasks[0].getCreator());
            Assert::AreEqual(description, loadedTasks[0].getDescription());
            Assert::AreEqual(time_created, loadedTasks[0].getTimeCreatedMs());
            Assert::AreEqual(time_due, loadedTasks[0].getTimeDueMs());
            Assert::AreEqual(string("backlog"), getStatusString(loadedTasks[0].getStatus()));

            std::vector<TaskEntry> emptyTasks;
            Assert::AreEqual(true, fileIo.store("..\\.task\\tasklog-test", emptyTasks));
        }
    };
}
