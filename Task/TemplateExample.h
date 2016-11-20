// TemplateExample.h
// Task
// CIS 22C F2016: Matthew Tso

/**
 * Example template functions in static library
 * Header declaration and definition of classes/functions
 * can still be in separate files, but the header file
 * will need to #include the .cpp implementation file.
 */
#pragma once

namespace task
{
	// Returns the lesser of two inputs
	template <typename T>
	T Min(const T& x, const T& y);

	// Returns the greater of two inputs
	template <typename T>
	T Max(const T& x, const T& y);

	template <typename T>
	class TempDemo {
	public:
		T getStuff(const T& stuff) const;
	};
}

// Must include implementation in the header file for template functions or classes
#include "TemplateExample.cpp"