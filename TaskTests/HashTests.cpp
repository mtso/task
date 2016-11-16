// Visual Studio Boilerplate
#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include "Utilities/Sha1.h"
#include <string>

// Namespace of Assert::
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskTests // Testing Project namespace
{
	TEST_CLASS(HashTests) // Groups the method tests together
	{
	public:

		TEST_METHOD(Sha1_ATest)
		{
			std::string input = "A Test";
			std::string expected = "8f0c0855915633e4a7de19468b3874c8901df043";
			std::string actual = task::sha_1(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Sha1_QuickFox)
		{
			std::string input = "The quick brown fox jumped over a lazy dog.";
			std::string expected = "e26d11465308c2c78f0914c69f2001cb3c454c9f";
			std::string actual = task::sha_1(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Sha1_LongParagraph)
		{
			std::string input = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque dignissim tellus non lacus aliquet pulvinar. Donec at orci turpis. Etiam consequat, sapien ut ornare tristique, erat mauris consectetur turpis, nec ullamcorper lacus nibh eu nulla. Aliquam nunc nisl, condimentum sit amet faucibus eu, maximus eu sem. In eu risus elit. Duis vitae lacinia neque. Cras ut volutpat quam. Fusce posuere augue nec arcu sagittis rutrum. Aliquam ac convallis est. Interdum et malesuada fames ac ante ipsum primis in faucibus. Phasellus volutpat, lorem eget tincidunt tincidunt, sapien dolor elementum mauris, ut tincidunt leo est a sapien. Aenean metus arcu, dignissim a viverra ut, fringilla at felis. Suspendisse ut rhoncus ipsum, eget blandit velit.";
			std::string expected = "2a78301bc7fba267541a198282b9876231771d9b";
			std::string actual = task::sha_1(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Sha1_Blank)
		{
			std::string input = "";
			std::string expected = "da39a3ee5e6b4b0d3255bfef95601890afd80709";
			std::string actual = task::sha_1(input);
			Assert::AreEqual(expected, actual);
		}
	};
}
