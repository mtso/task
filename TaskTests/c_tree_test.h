#ifndef C_TREE_TEST_H
#define C_TREE_TEST_H


/**
* @brief Unit test for c_tree.
*/
class c_tree_test {
public:
	virtual void test(void);

private:
	void test_misc(void);
	void test_insert(void);
	void test_remove(void);
};
#endif