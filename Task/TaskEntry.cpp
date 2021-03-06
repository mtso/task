// TaskEntry.h
// Task
// CIS 22C F2016: Matthew Tso, Jinzhu Shen

#include "TaskEntry.h"

namespace task
{
	// Private member functions

	void TaskEntry::init(
		const string& input_creator,
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

		user_creator = input_creator;
		time_created = input_time_created;
		time_due = (is_set) ? input_time_due : 0;
		description = input_description;
		status = input_status;

		ostringstream buffer;
		buffer << input_creator << input_time_created;
		unique_id = sha_1(buffer.str());
	}

	// Public member functions

	/**
	 * Default constructor, should never inserted directly into a table 
	 */
	TaskEntry::TaskEntry()
		: unique_id("")
		, time_created(0)
		, time_due(0)
		, description("")
		, status(BACKLOG)
		, user_creator("")
	{
	}

	TaskEntry::TaskEntry(const string& input_creator, const string& input_description)
	{
		using namespace chrono;
		steady_clock::time_point current_time = steady_clock::now();
		milliseconds current_time_ms = duration_cast<milliseconds>(current_time.time_since_epoch());

		init(input_creator, input_description, current_time_ms.count());
	}

	TaskEntry::TaskEntry(const string& input_creator, const string& input_description, const uint64_t& input_time_created)
	{
		init(input_creator, input_description, input_time_created);
	}

    TaskEntry::TaskEntry(const string& input_creator, const string& input_description, const uint64_t& input_time_created, const uint64_t& input_time_due, TaskEntryStatus& input_status)
    {
        init(input_creator, input_description, input_time_created, input_status, input_time_due);
    }

	TaskEntry::TaskEntry(const TaskEntry& original)
		: unique_id(original.unique_id)
		, time_created(original.time_created)
		, time_due(original.time_due)
		, description(original.description)
		, status(original.status)
		, user_creator(original.user_creator)
	{
	}

	string TaskEntry::getDescription() const
	{
		return description;
	}

	void TaskEntry::setDescription(const string& new_description)
	{
		description = new_description;
	}

	uint64_t TaskEntry::getTimeCreatedMs() const
	{
		return time_created;
	}

	string TaskEntry::getCreator() const
	{
		return user_creator;
	}

	string TaskEntry::getTimeCreatedStr() const
	{
		if (time_created == 0) {
			return "time created not set";
		}

		return msToString(time_created);
	}

	string TaskEntry::getTimeCreatedStrShort() const
	{
		if (time_created == 0) {
			return "time created not set";
		}
		return getTimeCreatedStr().substr(0, 10);
	}

	string TaskEntry::getTimeDueStrShort() const
	{
		if (time_due == 0) {
			return "time due not set";
		}
		return getTimeDueStr().substr(0, 10);
	}

	uint64_t TaskEntry::getTimeDueMs() const
	{
		//if (time_due == 0) {
		//	throw "Time due has not been set.";
		//}
		return time_due;
	}

	string TaskEntry::getTimeDueStr() const
	{
		if (time_due == 0) {
			return "due date not set";
		}

		// Call getTimeDueMs for the 0 check
		return msToString(getTimeDueMs());
	}

	void TaskEntry::setTimeDueMs(const uint64_t& input_time_due)
	{
		if (input_time_due < time_created) {
			throw "Input time due is before creation time";
		}
		time_due = input_time_due;
	}

	string TaskEntry::getId() const
	{
		return unique_id;
	}

	TaskEntryStatus TaskEntry::getStatus() const
	{
		return status;
	}

	void TaskEntry::setStatus(const TaskEntryStatus& new_status)
	{
		status = new_status;
	}

	bool TaskEntry::operator== (const TaskEntry& right) const
	{
		return unique_id == right.unique_id;
	}

	ostream& operator << (ostream& output, const TaskEntry& entry)
	{
		unsigned int description_length = 14;		
		if (entry.description.length() > description_length - 3) {
			output << yellow << entry.unique_id.substr(0, 8) << white << " \"" 
				<< entry.description.substr(0, description_length - 3)
				<< "...\"";
		}
		else {
			output << yellow << entry.unique_id.substr(0, 8) << white << " \""
				<< entry.description.substr(0, description_length)
				<< "\"";
		}
		return output;
	}
}
