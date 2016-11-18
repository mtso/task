// HashTable.h
// Task
// CIS 22C F2016: Matthew Tso
//
//
// Maybe try djb2 hash algorithm from: http://www.cse.yorku.ca/~oz/hash.html

/*
djb2

this algorithm (k=33) was first reported by dan bernstein many years ago in comp.lang.c. another version of this algorithm (now favored by bernstein) uses xor: hash(i) = hash(i - 1) * 33 ^ str[i]; the magic of number 33 (why it works better than many other constants, prime or not) has never been adequately explained.

unsigned long
hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;
    
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    
    return hash;
}
/**/

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
