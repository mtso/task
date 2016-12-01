//c_tree_impl.h
//Task
//CIS 22C F2016: Xin He

#ifndef C_TREE_IMPL_H
#define C_TREE_IMPL_H
#include <vector>
#ifndef INCLUDE_FROM_C_TREE_H
#error "c_tree_impl.h should only be included from c_tree.h"
#endif // INCLUDE_FROM_C_TREE_H
#define DELETE_IF(ptr) \
	if (ptr != nullptr) { \
		delete ptr; \
		ptr = nullptr; \
	}

// Default constructor for c_tree.
template <typename _key_t, typename _val_t>
c_tree<_key_t, _val_t>::c_tree(void)
	:m_root(NULL),
	m_size(0),
	m_cur_enumed_node(NULL)
{}

// Destructor for c_tree
template <typename _key_t, typename _val_t>
c_tree<_key_t, _val_t>::~c_tree(void)
{
	// Delete the whole tree.
	if (m_root != NULL) {
		del_tree(m_root);
		m_root = NULL;
	}
}

// Clear all the nodes.
template <typename _key_t, typename _val_t>
void c_tree<_key_t, _val_t>::clear(void)
{
	if (m_root != NULL) {
		del_tree(m_root);
		m_root = NULL;
	}

	m_cur_enumed_node = NULL;
}

// Remove a tree including the root itself.
template <typename _key_t, typename _val_t>
void c_tree<_key_t, _val_t>::del_tree(node_t* tree_root)
{
	// Use a stack to avoid recursion.
	vector<node_t*> node_stack;

	// Initialize the stack with the root.
	node_stack.push_back(tree_root);

	while (node_stack.size()!=0) {
		// pop_back a node from stack.
		node_t* node = node_stack[node_stack.size() - 1];
		node_stack.pop_back();

		// push_back the node's children to the stack if it has any.
		if (node->m_left != NULL) {
			node_stack.push_back(node->m_left);
		}
		if (node->m_right != NULL) {
			node_stack.push_back(node->m_right);
		}
		// Remove the node.
		del_node(node);
	}
}

// Remove a node and its data.
template <typename _key_t, typename _val_t>
void c_tree<_key_t, _val_t>::del_node(node_t* node)
{
	if (node->m_key != NULL) {
		--m_size;
	}

	DELETE_IF(node->m_key);
	DELETE_IF(node->m_val);
	DELETE_IF(node);
}
// Get the number of items in the tree.
template <typename _key_t, typename _val_t>
int c_tree<_key_t, _val_t>::size(void) const
{
	return m_size;
}

// Insert a node with key and value.
template <typename _key_t, typename _val_t>
void c_tree<_key_t, _val_t>::insert(const _key_t& key,
	const _val_t* const val, _key_t** new_key, _val_t** new_val)
{
	/*
	* Create a new node with the data.
	*/
	node_t* new_node = create_node(key, val);
	new_node->m_left = create_leaf_node(new_node);
	new_node->m_right = create_leaf_node(new_node);

	if (m_root == NULL) {
		// Empty tree, this is the first node.
		m_root = new_node;
	}
	else {
		// Insert the node.
		insert_node(new_node);
	}

	// Reset the enumeration status since the tree has been modified.
	m_cur_enumed_node = NULL;
	if (new_key != NULL) {
		*new_key = new_node->m_key;
	}

	if (new_val != NULL) {
		*new_val = new_node->m_val;
	}

	++m_size;
}

