#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data);

TreeNode* insertNode(TreeNode* root, int data);
TreeNode* deleteNode(TreeNode* root, int data);

bool searchNode(TreeNode* root, int data);
TreeNode* findMin(TreeNode* root);

void inorderTraversal(TreeNode* root);
void preorderTraversal(TreeNode* root);
void postorderTraversal(TreeNode* root);
void freeTree(TreeNode* root);

#endif /* BINARY_TREE_H */
