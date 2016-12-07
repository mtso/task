// DateTime.cpp
// Task/Utilities
// CIS 22C F2016: Matthew Tso

#include "DateTime.h"

namespace task {

	uint64_t weekToMs(const int& weeks)
	{
		uint64_t ms_in_week = 604800000;
		return (uint64_t)weeks * ms_in_week;
	}
	
	uint64_t dayToMs(const int& days)
	{
		uint64_t ms_in_day = 86400000;
		return (uint64_t)days * ms_in_day;
	}

	uint64_t hourToMs(const int& hours)
	{
		uint64_t ms_in_hour = 3600000;
		return (uint64_t)hours * ms_in_hour;
	}

	uint64_t minuteToMs(const int& minutes)
	{
		uint64_t ms_in_minute = 60000;
		return (uint64_t)minutes * ms_in_minute;
	}

	uint64_t rawDateToMs(const string& raw_input)
	{
		// example date:                              11-14-2015
		string month_str = raw_input.substr(0, 2); // 11
		string day_str = raw_input.substr(3, 2);   //    14
		string year_str = raw_input.substr(6, 4);  //       2015

		// Convert strings into integers
		int month, day, year;
		try {
			month = stoi(month_str);
			day = stoi(day_str);
			year = stoi(year_str);
		}
		catch (std::invalid_argument error) {
			throw error;
		}

		// Build a time struct
		tm date = { 0 };
		date.tm_year = year - 1900; // since 1900
		date.tm_mon = month - 1;    // [0, 11] month since january
		date.tm_mday = day;         // [1, 31] day of month
		date.tm_hour = 12;          // Hardcode as noon

		// Convert into time value
		time_t time = mktime(&date);
		using namespace chrono;
		steady_clock::time_point point = steady_clock::from_time_t(time);
		milliseconds epoch_time = duration_cast<milliseconds>(point.time_since_epoch());

		// Return the raw integer
		return epoch_time.count();
	}

	string msToString(const uint64_t& raw_ms)
	{
		using namespace std::chrono;
		milliseconds ms = (milliseconds)raw_ms;
		time_t time_created_s = duration_cast<seconds>(ms).count();

		// Time string must have at least 26 char of space.
		const size_t TIME_BUFLEN = 26;
		char time_char[TIME_BUFLEN];
		ctime_s(time_char, TIME_BUFLEN, &time_created_s);

		// Convert to a string type in order to return 
		// its substr without the trailing newline character
		string raw_time_str = (string)time_char;
		return raw_time_str.substr(0, raw_time_str.length() - 1);
	}
}