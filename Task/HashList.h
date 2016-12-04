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

		unsigned int list_length;

		unsigned int access_count;

		HashEntry<KV>* pointerTo(const KeyType& target_key);

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

		virtual unsigned int length() const;

		virtual bool isEmpty() const;

		virtual bool contains(const KeyType& target_key);

		virtual ValueType getValue(const KeyType& target_key);

		virtual ValueType& getRawValue(const KeyType& target_key);

		virtual void addFirst(const KeyType& new_key, const ValueType& new_value);

		virtual bool remove(const KeyType& delete_key);

		virtual bool removeFirst();

		void clear();

		void traverse(void visit(ValueType& entry)) const;

		KeyType peekKey();
		ValueType peekValue();

		int getAccessCountFor(const KeyType& target_key);
	};

}

#ifndef TASK_HASHLISTIMPLEMENTATION_H
#include "HashListImplementation.h"
#endif
#endif
