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
#include "HashEntry.h"
#include "ADT\List.h"

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
		HashEntry<KeyType, ValueType>** table;

		int entry_count;

		int table_size;

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
	T_KV
	task::HashTable<KeyType, ValueType>::HashTable()
	{
		entry_count = 0;
		table_size = DEFAULT_SIZE;

		table = new HashEntry<KV>*[table_size];

		for (int i = 0; i < table_size; i++) {
			table[i] = nullptr;
		}
	}

	T_KV
	task::HashTable<KV>::~HashTable()
	{
		for (int i = 0; i < table_size; i++) {

			if (table[i] != nullptr) {
				delete table[i];
			}
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
		return entry_count();
	}

	T_KV
	bool task::HashTable<KV>::insert(const KeyType& new_key, const ValueType& new_value)
	{
		throw "not implemented";
	}


	T_KV
	bool task::HashTable<KV>::remove(const KeyType& delete_key)
	{
		throw "not implemented";
	}


	T_KV
	void task::HashTable<KV>::clear()
	{
		throw "not implemented";
		for (int i = 0; i < table_size; i++) {
			if (table[i] == nullptr) { continue; }
			

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
		throw "not implemented";
	}

	T_KV
	void task::HashTable<KV>::traverse(void visit(const ValueType& entry)) const
	{
		throw "not implemented";
	}
}
#endif
