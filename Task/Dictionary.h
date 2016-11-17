// HashTable.h
// Task
// CIS 22C F2016: Matthew Tso

#ifndef TASK_DICTIONARY_H
#define TASK_DICTIONARY_H

#include <iterator>
#include <string>
using namespace std;

/**
 * Dictionary
 *
 * Collision resolution using separate linked-list chaining.
 */
template <typename KeyType, typename ValueType>
class Dictionary // : public std::iterator<input_iterator_tag, int>
{

public:
	/**
	 * Returns true if the Dictionary is empty
	 *
	 */
	bool isEmpty() const;

	/**
	 * Returns a count of the entries
	 */
	int count() const;

	bool insert(const KeyType& new_key, const Value& new_value);

	bool remove(const KeyType& delete_key);

	void clear();

	ValueType getValue(const KeyType& target_key) const;

	bool contains(const KeyType& target_key) const;

};

//#include "Dictionary.cpp"
#endif