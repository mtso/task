// HashEntry.h
// Task
// CIS 22C F2016: Matthew Tso

#ifndef TASK_HASHENTRY_H
#define TASK_HASHENTRY_H

#define T_KV template <typename KeyType, typename ValueType>
#define KV KeyType, ValueType

namespace task
{
	template <typename KeyType, typename ValueType>
	class HashEntry
	{
	private:
		KeyType key;
		ValueType value;
		HashEntry<KeyType, ValueType>* next;

		void setKey(const KeyType& search_key);

	public:
		//HashEntry();
		//HashEntry(const HashEntry<KV>& original);
		HashEntry(const KeyType& search_key, const ValueType& new_value);
		HashEntry(const KeyType& search_key, const ValueType& new_value, HashEntry<KeyType, ValueType>* new_next);

		KeyType getKey() const;
		ValueType getValue() const;
		HashEntry<KeyType, ValueType>* getNext() const;

		void setValue(const ValueType& new_value);
		void setNext(HashEntry<KeyType, ValueType>* next_entry);

		bool operator==(const HashEntry<KeyType, ValueType>& right) const;
		bool operator>(const HashEntry<KeyType, ValueType>& right) const;
	};
}

#include "HashEntry.cpp"
#endif