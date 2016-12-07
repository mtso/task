// HashTable.h
// Task
// CIS 22C F2016: Matthew Tso
//
// Maybe try djb2 hash algorithm from: http://www.cse.yorku.ca/~oz/hash.html
//
// TODO: try next-prime implementation here: http://stackoverflow.com/a/30052481/2684355
//       to get the next prime number of a certain order of magnitude

#ifndef TASK_HASHTABLE_H
#define TASK_HASHTABLE_H

// #include <iterator>
#include <string>
using namespace std;

#include "ADT\DictionaryInterface.h"
#include "HashList.h"
#include "TaskEntry.h"

typedef unsigned int uint;

namespace task 
{
	/**
	 * HashTable
	 *
	 * Collision resolution using separate chaining of linked-lists.
	 */
	template <typename KeyType, typename ValueType>
	class HashTable : public adt::DictionaryInterface<KeyType, ValueType> // : public std::iterator<input_iterator_tag, int>
	{
	private:
		static const uint DEFAULT_SIZE = 101; // Should be a prime number
		static const uint HASH_START = 15607; // 701;
		static const uint HASH_MULTIPLIER = 17;

		// Points to the dynamic array of linked lists
		HashList<KV>* table;

		unsigned int entry_count;
		unsigned int used_tables;
		unsigned int table_size;
		unsigned int index_of_longest;
		unsigned int collisions;

		// Uses a multiplicative hash to determine
		// an index based off of current table size
		inline unsigned int hashOf(const KeyType& target_key, const unsigned int &for_size) const;

		// Re-hashes the table to decrease load factor
		// will often lower the count of the longest list too 
		void expandTable();

		// Checks the primality of a number
		bool isPrime(const unsigned int &number);

		// Returns the next prime number greater than a minimum
		unsigned int nextPrime(unsigned int minimum);

		// Forces an expansion of the table.
		void forceExpansion();

	public:
		/**
		Default Constructor
		*/
		HashTable<KeyType, ValueType>();

		/**
		*/
		~HashTable<KeyType, ValueType>();

		/**
		 * Returns true if the Dictionary is empty
		 */
		bool isEmpty() const;

		/**
		 * Returns a count of the entries
		 */
		unsigned int count() const;

		/**
		 * Inserts an item by value
		 */
		bool insert(const KeyType& new_key, const ValueType& new_value);

		/**
		 * Removes an item by its key, may throw if entry is not found
		 */
		bool remove(const KeyType& delete_key);

		/**
		* Clears each list in the table
		*/
		void clear();

		/**
		* Returns a copy of the value of an entry identified by key
		*/
		ValueType getValue(const KeyType& target_key) const;

		/**
		 * Returns a reference to the value of an entry identified by the key
		 */
		ValueType& getRawValue(const KeyType& target_key);

		/**
		* Returns true if an entry is found with a key that matches
		*/
		bool contains(const KeyType& target_key) const;

		/**
		* Traverses each list in the table by array order
		* the list traverses from top to bottom
		*/
		virtual void traverse(void visit( ValueType& entry)) const;

		// Returns the load factor between 0 and 1,
		// number of non-empty tables divided by table size
		double getLoadFactor() const;

		// Returns the longest list identfied by index
		unsigned int countLongestList() const;

		// Returns the number of non-empty tables
		unsigned int countUsedTables() const;

		// Returns the current table size, should be a prime number
		unsigned int getTableSize() const;

		// Returns the number of comparisons before finding an entry by key
		int getAccessCountOf(const KeyType& target_key);

		// Returns the number of tables with more than one entry in it
		uint getCollisionCount() const;
	};
}

#ifndef TASK_HASHTABLEIMPLEMENTATION_H
#include "HashTableImplementation.h"
#endif
#endif
