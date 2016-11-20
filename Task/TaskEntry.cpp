// TaskEntry.h
// Task
// CIS 22C F2016:

#include "TaskEntry.h"

namespace task
{
	void TaskEntry::init(
		const string& input_description,
		const uint64_t& input_time_created,
		const TaskEntryStatus& input_status,
		const uint64_t& input_time_due)
	{
		bool is_set = (input_time_due != 0);
		
		// Throw if input time due is before creation time
		// If a constructor exists that takes in a default time,
		// place this check in there instead.
		if (input_time_due < input_time_created && is_set)
		{
			throw "Invalid: input_time_due is before time created";
		}

		time_created = input_time_created;
		time_due = (is_set) ? input_time_due : 0;
		description = input_description;
		status = input_status;

		ostringstream buffer;
		buffer << input_description << time_created;
		unique_id = sha_1(buffer.str());
	}

	TaskEntry::TaskEntry(const string& input_description)
	{
		using namespace chrono;
		steady_clock::time_point current_time = steady_clock::now();
		milliseconds current_time_ms = duration_cast<milliseconds>(current_time.time_since_epoch());

		init(input_description, current_time_ms.count());
	}

	TaskEntry::TaskEntry(const string& input_description, const uint64_t& input_time_created)
	{
		init(input_description, input_time_created);
	}

	string TaskEntry::getDescription() const
	{
		return description;
	}

	uint64_t TaskEntry::getTimeCreatedMs() const
	{
		return time_created;
	}

	// TODO: Clean newline character from the cstring returned by ctime_s
	string TaskEntry::getTimeCreatedStr() const
	{
		using namespace std::chrono;
		milliseconds ms = (milliseconds)time_created;
		time_t time_created_s = duration_cast<seconds>(ms).count();

		// Time string must have at least 26 char of space.
		const size_t TIME_BUFLEN = 26;
		char time_char[TIME_BUFLEN];
		ctime_s(time_char, TIME_BUFLEN, &time_created_s);
		return (string)time_char;
	}

	string TaskEntry::getId() const
	{
		return unique_id;
	}

	TaskEntryStatus TaskEntry::getStatus() const
	{
		return status;
	}

	bool TaskEntry::operator== (const TaskEntry& right) const
	{
		return unique_id == right.unique_id;
	}

}
