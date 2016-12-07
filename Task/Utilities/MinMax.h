// MinMax.h
// Task/Utilities
// CIS 22C F2016: Matthew Tso

#ifndef TASK_MINMAX_H
#define TASK_MINMAX_H

#include <chrono>
#include <stdint.h>

namespace task {

	template <typename T>
	T min_of(const T& x, const T& y)
	{
		return (x < y) ? x : y;
	}

	template <typename T>
	T max_of(const T& x, const T& y)
	{
		return (x > y) ? x : y;
	}
}

#endif