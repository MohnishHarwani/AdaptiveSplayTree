#pragma once
#include <sstream>
#include <exception>
#include <memory>
namespace cs251 {

// Custom exception classes
class duplicate_key : public std::runtime_error {
	public: duplicate_key() : std::runtime_error("Duplicate key!") {} };
class nonexistent_key : public std::runtime_error {
	public: nonexistent_key() : std::runtime_error("Key does not exist!") {} };
class empty_tree : public std::runtime_error {
	public: empty_tree() : std::runtime_error("Tree is empty!") {} };

template <typename K, typename V>
class splay_tree {
public:
	struct splay_tree_node {
		// Pointer to the left child
		std::shared_ptr<splay_tree_node> m_left {};
		// Pointer to the right child
		std::shared_ptr<splay_tree_node> m_right {};
		// Weak pointer to the parent
		std::weak_ptr<splay_tree_node> m_parent {};

		// The key of this element
		K m_key {};
		// Pointer to the value of this element
		std::unique_ptr<V> m_value {};
	};

	// Return a pointer to the root of the tree
	std::shared_ptr<splay_tree_node> get_root() const;

	// Default constructor - create an empty splay tree
	splay_tree();

	// Insert the key/value pair into the tree, if the key doesn't already exist
	// Throw duplicate_key if the key already exists
	void insert(const K& key, std::unique_ptr<V> value);
	// Return a const reference to the value associated with the given key
	// Throw nonexistent_key if the key is not in the splay tree
	const std::unique_ptr<V>& peek(const K& key);
	// Remove and return the key-value pair associated with the given key
	// Throw nonexistent_key if the key is not in the splay tree
	std::unique_ptr<V> extract(const K& key);

	// Return the minimum key in the splay tree, and splay the node
	// Throw empty_tree if the tree is empty
	K minimum_key();
	// Return the maximum key in the splay tree, and splay the node
	// Throw empty_tree if the tree is empty
	K maximum_key();

	// Return the current number of elements in the splay tree
	bool empty() const;
	// Return whether the splay tree is currently empty
	size_t size() const;

private:
	// Pointer to the root node of the splay tree
	std::shared_ptr<splay_tree_node> m_root {};

	bool check_existence(const K& key, std::shared_ptr<splay_tree_node> a);

	void rightRotate(std::shared_ptr<splay_tree_node> a);
	void leftRotate(std::shared_ptr<splay_tree_node> a);
	void splay_node(std::shared_ptr<splay_tree_node> a);
	std::shared_ptr<splay_tree_node> inOrderSuccessor(std::shared_ptr<splay_tree_node> node);


