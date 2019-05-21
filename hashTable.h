#include <algorithm>
#include <vector>
#include <list>
#include <functional>

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

template <typename T>
class hashTable
{
	std::vector<std::list<T>> hash_table_;
	std::function<int (T&)> hasher_;
public:
	hashTable(int size, std::function<int(T&)> hasher) : hash_table_(size), hasher_(hasher) {}

	const std::list<T>& chain(int x);
	void add(T& x);
	typename std::list<T>::iterator find(T& x);
	void remove(T& x);
};

template <typename T>
const std::list<T>& hashTable<T>::chain(int x)
{
	return hash_table_[x];
}

template <typename T>
void hashTable<T>::add(T& x)
{
	int h = hasher_(x) % hash_table_.size();
	if (std::find(hash_table_[h].begin(), hash_table_[h].end(), x) == hash_table_[h].end())
		hash_table_[h].push_front(x);
}

template <typename T>
typename std::list<T>::iterator hashTable<T>::find(T& x)
{
	int h = hasher_(x) % hash_table_.size();
	auto it = std::find(hash_table_[h].begin(), hash_table_[h].end(), x);
	if (it == hash_table_[h].end())
		it._Ptr = nullptr;
	
	return it;
}

template <typename T>
void hashTable<T>::remove(T& x)
{
	int h = hasher_(x) % hash_table_.size();
	auto it = std::find(hash_table_[h].begin(), hash_table_[h].end(), x);
	if (it != hash_table_[h].end())
		hash_table_[h].erase(it);
}

#endif HASH_TABLE_H_