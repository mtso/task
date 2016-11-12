// Main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Demo.h"

int main(int argc, char* argv[])
{
	task::Demo demo;
	std::cout << demo.add(1, 1) << std::endl;

	system("PAUSE");
	return 0;
}

