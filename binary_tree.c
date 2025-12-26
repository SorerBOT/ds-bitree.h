#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

TreeNode* createNode(int data)
{
    TreeNode* node = malloc(sizeof(TreeNode));

    if (node == NULL)
    {
        fprintf(stderr, "malloc()");
        exit(EXIT_FAILURE);
    }

    *node = (TreeNode)
    {
        .data = data,
        .left = NULL,
        .right = NULL,
    };

    return node;
}

TreeNode* searchNode(TreeNode* root, int data)
{
    if (root->data == data)
    {
        return root;
    }
    else if (root->data > data)
    {
        if (root->left == NULL)
        {
            return NULL;
        }
        else
        {
            return searchNode(root->left, data);
        }
    }
    else
    {
        if (root->right == NULL)
        {
            return NULL;
        }
        else
        {
            return searchNode(root->right, data);
        }
    }
}

TreeNode* findMin(TreeNode* root)
{
    if (root->left != NULL)
    {
        return findMin(root);
    }
    else
    {
        return root;
    }
}

void freeTree(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        TreeNode* left = root->left;
        TreeNode* right = root->left;

        free(root);
        freeTree(left);
        freeTree(right);
    }
}
