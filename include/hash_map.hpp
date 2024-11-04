#pragma once
#include <sstream>
#include <exception>
#include <vector>
#include <memory>
namespace cs251 {

// Custom exception classes
class duplicate_key : public std::runtime_error {
	public: duplicate_key() : std::runtime_error("Duplicate key!") {} };
class nonexistent_key : public std::runtime_error {
	public: nonexistent_key() : std::runtime_error("Key does not exist!") {} };

template <typename K, typename V>
class hash_map {
public:
	class hash_map_node {
	public:
		// The key of current node.
		K m_key = {};
		// The value of current node.
		std::unique_ptr<V> m_value{};
	};

	// Return a constant reference to the hash table vector
	const std::vector<std::shared_ptr<hash_map_node>>& get_data() const;

	// Default constructor - create a hash map with an initial capacity of 1
	hash_map();
	// Constructor - create a hash map with an intial capacity of bucketCount
	hash_map(size_t bucketCount);

	// Get the hash code for a given key
	size_t hash_code(K key) const;

	// Change the size of the table to bucketCount, re-hashing all existing elements
	// bucketCount will never be 0 or less than the current number of elements
	void resize(size_t bucketCount);

	// Insert the key/value pair into the table, if the key doesn't already exist
	// Throw duplicate_key if the key already exists
	void insert(const K& key, std::unique_ptr<V> value);
	// Return a const reference to the value associated with the given key
	// Throw nonexistent_key if the key is not in the hash table
	const std::unique_ptr<V>& peek(const K& key);
	// Remove and return the key-value pair associated with the given key
	// Throw nonexistent_key if the key is not in the hash table
	std::unique_ptr<V> extract(const K& key);

	// Return the current number of elements in the hash table
	size_t size() const;
	// Return the current capacity of the hash table
	size_t bucket_count() const;
	// Return whether the hash table is currently empty
	bool empty() const;

private:
	// The array that holds key-value pairs
	std::vector<std::shared_ptr<hash_map_node>> m_data = {};

	size_t m_size = 0;

	size_t m_bucketSize = 0;

	// TODO: Add any additional methods or variables here
};

template <typename K, typename V>
const std::vector<std::shared_ptr<typename hash_map<K,V>::hash_map_node>>& hash_map<K,V>::get_data() const {
	return m_data;
}

template <typename K, typename V>
hash_map<K,V>::hash_map() {
	m_data.resize(1);
	m_bucketSize = 1;
}

template <typename K, typename V>
hash_map<K,V>::hash_map(const size_t bucketCount) {
	m_data.resize(bucketCount);
	m_bucketSize = bucketCount;
}

template <typename K, typename V>
size_t hash_map<K,V>::hash_code(K key) const {
	return key % bucket_count();
}

template <typename K, typename V>
void hash_map<K,V>::resize(const size_t bucketCount) {
	//std::cout << "target:" << bucketCount << "\n";
	//std::cout << "cur:" << m_bucketSize << "\n";
	if (bucketCount < m_size) {
		return;
	}

	

	std::vector<std::shared_ptr<hash_map_node>> orig_map_copy(m_bucketSize);

	for (int i = 0; i < m_bucketSize; i++) {
		orig_map_copy[i] = m_data[i];
	}

	m_data.clear();
	m_data.resize(bucketCount);

	m_bucketSize = bucketCount;
	//std::cout << "bucket size: " << m_bucketSize <<std::endl; 

	/*
	for (auto& b: m_data) {
		b = nullptr;
	}
	*/
	m_size = 0;
	for (auto& b: orig_map_copy) {
		if (b != nullptr) {
			insert(b->m_key, std::move(b->m_value));
		}
	}

	

}

template <typename K, typename V>
void hash_map<K,V>::insert(const K& key, std::unique_ptr<V> value) {

	//size_t place = hash_code(key);


	//make note to start at hash place, not start

	for (auto b: m_data) {
		if (b != nullptr) {
			if (b->m_key == key) {
				throw duplicate_key();
			}
		}
	}
	
	size_t place = hash_code(key);

	int count = 1;

	std::shared_ptr<hash_map_node> a = m_data[place];

	while ((a != nullptr) && (count <= m_bucketSize)) {
		place++;
		place = place % m_bucketSize;
		a = m_data[place];
		count++;
	}


	if (count <= m_bucketSize) {

		hash_map_node *b = new hash_map_node();
		(*b).m_key = key;
		(*b).m_value = std::move(value);


		m_data[place] = std::shared_ptr<hash_map_node>(b);
		m_size++;

	} else {
		resize(m_bucketSize * 2);
		insert(key, std::move(value)); 
	}

	
}

template <typename K, typename V>
const std::unique_ptr<V>& hash_map<K,V>::peek(const K& key) {
	size_t place = hash_code(key);

	int count = 1;

	while (count <= m_bucketSize) {
		if (m_data[place] != nullptr) {
			if (m_data[place]->m_key == key) {
				break;
			}
		}
		
		place++;
		place = place % m_bucketSize;
		count++;
	}


	if (count > m_bucketSize) {
		throw nonexistent_key();
	}


	//std::unique_ptr<V> temp = std::move<V>(m_data[place]->m_value);
	return m_data[place]->m_value;
}

template <typename K, typename V>
std::unique_ptr<V> hash_map<K,V>::extract(const K& key) {
	size_t place = hash_code(key);

	int count = 1;
	//std::shared_ptr<hash_map_node> a = m_data[place];

	while (count <= m_bucketSize) {
		if (m_data[place] != nullptr) {
			if (m_data[place]->m_key == key) {
				break;
			}
		}
		
		place++;
		place = place % m_bucketSize;
		count++;
	}


	if (count > m_bucketSize) {
		throw nonexistent_key();
	}

	std::unique_ptr<V> temp = std::move(m_data[place]->m_value);

	m_data[place] = nullptr;

	m_size--;
	return temp;
}

template <typename K, typename V>
size_t hash_map<K,V>::size() const {
	return m_size;
}

template <typename K, typename V>
size_t hash_map<K,V>::bucket_count() const {
	return m_bucketSize;
}

template <typename K, typename V>
bool hash_map<K,V>::empty() const {
	return (m_size == 0);
}

}
