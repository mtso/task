
#pragma once

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