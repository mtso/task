// TemplateExample.cpp
// Task
// CIS 22C F2016: Matthew Tso

/**
 * Should not #include TemplateExample.h header file
 * or there will be a reference loop because
 * TemplateExample.h explicitly references this file.
 */
//#pragma once

namespace task
{
	template <typename T>
	T Min(const T& x, const T& y)
	{
		return x < y ? x : y;
	}

	template <typename T>
	T Max(const T& x, const T& y)
	{
		return x > y ? x : y;
	}
}
