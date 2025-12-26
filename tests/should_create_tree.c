#include "../external/cunit.h"
#include "../binary_tree.h"

CUNIT_TEST(min_node)
{
    TreeNode* tree = createNode(10);
    insertNode(tree, 5);
    insertNode(tree, 15);
    insertNode(tree, 3);
    insertNode(tree, 7);
    insertNode(tree, 12);
    insertNode(tree, 18);

    TreeNode* minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 3);
}