// Convert the BST to string.
template <typename _key_t, typename _val_t>
string c_tree<_key_t, _val_t>::to_string(void) const
{
	string ret;
	vector<node_t*> node_stack;
	if (m_root != NULL) {
		node_stack.push_back(m_root);
	}

	ostringstream os;
	while (node_stack.size() != 0) {
		node_t* node = node_stack[node_stack.size() - 1];
		node_stack.pop_back();

		/*
		* Go back from node to root to find out how to draw lines.
		* If this node is in node A's left sub-tree, the node A
		* will need a "|" line to connect to it's right sub-tree.
		* But the connection from node to it's parent is different,
		* "+---" if node is left child and "L---" if right child.
		*/
		string lines;
		if (node->m_parent == NULL) {
			// Root node doesn't need line.
		} else {
			if (node == node->m_parent->m_left) {
				lines = "+---";
			}
			else {
				lines = "L---";
			}

			for (node_t* n = node->m_parent; n->m_parent != NULL;
				n = n->m_parent) {
				if (n == n->m_parent->m_left) {
					lines = "|   " + lines;
				}
				else {
					lines = "    " + lines;
				}
			}
		}
		ret += lines;

		// Print the node.
		if (node->m_key != NULL) {
			os.str("");
			os << *node->m_key;
			ret += '(' + os.str() + ',';
			if (node->m_val != NULL) {
				os.str("");
				os << *node->m_val;
				ret += os.str();
			}
			else {
				ret += "null";
			}
			ret += ')';
		} else {
			ret += "(null,null)";
		}
		// push_back the right and left child to the stack.
		if (node->m_right != NULL) {
			node_stack.push_back(node->m_right);
		}
		if (node->m_left != NULL) {
			node_stack.push_back(node->m_left);
		}

		if (node_stack.size() != 0) {
			// Append a return when it's not the last line.
			ret += "\r\n";
		}
	}
	return ret;
}

// Create a node with key and value .
template <typename _key_t, typename _val_t>
typename c_tree<_key_t, _val_t>::node_t*
c_tree<_key_t, _val_t>::create_node(const _key_t& key,
	const _val_t* const val)
{
	node_t* node = new node_t;
	node->m_left = NULL;
	node->m_right = NULL;
	node->m_parent = NULL;
	node->m_key = new _key_t(key);
	if (val != NULL) {
		node->m_val = new _val_t(*val);
	}
	else {
		node->m_val = new _val_t;
	}

	return node;
}

// Create a leaf node.
template <typename _key_t, typename _val_t>
typename c_tree<_key_t, _val_t>::node_t*
c_tree<_key_t, _val_t>::create_leaf_node(node_t* parent)
{
	node_t* node = new node_t;
	node->m_left = NULL;
	node->m_right = NULL;
	node->m_parent = parent;
	node->m_key = NULL;
	node->m_val = NULL;

	return node;
}

// Insert a node when it's not an empty tree.
template <typename _key_t, typename _val_t>
void c_tree<_key_t, _val_t>::insert_node(node_t* new_node)
{
	node_t* node = m_root;
	bool inserted = false;

	while (!inserted) {
		if (*(new_node->m_key) < *(node->m_key)) {
			/*
			* The new node is less than the current node.
			* Search the left child tree.
			*/
			if (node->m_left->m_key == NULL) {
				/*
				* The left child of the current node is a leaf.
				* Insert the new node as the left child of the
				* current node.
				*/
				del_node(node->m_left);
				node->m_left = new_node;
				new_node->m_parent = node;
				inserted = true;
			}
			else {
				/*
				* The left child of the current node is not a
				* leaf. Search the left child.
				*/
				node = node->m_left;
			}
		}
		else if (*new_node->m_key == *node->m_key) {
			/*
			* The new node is equal to the current node.
			* Replace the node with the new node and delete the
			* current node.
			* Note: the new node may still be referenced after this
			* function, we can't just replace the data and delete
			* the new node.
			*/
			new_node->m_parent = node->m_parent;
			if (node->m_parent != NULL) {
				if (node->m_parent->m_left == node) {
					node->m_parent->m_left = new_node;
				}
				else {
					node->m_parent->m_right = new_node;
				}
			}
			else {
				m_root = new_node;
			}

			del_node(new_node->m_left);
			node->m_left->m_parent = new_node;
			new_node->m_left = node->m_left;

			del_node(new_node->m_right);
			node->m_right->m_parent = new_node;
			new_node->m_right = node->m_right;
			del_node(node);
			node = NULL;
			inserted = true;
		}
		else {
			/*
			* The new node is greater than the current node.
			* Search the right child tree.
			*/
			if (node->m_right->m_key == NULL) {
				/*
				* The right child of the current node is leaf.
				* Insert the new node as the right child of the
				* current node.
				*/
				del_node(node->m_right);
				node->m_right = new_node;
				new_node->m_parent = node;
				inserted = true;
			}
			else {
				/*
				* The right child of the current node is not a
				* leaf. Search the right child.
				*/
				node = node->m_right;
			}
		}
	}
}

