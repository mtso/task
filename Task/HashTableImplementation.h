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
	unsigned int HashTable<KeyType, ValueType>::hashOf(const KeyType& target_key, const unsigned int &for_size) const
	{
		throw "HashTable has only been specialized for key/value pairs: <string, TaskEntry>, <string, TaskEntry*>";
	}

	template <>
	unsigned int HashTable<string, TaskEntry>::hashOf(const string& target_key, const unsigned int &for_size) const
	{
		unsigned int hash = HASH_START; 
		char current;

		for (unsigned int i = 0; i < target_key.length(); i++) {
			current = target_key[i];
			hash = hash * HASH_MULTIPLIER + current;
		}

		hash %= for_size;
		return hash;
	}

	template <>
	unsigned int HashTable<string, TaskEntry*>::hashOf(const string& target_key, const unsigned int &for_size) const
	{
		unsigned int hash = HASH_START;
		char current;

		for (unsigned int i = 0; i < target_key.length(); i++) {
			current = target_key[i];
			hash = hash * HASH_MULTIPLIER + current;
		}

		hash %= for_size;
		return hash;
	}


	// REF:
	// http://stackoverflow.com/a/30052481/2684355
	// https://en.wikipedia.org/wiki/Primality_test#Simple_methods
	T_KV
	bool HashTable<KV>::isPrime(const unsigned int &number)
	{
		if (number <= 3) { return true; } // Should never be less than DEFAULT_SIZE in this hash table
		if (number % 2 == 0 || number % 3 == 0) { return false; }

		for ( unsigned int divisor = 6
			; divisor * divisor - 2 * divisor + 1 <= number
			; divisor += 6 )
		{
			if (number % (divisor - 1) == 0 ||
				number % (divisor + 1) == 0)
			{
				return false;
			}
		}
		return true;
	}

	T_KV
	unsigned int HashTable<KV>::nextPrime(unsigned int minimum)
	{
		while (!isPrime(minimum))
		{
			minimum++;
		}
		return minimum;
	}

	T_KV
	void HashTable<KV>::expandTable()
	{
		unsigned int new_table_size = nextPrime(table_size * 2);

		if (new_table_size < table_size) {
			throw "Can no longer grow";
		}

		HashList<KV>* new_table = new HashList<KV>[new_table_size];
		for (unsigned int i = 0; i < new_table_size; i++) {
			new_table[i] = HashList<KV>();
		}
		//unsigned int new_entry_count = entry_count; 

		unsigned int new_used_tables = 0;
		unsigned int new_index_of_longest = 0;
		unsigned int new_collisions = 0;

		KeyType transfer_key;
		ValueType transfer_value;
		unsigned int new_index;
		unsigned int check_count = 0; // number of entries shouldn't change in this process

		// TRANSFER OLD ENTRIES INTO NEW TABLE
		for (uint i = 0; i < table_size; i++) {

			// Loop through the list at each index
			while (!table[i].isEmpty()) {

				// Pop the entry
				transfer_key = table[i].peekKey();
				transfer_value = table[i].peekValue();
				table[i].removeFirst();

				// Calculate the new hash key index
				new_index = hashOf(transfer_key, new_table_size);
				new_table[new_index].addFirst(transfer_key, transfer_value);
				check_count++;

				// Calculate new stats
				if (new_table[new_index].length() == 1) {
					new_used_tables++;
				} 
				else if (new_table[new_index].length() > 1) {
					new_collisions++;

					if (new_table[new_index].length() > new_table[new_index_of_longest].length()) {
						new_index_of_longest = new_index;
					}
				}
			}
		}

		if (check_count != entry_count) { throw "Entry count does not match after the transfer."; }
		delete[] table;
		table = new_table;
		table_size = new_table_size;
		index_of_longest = new_index_of_longest;
		used_tables = new_used_tables;
		collisions = new_collisions;
	}

	// Public:

	T_KV
	HashTable<KeyType, ValueType>::HashTable()
	: index_of_longest(0)
	, used_tables(0)
	, entry_count(0)
	, collisions(0)
	{
		table_size = DEFAULT_SIZE;

		table = new HashList<KV>[table_size];

		for (uint i = 0; i < table_size; i++) {
			table[i] = HashList<KV>();
		}
	}

	T_KV
	HashTable<KV>::~HashTable()
	{
		for (uint i = 0; i < table_size; i++) {

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
	unsigned int HashTable<KV>::count() const
	{
		return entry_count;
	}

	T_KV
	bool HashTable<KV>::insert(const KeyType& new_key, const ValueType& new_value)
	{
		unsigned int index = hashOf(new_key, table_size);

		if (table[index].contains(new_key)) {
			return false;
		}
		else {
			//if (table[index].isEmpty()) { used_tables += 1; }
			table[index].addFirst(new_key, new_value);
			entry_count++;

			// Increment stats
			if (table[index].length() == 1) {
				used_tables++;
			}
			else if (table[index].length() > 1) {
				collisions++;

				if (table[index].length() > table[index_of_longest].length()) {
					index_of_longest = index;
				}
			}
			
			if (getLoadFactor() > 0.9 || table[index_of_longest].length() > 5) {
				expandTable();
			}

			return true;
		}
	}


	T_KV
	bool HashTable<KV>::remove(const KeyType& delete_key)
	{
		unsigned int index = hashOf(delete_key, table_size);
		bool didRemove = table[index].remove(delete_key);
		if (didRemove) {
			// Decrement used_tables and collision count
			if (table[index].isEmpty()) { used_tables -= 1; }
			else { collisions--; }

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
		for (uint i = 0; i < table_size; i++) {
			table[i].clear();
		}
	}

	T_KV
	ValueType HashTable<KV>::getValue(const KeyType& target_key) const
	{
		return table[hashOf(target_key, table_size)].getValue(target_key);
	}

	T_KV
	ValueType& HashTable<KV>::getRawValue(const KeyType& target_key)
	{
		return table[hashOf(target_key, table_size)].getRawValue(target_key);
	}

	T_KV
	bool HashTable<KV>::contains(const KeyType& target_key) const
	{
		int index = hashOf(target_key, table_size);
		return table[index].contains(target_key);
	}

	T_KV
	void HashTable<KV>::traverse(void visit(ValueType& entry)) const
	{
		for (uint i = 0; i < table_size; i++) 
		{
			table[i].traverse(visit);
		}
	}

	T_KV
	double HashTable<KV>::getLoadFactor() const
	{
		return (double)used_tables / (double)table_size;
	}

	T_KV
	unsigned int HashTable<KV>::countLongestList() const
	{
		return table[index_of_longest].length();
	}

	T_KV
	void HashTable<KV>::forceExpansion()
	{
		expandTable();
	}

	T_KV
	unsigned int HashTable<KV>::countUsedTables() const
	{
		return used_tables;
	}

	T_KV
	unsigned int HashTable<KV>::getTableSize() const
	{
		return table_size;
	}

	T_KV
	int HashTable<KV>::getAccessCountOf(const KeyType& target_key)
	{
		int index = hashOf(target_key, table_size);
		return table[index].getAccessCountFor(target_key);
	}
}

#endif