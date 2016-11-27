// TaskEntry.h
// Task
// CIS 22C F2016:

#ifndef TASK_TASKENTRY_H
#define TASK_TASKENTRY_H

#include <stdint.h>
#include <sstream>
//#include <string>
#include <chrono>
using namespace std;

#include "TaskEntryStatus.h"
#include "Utilities\Sha1.h"

namespace task
{

	class TaskEntry
	{
	private:
		// 40 hex character id
		string unique_id;
		uint64_t time_created;
		uint64_t time_due;
		string description;
		TaskEntryStatus status;
		string user_creator;

		/**
		 * Mutual initializer, all constructors should call this!
		 */
		void init(
			const string& input_creator,
			const string& input_description,
			const uint64_t& input_time_created,
			const TaskEntryStatus& input_status = BACKLOG,
			const uint64_t& input_time_due = 0);

		static string msToString(const uint64_t& milliseconds);

	public:
		/**
		 * Construct a new TaskEntry with just a string.
		 */
		TaskEntry(const string& input_creator, const string& input_description);

		/**
		 * Construct a new TaskEntry with a string and
		 * a manual time value. This can be used for testing.
		 */
		TaskEntry(const string& input_creator, const string& input_description, const uint64_t& input_time_created);

		TaskEntry(const string& input_creator, const string& input_description, const uint64_t& input_time_created, const uint64_t& input_time_due, TaskEntryStatus& input_status);

		/**
		 * Copy constructor
		 */
		TaskEntry(const TaskEntry& original);

		/**
		 * Returns the description as a string
		 */
		string getDescription() const;

		/**
		 * TODO: IMPLEMENT THIS
		 */
		void setDescription(const string& new_description);

		/**
		 * Returns the creation time in milliseconds
		 */
		uint64_t getTimeCreatedMs() const;
		
		/**
		 * Returns the creation time as a natural language string
		 */
		string getTimeCreatedStr() const;

		/**
		 * Returns the due time in milliseconds
		 */
		uint64_t getTimeDueMs() const;

		/**
		 * Returns the due time as a natural language string
		 */
		string getTimeDueStr() const;

		/**
		 * Sets the due time.
		 */
		void setTimeDueMs(const uint64_t& input_time_due);

		/**
		 * Returns the unique id.
		 */
		string getId() const;

		/**
		 * Returns the status enum.
		 */
		TaskEntryStatus getStatus() const;

		/**
		 * TODO: IMPLEMENT THIS
		 */
		void setStatus(const TaskEntryStatus& new_status);

		/**
		 * Returns the username of the creator
		 */
		string getCreator() const;

		/**
		 * Used in collections to identify entries
		 */
		bool operator==(const TaskEntry& right) const;
	};
}

#endif