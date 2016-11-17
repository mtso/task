// WindowsMain.cpp
// TaskApp
// CIS 22C F2016: Adrian Marroquin
//
// WindowsMain is the entry point into Tasks's 
// interactive shell on Windows platforms.

#include <iostream>
#include <string>

#include "Example.h"
#include "TemplateExample.h"
#include "Utilities\Sha1.h"

int main(int argc, char* argv[])
{
	task::Example example;
	std::cout << "The smaller value between (1+1) and 1 is: "
		<< task::Min(example.add(1, 1), 1) << std::endl;

	std::cout << "The SHA-1 hash of \"Adrian Marroquin\" is: " << task::sha_1("Adrian Marroquin") << std::endl;

	system("PAUSE");
	return 0;
}

