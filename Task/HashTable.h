// HashTable.h
// Task
// CIS 22C F2016: Matthew Tso
//
// Maybe try djb2 hash algorithm from: http://www.cse.yorku.ca/~oz/hash.html

#ifndef TASK_HASHTABLE_H
#define TASK_HASHTABLE_H

// #include <iterator>
#include <string>
using namespace std;

#include "ADT\DictionaryInterface.h"
#include "HashList.h"
#include "TaskEntry.h"

//#define KV KeyType, ValueType

namespace task {

	// TODO: Need to design HashTable and figure out collision resolution method

	/**
	 * HashTable
	 *
	 * Collision resolution using separate chaining of linked-lists.
	 */
	template <typename KeyType, typename ValueType>
	class HashTable : public adt::DictionaryInterface<KeyType, ValueType> // : public std::iterator<input_iterator_tag, int>
	{
	private:
		static const int DEFAULT_SIZE = 101; // Should be a prime number

		// adt::List<ValueType> table[TABLE_SIZE];
		//HashEntry<KeyType, ValueType>** table;
		HashList<KV>* table;

		int entry_count;

		int table_size;

		unsigned int hashOf(const KeyType& target_key) const;

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
		int count() const;

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
		bool contains(const KeyType& target_key) const;

		/**
		*
		*/
		virtual void traverse(void visit(const ValueType& entry)) const;
	};


	/**
	IMPLEMENTATION
	*/

	// Private:

	T_KV
	unsigned int HashTable<KeyType, ValueType>::hashOf(const KeyType& target_key) const
	{
		throw "HashTable must only be used on <string, TaskEntry>";
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
	task::HashTable<KeyType, ValueType>::HashTable()
	{
		entry_count = 0;
		table_size = DEFAULT_SIZE;

		table = new HashList<KV>[table_size];

		for (int i = 0; i < table_size; i++) {
			table[i] = HashList<KV>();
		}
	}

	T_KV
	task::HashTable<KV>::~HashTable()
	{
		for (int i = 0; i < table_size; i++) {

			table[i].clear();

		}
		delete[] table;
	}

	T_KV
	bool task::HashTable<KV>::isEmpty() const
	{
		return entry_count == 0;
	}

	T_KV
	int task::HashTable<KV>::count() const
	{
		return entry_count;
	}

	T_KV
	bool task::HashTable<KV>::insert(const KeyType& new_key, const ValueType& new_value)
	{
		int index = hashOf(new_key);
		table[index].addFirst(new_key, new_value);
		return true; // always true in a linked-list implementation
	}


	T_KV
	bool task::HashTable<KV>::remove(const KeyType& delete_key)
	{
		throw "not implemented";
	}


	T_KV
	void task::HashTable<KV>::clear()
	{
		for (int i = 0; i < table_size; i++) {
			table[i].clear();
		}
	}

	T_KV
	ValueType task::HashTable<KV>::getValue(const KeyType& target_key) const
	{
		throw "not implemented";
	}

	T_KV
	bool task::HashTable<KV>::contains(const KeyType& target_key) const
	{
		int index = hashOf(target_key);
		return table[index].contains(target_key);
	}

	T_KV
	void task::HashTable<KV>::traverse(void visit(const ValueType& entry)) const
	{
		throw "not implemented";
		//for (int i = 0; i < table_size; i++) {
		//	if (!table[i].isEmpty()) {
		//		
		//		while (table[i])
		//	}
		//}
	}
}
#endif
