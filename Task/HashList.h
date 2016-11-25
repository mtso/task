// HashList.h
// Task
// CIS 22C F2016: Matthew Tso

#ifndef TASK_HASHLIST_H
#define TASK_HASHLIST_H

#include <string>
using namespace std;

#include "HashEntry.h"

namespace task
{

	T_KV
	class HashList
	{
	private:
		HashEntry<KV>* head;

		int list_length;

	public:
		class NotFoundException
		{
		private:
			string description = "Value not found";
		public:
			string getDescription() const { return description; }
		};

		HashList();

		virtual ~HashList();

		virtual int length() const;

		virtual bool isEmpty() const;

		virtual bool contains(const KeyType& target_key);

		virtual ValueType getValue(const KeyType& target_key);

		virtual void addFirst(const KeyType& new_key, const ValueType& new_value);

		virtual bool remove(const KeyType& delete_key);

		virtual bool removeFirst();

		void clear();

		void traverse(void visit(const ValueType& entry)) const;
	};

}

#include "HashListImplementation.h"
#endif
