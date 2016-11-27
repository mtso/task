// Visual Studio Boilerplate
#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include "FileStore.h"

// Namespace of Assert::
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileIoTests // Testing Project namespace
{
    TEST_CLASS(FileIoTests) // Groups the method tests together
    {
    public:

        TEST_METHOD(TestGetUser) 
        {
            task::FileStore fileIo(nullptr);
            Assert::AreEqual(true, fileIo.load("../.task/tasklog-mryagni"));
        }
    };
}
