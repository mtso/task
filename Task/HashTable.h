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
		static const uint HASH_START = 593; // 701;
		static const uint HASH_MULTIPLIER = 17;

		HashList<KV>* table;

		unsigned int entry_count;

		unsigned int used_tables;
		unsigned int table_size;
		unsigned int index_of_longest;
		unsigned int collisions;

		inline unsigned int hashOf(const KeyType& target_key, const unsigned int &for_size) const;

		void expandTable();

		bool isPrime(const unsigned int &number);
		unsigned int nextPrime(unsigned int minimum);
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
		 *
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
		 *
		 */
		bool remove(const KeyType& delete_key);

		/**
		*
		*/
		void clear();

		/**
		*
		*/
		ValueType getValue(const KeyType& target_key) const;

		/**
		 *
		 */
		ValueType& getRawValue(const KeyType& target_key);

		/**
		*
		*/
		bool contains(const KeyType& target_key) const;

		/**
		*
		*/
		virtual void traverse(void visit( ValueType& entry)) const;


		double getLoadFactor() const;

		unsigned int countLongestList() const;

		unsigned int countUsedTables() const;

		unsigned int getTableSize() const;

		int getAccessCountOf(const KeyType& target_key);
	};
}

#ifndef TASK_HASHTABLEIMPLEMENTATION_H
#include "HashTableImplementation.h"
#endif
#endif
