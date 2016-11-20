// HashTable.h
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

	public:
		HashEntry();
		HashEntry(const KeyType& new_key, const ValueType& new_value);
		ValueType getValue() const;
		void setValue(const ValueType& new_value);

		bool operator==(const HashEntry<KeyType, ValueType>& right) const;
		bool operator>(const HashEntry<KeyType, ValueType>& right) const;
	};
}
#endif