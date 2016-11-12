// Main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Demo.h"
#include "TemplateTest.h"

int main(int argc, char* argv[])
{
	task::Demo demo;
	std::cout << task::Min(demo.add(1, 1), 1)<< std::endl;

	system("PAUSE");
	return 0;
}

