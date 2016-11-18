// Visual Studio Boilerplate
#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

// Include the header file of your class to be able to access its public functions
// #include "[ObjectName].h" where [ObjectMain] is the name of the header file of your class.


// Namespace of Assert::
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileIoTests // Testing Project namespace
{
    TEST_CLASS(FileIoTests) // Groups the method tests together
    {
    public:

        TEST_METHOD(ExampleMethodTest)
        {
            // returns true if expected and actual are equivalent
            Assert::AreEqual(0, 0);
        }

        // Once test methods are set up,
        // run the tests through the menubar:
        // Test > Run > All Tests
        //
        // This opens the test explorer
        // Checkmark means that all Assert:: 
        // testing statements have passed

    };
}