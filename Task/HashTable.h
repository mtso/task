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
	static const int TABLE_SIZE = 101; // Should be a prime number


public:
	/**
	Default Constructor
	*/
	HashTable<KeyType, ValueType>();

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
	bool insert(const ValueType& new_value);

	/**
	 * 
	 */
	bool remove(const ValueType& delete_value);

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
	bool contains(const ValueType& target_value) const;
};


/**
IMPLEMENTATION 
*/
T_KV
HashTable<KeyType, ValueType>::HashTable<KeyType, ValueType>()
{

}

}

//#include "HashTable.cpp"
#endif