	size_t m_size = 0;
};

template <typename K, typename V>
std::shared_ptr<typename splay_tree<K,V>::splay_tree_node> splay_tree<K,V>::get_root() const {
	return m_root;
}

template <typename K, typename V>
splay_tree<K,V>::splay_tree() {
	m_root = nullptr;
}

template <typename K, typename V>
bool splay_tree<K, V>::check_existence(const K& key, std::shared_ptr<splay_tree_node> a) {
	if (a == nullptr) {
		return false;
	} else if (a->m_key == key) {
			return true;
	} else {
		bool b = false;
		if (key < a->m_key) {
			b = check_existence(key, a->m_left);
		} else {
			b = check_existence(key, a->m_right);
		}
		return b;
	}
}


template <typename K, typename V>
void splay_tree<K, V>::rightRotate(std::shared_ptr<splay_tree_node> a) {

	//std::cout << "RR start" << std::endl;

	std::shared_ptr<splay_tree_node> b = a->m_left;

	a->m_left = b->m_right;

	if (b->m_right != nullptr) {
		b->m_right->m_parent = std::weak_ptr<splay_tree_node>(a);
	}

	b->m_parent = std::weak_ptr<splay_tree_node>(a->m_parent);

	if (a->m_parent.expired()) {
		m_root = b;
	} else if (a == a->m_parent.lock()->m_right) {
		a->m_parent.lock()->m_right = b;
	} else {
		a->m_parent.lock()->m_left = b;
	}

	b->m_right = a;
	a->m_parent = std::weak_ptr<splay_tree_node>(b);

	//std::cout << "RR end" << std::endl;
}

template <typename K, typename V>
void splay_tree<K, V>::leftRotate(std::shared_ptr<splay_tree_node> a) {

	std::shared_ptr<splay_tree_node> b = a->m_right;
	a->m_right = b->m_left;

	if (b->m_left != nullptr) {
		b->m_left->m_parent = std::weak_ptr<splay_tree_node>(a);
	}

	b->m_parent = std::weak_ptr<splay_tree_node>(a->m_parent);

	if (a->m_parent.expired()) {
		m_root = b;
	} else if (a == a->m_parent.lock()->m_right) {
		a->m_parent.lock()->m_right = b;
	} else {
		a->m_parent.lock()->m_left = b;
	}

	b->m_left = a;
	a->m_parent = std::weak_ptr<splay_tree_node>(b);

	//std::cout << "LR end" << std::endl;
}

template <typename K, typename V>
void splay_tree<K, V>::splay_node(std::shared_ptr<splay_tree_node> a) {

	while (m_root != a) {

		std::weak_ptr<splay_tree_node> par = a->m_parent;


		if (par.lock()->m_parent.expired()) {

			if (a == par.lock()->m_left)  {
				rightRotate(par.lock());
			} else {
				leftRotate(par.lock());
			}
			break;

		} else {
			/*
			if (a != nullptr) {
					std::cout << "Splay, a = \n" << a->m_key <<std::endl;
				if (!a->m_parent.expired()) {
					std::cout << "Splay, a's parent = \n" << a->m_parent.lock()->m_key <<std::endl;

					if (a->m_parent.lock()->m_right != nullptr) {
						std::cout << "Splay, a's parent's right = \n" << a->m_parent.lock()->m_right->m_key <<std::endl;
					}
				}
			} 
			*/
			

			std::weak_ptr<splay_tree_node> gpar = par.lock()->m_parent;


			if ((a == par.lock()->m_left) && (par.lock() == gpar.lock()->m_left)) {
				rightRotate(gpar.lock());
				rightRotate(par.lock());
			} else if ((a == par.lock()->m_right) && (par.lock() == gpar.lock()->m_right)) {
				leftRotate(gpar.lock());
				leftRotate(par.lock());
			} else if ((a == par.lock()->m_right) && (par.lock() == gpar.lock()->m_left)) {
				leftRotate(par.lock());
				rightRotate(gpar.lock());
			} else  {
				rightRotate(par.lock());
				leftRotate(gpar.lock());
			}
		}
	}

}

template <typename K, typename V>
std::shared_ptr<typename splay_tree<K, V>::splay_tree_node> splay_tree<K,V>::inOrderSuccessor(std::shared_ptr<splay_tree_node> node) {
	std::shared_ptr<splay_tree_node> b = node;

	b = b->m_right;

	while (b->m_left != nullptr) {
		b = b->m_left;
	}

	return b;
}



template <typename K, typename V>
void splay_tree<K,V>::insert(const K& key, std::unique_ptr<V> value) {
	if (check_existence(key, m_root)) {
		throw duplicate_key();
	}

	//std::cout << "Checkpoint 1\n" << std::endl;

	std::shared_ptr<splay_tree_node> b = std::make_shared<splay_tree_node>();
	b->m_key = key;
	b->m_value = std::move(value);
	b->m_left = nullptr;
	b->m_right = nullptr;
	b->m_parent.reset();

	//std::cout << "Checkpoint 2\n" << std::endl;


	if (m_root == nullptr) {
		m_root = std::shared_ptr<splay_tree_node>(b);
		m_size++;
		return;
	}

	std::shared_ptr<splay_tree_node> current_node = m_root;
	std::shared_ptr<splay_tree_node> parent_node = nullptr;
	
	//std::cout << "Checkpoint 3\n" << std::endl;

	while (current_node != nullptr) {
		parent_node = current_node;

		if (key < current_node->m_key) {
			current_node = current_node->m_left;
		} else {
			current_node = current_node->m_right;
		}
	}

	//std::cout << "Checkpoint 3, parent_node = "<< parent_node->m_key << std::endl;

	if (key < parent_node->m_key) {
		parent_node->m_left = b;
	} else {
		parent_node->m_right = b;
	}

	b->m_parent = std::weak_ptr<splay_tree_node>(parent_node);

	//std::cout << "Checkpoint 4\n" << std::endl;
	
	splay_node(b);

	//std::cout << "Checkpoint 5\n" << std::endl;
	m_size++;

}

template <typename K, typename V>
const std::unique_ptr<V>& splay_tree<K,V>::peek(const K& key) {

	std::shared_ptr<splay_tree_node> node = m_root;

	while (node != nullptr) {
		//std::cout << "Node name: " << node->m_key << std::endl;
		if (node->m_key == key) {
		//std::cout << "Peek Found, While Break\n" <<std::endl;
			break;
		} else if (key < node->m_key) {
			node = node->m_left;
		} else {
			node = node->m_right;
		}
	}


	if (node != nullptr) {
		//std::cout << "Peek, node = \n" << node->m_key <<std::endl;
		if (!node->m_parent.expired()) {
			//std::cout << "Peek, node's parent = \n" << node->m_parent.lock()->m_key <<std::endl;

			if (node->m_parent.lock()->m_right != nullptr) {
				//std::cout << "Peek, node's parent's right = \n" << node->m_parent.lock()->m_right->m_key <<std::endl;
			}
		}
	} 
	

	if (node != nullptr) {
		/*
		std::cout << "Peek, node = \n" << node->m_key <<std::endl;
		if (!node->m_parent.expired()) {
			std::cout << "Peek, node's parent = \n" << node->m_parent.lock()->m_key <<std::endl;

			if (node->m_parent.lock()->m_right != nullptr) {
				std::cout << "Peek, node's parent's right = \n" << node->m_parent.lock()->m_right->m_key <<std::endl;
			}
		}
		*/
		splay_node(node);
	} else {
		throw nonexistent_key();
	}

	//std::cout << "Peek Checkpoint 3" <<std::endl;
	
	return std::move(node->m_value);
}



template <typename K, typename V>
std::unique_ptr<V> splay_tree<K,V>::extract(const K& key) {
	//std::cout << "Checkpoint 1, root = " << m_root->m_key << std::endl; 

	if (!check_existence(key, m_root)) {
		throw nonexistent_key();
	}

	std::shared_ptr<splay_tree_node> k = m_root;

	while (k != nullptr) {
		if (k->m_key == key) {
			break;
		} else if (key <= k->m_key) {
			k = k->m_left;
		} else {
			k = k->m_right;
		}
	}
	

	if (k != nullptr) {
		splay_node(k);
	} else {
		throw nonexistent_key();
	}

	if ((k->m_left == nullptr) && (k->m_right == nullptr)) {
		m_root = nullptr;
	} else if (k->m_left == nullptr) {
		m_root->m_right->m_parent.reset();
		m_root = m_root->m_right;

	} else if (k->m_right == nullptr) {
		m_root->m_left->m_parent.reset();
		m_root = m_root->m_left;

	} else {

		std::shared_ptr<splay_tree_node> successor = inOrderSuccessor(k);

		if (successor->m_parent.lock() != m_root) {
			successor->m_parent.lock()->m_left = successor->m_right;
			if (successor->m_right != nullptr) {
				successor->m_right->m_parent = successor->m_parent;
			}

			successor->m_right = m_root->m_right;
			successor->m_right->m_parent = successor;
		}
		
		successor->m_left = m_root->m_left;
		successor->m_left->m_parent = successor;

		m_root = successor;
		m_root->m_parent.reset();

	}

	k->m_left = nullptr;
	k->m_right = nullptr;
	k->m_parent.reset();

	m_size--;

	return std::move(k->m_value);
}


template <typename K, typename V>
K splay_tree<K,V>::minimum_key() {
	if (empty()) {
		throw empty_tree();
	}


	std::shared_ptr<splay_tree_node> k = m_root;
	
	while (k->m_left != nullptr) {
		k  = k->m_left;
	}

	splay_node(k);

	return k->m_key;
}

template <typename K, typename V>
K splay_tree<K,V>::maximum_key() {
	if (empty()) {
		throw empty_tree();
	}
	
	std::shared_ptr<splay_tree_node> k = m_root;
	
	while (k->m_right != nullptr) {
		k  = k->m_right;
	}

	splay_node(k);

	return k->m_key;
}

template <typename K, typename V>
bool splay_tree<K,V>::empty() const {
	return (m_size == 0);
}

template <typename K, typename V>
size_t splay_tree<K,V>::size() const {
	return m_size;
}

}
		


