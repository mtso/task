
#ifndef TASK_HASHLIST_H
#define TASK_HASHLIST_H

#include "HashEntry.h"

namespace task
{

	T_KV
	class HashList
	{
	private:
		HashEntry<KV>* head;

		int entry_length;

	public:

		HashList();

		virtual ~HashList();

		virtual int length() const;

		virtual bool isEmpty() const;

		virtual bool contains(const KeyType& target_key) const;

		virtual ValueType getValue(const KeyType& target_key) const;

		virtual bool addFirst(const HashEntry<KV>& new_entry);

		virtual bool remove(const KeyType& delete_key);

		void clear();
	};

	
}

#endif