#define CUNIT_IMPLEMENTATION
#include "../external/cunit.h"

#include "../binary_tree.h"

CUNIT_TEST(create_tree)
{
    TreeNode* node_10 = createNode(10);
    node_10 = insertNode(node_10, 5);
    node_10 = insertNode(node_10, 15);
    node_10 = insertNode(node_10, 3);
    node_10 = insertNode(node_10, 7);
    node_10 = insertNode(node_10, 12);
    node_10 = insertNode(node_10, 18);

    CUNIT_ASSERT_PTR_NOT_NULL(node_10);
    CUNIT_ASSERT_INT_EQ(node_10->data, 10);

    TreeNode* node_5 = node_10->left;
    CUNIT_ASSERT_PTR_NOT_NULL(node_5);
    CUNIT_ASSERT_INT_EQ(node_5->data, 5);

    TreeNode* node_3 = node_5->left;
    CUNIT_ASSERT_PTR_NOT_NULL(node_3);
    CUNIT_ASSERT_INT_EQ(node_3->data, 3);
    CUNIT_ASSERT_PTR_NULL(node_3->left);
    CUNIT_ASSERT_PTR_NULL(node_3->right);

    TreeNode* node_7 = node_5->right;
    CUNIT_ASSERT_PTR_NOT_NULL(node_7);
    CUNIT_ASSERT_INT_EQ(node_7->data, 7);
    CUNIT_ASSERT_PTR_NULL(node_7->left);
    CUNIT_ASSERT_PTR_NULL(node_7->right);

    TreeNode* node_15 = node_10->right;
    CUNIT_ASSERT_PTR_NOT_NULL(node_15);
    CUNIT_ASSERT_INT_EQ(node_15->data, 15);

    TreeNode* node_12 = node_15->left;
    CUNIT_ASSERT_PTR_NOT_NULL(node_12);
    CUNIT_ASSERT_INT_EQ(node_12->data, 12);
    CUNIT_ASSERT_PTR_NULL(node_12->left);
    CUNIT_ASSERT_PTR_NULL(node_12->right);

    TreeNode* node_18 = node_15->right;
    CUNIT_ASSERT_PTR_NOT_NULL(node_18);
    CUNIT_ASSERT_INT_EQ(node_18->data, 18);
    CUNIT_ASSERT_PTR_NULL(node_18->left);
    CUNIT_ASSERT_PTR_NULL(node_18->right);
}

CUNIT_TEST(min_node)
{
    TreeNode* tree = createNode(10);
    TreeNode* minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 10);

    insertNode(tree, 5);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 5);

    insertNode(tree, 15);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 5);

    insertNode(tree, 3);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 3);

    insertNode(tree, 7);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 3);

    insertNode(tree, 12);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 3);

    insertNode(tree, 18);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 3);
}

CUNIT_TEST(search_node)
{

}
