// HashEntry.cpp
// Task
// CIS 22C F2016: Matthew Tso

#ifndef TASK_HASHENTRYIMPLEMENTATION_H
#define TASK_HASHENTRYIMPLEMENTATION_H

#include "HashEntry.h"

namespace task 
{
	// Constructors

	// Copy constructor
	//T_KV
	//HashEntry<KV>::HashEntry(const HashEntry<KV>& original)
	//	: key(original.key)
	//	, value(original.value)
	//	, next(original.next)
	//{
	//}

	T_KV
	HashEntry<KeyType, ValueType>::HashEntry(const KeyType& search_key, const ValueType& new_value)
		: key(search_key)
		, value(new_value)
		, next(nullptr)
	{
	}

	T_KV
	HashEntry<KeyType, ValueType>::HashEntry
		(const KeyType& search_key
		, const ValueType& new_value
		, HashEntry<KeyType, ValueType>* new_next
		)
		: key(search_key)
		, value(new_value)
		, next(new_next)
	{
	}

	/**
	GETTER DEFINITIONS
	*/
	T_KV
	KeyType HashEntry<KeyType, ValueType>::getKey() const
	{
		return key;
	}

	T_KV
	ValueType HashEntry<KeyType, ValueType>::getValue() const
	{
		return value;
	}

	T_KV
	ValueType& HashEntry<KeyType, ValueType>::getRawValue()
	{
		return value;
	}

	T_KV
	HashEntry<KeyType, ValueType>* HashEntry<KeyType, ValueType>::getNext() const
	{
		return next;
	}

	/**
	SETTER DEFINITIONS
	*/

	T_KV
	void HashEntry<KeyType, ValueType>::setValue(const ValueType& new_value)
	{
		value = new_value;
	}

	T_KV
	void HashEntry<KeyType, ValueType>::setNext(HashEntry<KeyType, ValueType>* next_entry)
	{
		next = next_entry;
	}

	/**
	OPERATOR OVERLOAD DEFINITIONS
	*/
	T_KV
	bool HashEntry<KeyType, ValueType>::operator==(const HashEntry<KeyType, ValueType>& right) const
	{
		return key == right.key;
	}

	T_KV
	bool HashEntry<KeyType, ValueType>::operator>(const HashEntry<KeyType, ValueType>& right) const
	{
		return key > right.key;
	}
}
#endif