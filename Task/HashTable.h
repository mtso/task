// HashTable.h
// Task
// CIS 22C F2016: Matthew Tso
//
// Maybe try djb2 hash algorithm from: http://www.cse.yorku.ca/~oz/hash.html

#ifndef TASK_DICTIONARY_H
#define TASK_DICTIONARY_H

#include <iterator>
#include <string>
using namespace std;

namespace task {
    
/**
 * HashTable
 *
 * Collision resolution using separate chaining of linked-lists.
 */
template <typename ValueType>
class HashTable // : public std::iterator<input_iterator_tag, int>
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

	bool insert(const ValueType& new_value);

	bool remove(const ValueType& delete_value);

	void clear();

	//ValueType getValue(const KeyType& target_key) const;

	bool contains(const ValueType& target_value) const;
};

}

//#include "Dictionary.cpp"
#endif
