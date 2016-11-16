// Main.cpp : Defines the entry point for the console application.
// TaskApp
// CIS 22C F2016: Matthew Tso

/**
 * An example of the static library usage in a console process
 */

#include <iostream>
#include <string>

#include "Example.h"
#include "TemplateExample.h"

#ifdef _WIN32 /* Windows-style */
#include "Utilities\Sha1.h"

#else         /* Xcode-style */
#include "Sha1.h"

#endif

int main(int argc, char* argv[])
{
	task::Example example;
	std::cout << "The smaller value between (1+1) and 1 is: "
		      << task::Min(example.add(1, 1), 1) << std::endl;
    
    std::cout << "The SHA-1 hash of \"Adrian Marroquin\" is: " << task::sha_1("Adrian Marroquin") << std::endl;

#ifdef _WIN32
	system("PAUSE");
#endif
	return 0;
}

