
#ifndef TASKAPP_WINDOWSDIRECTORY_H
#define TASKAPP_WINDOWSDIRECTORY_H

#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <strsafe.h>
using namespace std;
#pragma comment(lib, "User32.lib")

namespace taskapp {

	/**
	 * Stub of a function that 
	 */
	string filenamesIn(const TCHAR* search_directory);
}

#endif