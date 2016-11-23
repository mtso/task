
#ifndef C_TREE_H
#define C_TREE_H
#include <vector>
#include <string>
using namespace std;

/**
* @brief c_tree is a template for binary search tree.
* @tparam _key_t The key type in the binary search tree, must support operator <,
* operator ==, and copy constructor.
* @tparam _val_t The value type in the binary search tree, default as void.
*/
template <typename _key_t, typename _val_t>
class c_tree 
{	
private:
	/** The tree node type. */
	struct node_t {
	/** The left child of the node. */
	node_t* m_left;
	/** The right child of the node. */
	node_t* m_right;
	/** The parent of the node. */
	node_t* m_parent;
	/** The key of the node, NULL for leaf.*/
	_key_t* m_key;
	/** The value of the node, could be NULL. */
	_val_t* m_val;
	};
public:
	/**
	* @brief Constructor for c_tree
	*/
	c_tree(void);
	/**
	* @brief Destructor for c_tree
	*/
	~c_tree(void);
	/**
	* @brief Get the number of items in the tree.
	* @return The number of items in the tree.
	*/
	int size(void) const;
	/**
	* @brief Insert a node with the key and value.
	* @param[in] key The key to be inserted.
	* @param[in] val The value to be inserted, if NULL, this function will
	* @param[out] new_key The newly allocated key if not NULL.
	* @param[out] new_val The newly allocated value if not NULL.
	*/
	void insert(const _key_t& key, const _val_t* const val = NULL,
		_key_t** new_key = NULL, _val_t** new_val = NULL);
	/**
	* @brief Remove a node with key.
	* Nothing will be done if the key is not found.
	* @param[in] key The key to the data to be found and removed.
	*/
	void remove(const _key_t& key);
	/**
	* @brief Clear all the nodes.
	*/
	void clear(void);
	/**
	* @brief Find a node with the key.
	* @param[in] key The key to be found.
	* @param[out] found_key The pointer to the key in the tree if found.
	* NULL if not found.
	* @param[out] found_value The pointer to the value in the tree if
	* found. NULL if not found.
	* @return true if the key was found, false if otherwise.
	*/
	bool find(const _key_t& key, _key_t** found_key = NULL,
		_val_t** found_value = NULL) const;
	/**
	* @brief Test if the tree is empty.
	* @return true if the tree is empty, false if otherwise.
	*/
	bool is_empty(void) const;
	/**
	* @brief Test if the tree is not empty.
	* @return true if the tree is not empty, false if otherwise.
	*/
	bool is_not_empty(void) const;
	/**
	* @brief Return the first data.
	* @param[out] value The pointer to the value data if not NULL.
	* @return The first key.
	*/
	_key_t* first_data(_val_t** value = NULL) const;

	/**
	* @brief Return the next data.
	* @param[out] value The pointer to the value data if not NULL.
	* @return The next key, NULL if there is no next data.
	* @note The user must call first_data or last_data first, and do not
	* modify the tree before calling this.
	*/
	_key_t* next_data(_val_t** value = NULL) const;

	/**
	* @brief Return the last data.
	* @param[out] value The pointer to the value data if not NULL.
	* @return The last key.
	*/
	_key_t* last_data(_val_t** value = NULL) const;

	/**
	* @brief Return the previous data.
	* @param[out] value The pointer to the value data if not NULL.
	* @return The previous key, NULL if there is no previous data.
	* @note The user must call first_data or last_data first, and do not
	* modify the tree before calling this.
	*/
	_key_t* prev_data(_val_t** value = NULL) const;

	/**
	* @brief Convert the BST to string.
	* @return The converted string.
	*/	
	string c_tree<_key_t, _val_t>::to_string(void) const;
	//ostream &operator<<(ostream & os);
private:
	/**
	* @brief Create a leaf node.
	* @return The created leaf node, which has no data, no parent, no
	* child and is black.
	*/
	node_t* create_leaf_node(void);

	/**
	* @brief Remove a tree including the root itself.
	* @param[in] tree_root The root of the tree to be deleted.
	*/
	void del_tree(node_t* tree_root);

	/**
	* @brief Remove a node and its data.
	* @param[in] node The node to be deleted.
	*/
	void del_node(node_t* node);

	/**
	* @brief Find the minimum node in tree, root_node shouldn't be NULL or
	* leaf.
	* @param[in] root_node The root node.
	* @return The node with minimum value in root_node's sub tree.
	*/
	node_t* find_min_node(node_t* root_node) const;

	/**
	* @brief Find the maximum node in tree, root_node shouldn't be NULL or
	* leaf.
	* @param[in] root_node The root node.
	* @return The node with maximum value in root_node's sub tree.
	*/
	node_t* find_max_node(node_t* root_node) const;

private:
	/**
	* @brief Create a node with data.
	* @param[in] key The key for the node, will be copied.
	* @param[in] value The value for the node, will be copied.
	* @param[in] color The color for the node.
	* @return The created node.
	*/
	node_t* create_node(const _key_t& key, const _val_t* const val);

	/**
	* @brief Create a leaf node.
	* @param[in] parent The parent for the node.
	* @return The created node.
	*/
	node_t* create_leaf_node(node_t* parent);

	/**
	* @brief Insert a node when it's not an empty tree.
	* @param[in] new_node The new node to be inserted.
	*/
	void insert_node(node_t* new_node);

	/**
	* @brief Find a node with data.
	* @param[in] key The key to be compared.
	* @return The node with the key or NULL if not found.
	*/
	node_t* find_node(const _key_t& key) const;

	/**
	* @brief Find the maximum node in a node's left sub-tree.
	* The node and its left child shouldn't be leaf node.
	* @param[in] node The node to start searching.
	* @return The found node.
	*/
	node_t* find_left_max_node(node_t* node);

	/**
	* @brief Remove a node from tree. The node must have at most one
	* non-leaf child, and the node can't be root.
	* @param[in] node The node to be removed.
	*/
	void remove_node_from_tree(node_t* node);

private:
	node_t* m_root;
	int m_size;
	mutable node_t* m_cur_enumed_node;
};

// Protect the implementation from being directly included by other sources.
#define INCLUDE_FROM_C_TREE_H
#include "c_tree_impl.h"
#undef INCLUDE_FROM_C_TREE_H

#endif // C_TREE_HPP
