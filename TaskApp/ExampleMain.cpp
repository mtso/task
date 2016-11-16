// Main.cpp : Defines the entry point for the console application.
// TaskApp
// CIS 22C F2016: Matthew Tso

/**
 * An example of the static library usage in a console process
 */

#include <iostream>

// Just include the header files (because project properties reference Task)
#ifdef OS_WINDOWS
#include "Example.h"
#include "TemplateExample.h"
#else
#include "../Task/Example.h"
#include "../Task/TemplateExample.h"
#include "../Task/Utilities/Sha1.h"
#include <string>
#endif

int main(int argc, char* argv[])
{
	task::Example example;
	std::cout << "The smaller value between (1+1) and 1 is: "
		      << task::Min(example.add(1, 1), 1) << std::endl;

	system("PAUSE");
	return 0;
}