// Find data with data.
template <typename _key_t, typename _val_t>
bool c_tree<_key_t, _val_t>::find(const _key_t& key, _key_t** found_key,
	_val_t** found_value) const
{
	node_t* node = find_node(key);
	bool found;

	if (node != NULL) {
		if (found_key != NULL) {
			*found_key = node->m_key;
		}
		if (found_value != NULL) {
			*found_value = node->m_val;
		}
		found = true;
	}
	else {
		if (found_key != NULL) {
			*found_key = NULL;
		}
		if (found_value != NULL) {
			*found_value = NULL;
		}
		found = false;
	}

	return found;
}

// Find a node with data.
template <typename _key_t, typename _val_t>
typename c_tree<_key_t, _val_t>::node_t*
c_tree<_key_t, _val_t>::find_node(const _key_t& key) const
{
	node_t* found_node = NULL;

	for (node_t* node = m_root; (node != NULL) && (node->m_key != NULL);){
		if (key < *(node->m_key)) {
			// Search to the left
			node = node->m_left;
		}
		else if (key == *(node->m_key)) {
			// Found.
			found_node = node;
			break;
		}
		else {
			// Search to the right.
			node = node->m_right;
		}
	}

	return found_node;
}

// Find the maximum node in a node's left sub-tree.
// The node and its left child shouldn't be leaf node.
template <typename _key_t, typename _val_t>
typename c_tree<_key_t, _val_t>::node_t*
c_tree<_key_t, _val_t>::find_left_max_node(node_t* node)
{
	node_t* left_max_node;
	for (left_max_node = node->m_left;
		left_max_node->m_right->m_key != NULL;
		left_max_node = left_max_node->m_right) {
		// Nothing here.
	}
	return left_max_node;
}

// Remove a node with data.
template <typename _key_t, typename _val_t>
void c_tree<_key_t, _val_t>::remove(const _key_t& key)
{
	node_t* node = find_node(key);

	if (node == NULL) {
		// Nothing to do when the node can't be found.
	}
	else if ((node->m_parent == NULL) && (node->m_left->m_key == NULL)
		&& (node->m_right->m_key == NULL)) {
		/*
		* When a single root node is all that's left to be deleted,
		* make this an empty tree.
		*/
		clear();
	}
	else if ((node->m_left->m_key != NULL) &&
		(node->m_right->m_key != NULL)) {
		/*
		* For a node with two non-leaf children, just copy the data of
		* the max node in it's left sub-tree to this node.
		* The max node can't have two non-leaf children, otherwise its
		* right child will be greater than it.
		* So the problem is reduced to removing a node with zero or one
		* non-leaf child.
		*/
		node_t* left_max_node = find_left_max_node(node);

		/*
		* Exchange the data which will be later deleted along with the
		* deletion of left_max_node.
		*/
		_key_t* key_temp = node->m_key;
		_val_t* val_temp = node->m_val;

		node->m_key = left_max_node->m_key;
		node->m_val = left_max_node->m_val;

		left_max_node->m_key = key_temp;
		left_max_node->m_val = val_temp;

		// Now we can delete the left_max_node instead.
		remove_node_from_tree(left_max_node);
	}
	else {
		// The node has one or two leaf child(ren).
		remove_node_from_tree(node);
	}

	m_cur_enumed_node = NULL;
}

// Remove a node from tree.
// The node must have one or two leaf child(ren).
template <typename _key_t, typename _val_t>
void c_tree<_key_t, _val_t>::remove_node_from_tree(node_t* node)
{
	node_t* leaf_child;
	node_t* other_child;

	if (node->m_left->m_key != NULL) {
		leaf_child = node->m_right;
		other_child = node->m_left;
	}
	else {
		leaf_child = node->m_left;
		other_child = node->m_right;
	}

	/*
	* Disconnect node from tree along with the leaf node, then put the
	* other_child to its place.
	*/
	if (node->m_parent == NULL) {
		m_root = other_child;
	}
	else if (node == node->m_parent->m_left) {
		node->m_parent->m_left = other_child;
	}
	else {
		node->m_parent->m_right = other_child;
	}
	other_child->m_parent = node->m_parent;

	// Now delete the node.
	del_node(leaf_child);
	del_node(node);
}

// Test if the tree is empty.
template <typename _key_t, typename _val_t>
bool c_tree<_key_t, _val_t>::is_empty(void) const
{
	return m_root == NULL;
}

//  Test if the tree is not empty.
template <typename _key_t, typename _val_t>
bool c_tree<_key_t, _val_t>::is_not_empty(void) const
{
	return m_root != NULL;
}

