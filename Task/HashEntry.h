// HashEntry.h
// Task
// CIS 22C F2016: Matthew Tso

#ifndef TASK_HASHENTRY_H
#define TASK_HASHENTRY_H

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
		HashEntry();
		HashEntry(const KeyType& search_key, const ValueType& new_value);
		KeyType getKey() const;
		ValueType getValue() const;
		void setValue(const ValueType& new_value);

		bool operator==(const HashEntry<KeyType, ValueType>& right) const;
		bool operator>(const HashEntry<KeyType, ValueType>& right) const;
	};

	template <typename KeyType, typename ValueType>
	HashEntry<KeyType, ValueType>::HashEntry(const KeyType& search_key, const ValueType& new_value)
		: key(search_key)
		, value(new_value)
		, next(nullptr)
	{
	}

	template <typename KeyType, typename ValueType>
	KeyType HashEntry<KeyType, ValueType>::getKey() const
	{
		return key;
	}
}

#endif