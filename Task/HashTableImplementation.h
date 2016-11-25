// HashTable.cpp
// Task
// CIS 22C F2016: Matthew Tso

//#include "HashTable.h"

#ifndef TASK_HASHTABLEIMPLEMENTATION_HP
#define TASK_HASHTABLEIMPLEMENTATION_H

#ifndef TASK_HASHTABLE_H
#include "HashTable.h"
#endif

namespace task 
{
	// Private:

	T_KV
	unsigned int HashTable<KeyType, ValueType>::hashOf(const KeyType& target_key) const
	{
		throw "HashTable has only been implemented for key/value pair of <string, TaskEntry>";
	}

	template <>
	unsigned int HashTable<string, TaskEntry>::hashOf(const string& target_key) const
	{
		unsigned int hash = 5381;
		char current;

		for (unsigned int i = 0; i < target_key.length(); i++) {
			current = target_key[i];
			hash = hash * 33 + current;
		}

		hash %= table_size;
		return hash;
	}

	// Public:

	T_KV
	HashTable<KeyType, ValueType>::HashTable()
	{
		entry_count = 0;
		table_size = DEFAULT_SIZE;

		table = new HashList<KV>[table_size];

		for (int i = 0; i < table_size; i++) {
			table[i] = HashList<KV>();
		}
	}

	T_KV
	HashTable<KV>::~HashTable()
	{
		for (int i = 0; i < table_size; i++) {

			table[i].clear();

		}
		delete[] table;
	}

	T_KV
	bool HashTable<KV>::isEmpty() const
	{
		return entry_count == 0;
	}

	T_KV
	int HashTable<KV>::count() const
	{
		return entry_count;
	}

	T_KV
	bool HashTable<KV>::insert(const KeyType& new_key, const ValueType& new_value)
	{
		int index = hashOf(new_key);

		if (table[index].contains(new_key)) {
			return false;
		}
		else {
			table[index].addFirst(new_key, new_value);
			entry_count++;
			return true;
		}
	}


	T_KV
	bool HashTable<KV>::remove(const KeyType& delete_key)
	{
		bool didRemove = table[hashOf(delete_key)].remove(delete_key);
		if (didRemove) {
			entry_count--;
			return true;
		}
		else {
			return false;
		}
	}


	T_KV
	void HashTable<KV>::clear()
	{
		for (int i = 0; i < table_size; i++) {
			table[i].clear();
		}
	}

	T_KV
	ValueType HashTable<KV>::getValue(const KeyType& target_key) const
	{
		return table[hashOf(target_key)].getValue(target_key);
	}

	T_KV
	bool HashTable<KV>::contains(const KeyType& target_key) const
	{
		int index = hashOf(target_key);
		return table[index].contains(target_key);
	}

	T_KV
	void HashTable<KV>::traverse(void visit(const ValueType& entry)) const
	{
		throw "not implemented";
		for (int i = 0; i < table_size; i++) {
			// TODO: resolve traversal of list through table;
			table[i].traverse(visit);
		}
	}
}

#endif