// Find the minimum node in tree, root_node shouldn't be NULL or leaf.
template <typename _key_t, typename _val_t>
typename c_tree<_key_t, _val_t>::node_t*
c_tree<_key_t, _val_t>::find_min_node(node_t* root_node) const
{
	node_t* node;
	for (node = root_node; node->m_left->m_key != NULL;
		node = node->m_left) {
	}

	return node;
}

// Find the maximum node in tree, root_node shouldn't be NULL or leaf.
template <typename _key_t, typename _val_t>
typename c_tree<_key_t, _val_t>::node_t*
c_tree<_key_t, _val_t>::find_max_node(node_t* root_node) const
{
	node_t* node;
	for (node = root_node; node->m_right->m_key != NULL;
		node = node->m_right) {
	}
	return node;
}

// Return the first data.
template <typename _key_t, typename _val_t>
_key_t* c_tree<_key_t, _val_t>::first_data(_val_t** value) const
{
	_key_t* key = NULL;

	if (m_root != NULL) {
		m_cur_enumed_node = find_min_node(m_root);
		key = m_cur_enumed_node->m_key;
		if (value != NULL) {
			*value = m_cur_enumed_node->m_val;
		}
	}
	else {
		if (value != NULL) {
			*value = NULL;
		}
	}

	return key;
}

// Return the last data.
template <typename _key_t, typename _val_t>
_key_t* c_tree<_key_t, _val_t>::last_data(_val_t** value) const
{
	_key_t* key = NULL;

	if (m_root != NULL) {
		m_cur_enumed_node = find_max_node(m_root);
		key = m_cur_enumed_node->m_key;
		if (value != NULL) {
			*value = m_cur_enumed_node->m_val;
		}
	}
	else {
		if (value != NULL) {
			*value = NULL;
		}
	}

	return key;
}

// Return the next data.
template <typename _key_t, typename _val_t>
_key_t* c_tree<_key_t, _val_t>::next_data(_val_t** value) const
{
	node_t* next_node = NULL;

	if (m_cur_enumed_node->m_right->m_key != NULL) {
		/*
		* The right child is not a leaf node, the next node would be
		* the right child's left-most child.
		*/
		next_node = find_min_node(m_cur_enumed_node->m_right);
		m_cur_enumed_node = next_node;
	}
	else {
		/*
		* The right child is a leaf node, the next node should be the
		* first grand parent that has this node in it's left subtree.
		*/
		for (next_node = m_cur_enumed_node;
				(next_node->m_parent != NULL) &&
				(next_node == next_node->m_parent->m_right);
				next_node = next_node->m_parent) {
		}
		next_node = next_node->m_parent;
		m_cur_enumed_node = next_node;
	}

	_key_t* key = NULL;
	if (m_cur_enumed_node != NULL) {
		key = m_cur_enumed_node->m_key;
		if (value != NULL) {
			*value = m_cur_enumed_node->m_val;
		}
	}
	else {
		if (value != NULL) {
			*value = NULL;
		}
	}
	return key;
}

// Return the previous data.
template <typename _key_t, typename _val_t>
_key_t* c_tree<_key_t, _val_t>::prev_data(_val_t** value) const
{
	node_t* prev_node = NULL;

	if (m_cur_enumed_node->m_left->m_key != NULL) {
		/*
		* The left child is not a leaf node, the prev node would be
		* the left child's right-most child.
		*/
		prev_node = find_max_node(m_cur_enumed_node->m_left);
		m_cur_enumed_node = prev_node;
	}
	else {
		/*
		* The left child is a leaf node, the next node should be the
		* first grand parent that has this node in it's right subtree.
		*/
		for (prev_node = m_cur_enumed_node;
			(prev_node->m_parent != NULL) &&
			(prev_node == prev_node->m_parent->m_left);
		prev_node = prev_node->m_parent) {
		}
		prev_node = prev_node->m_parent;
		m_cur_enumed_node = prev_node;
	}

	_key_t* key = NULL;
	if (m_cur_enumed_node != NULL) {
		key = m_cur_enumed_node->m_key;
		if (value != NULL) {
			*value = m_cur_enumed_node->m_val;
		}
	}
	else {
		if (value != NULL) {
			*value = NULL;
		}
	}

	return key;
}

#endif // C_TREE_IMPL_H
