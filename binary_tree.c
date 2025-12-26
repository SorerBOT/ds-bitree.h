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

bool searchNode(TreeNode* root, int data)
{
    if (root == NULL)
    {
        return false;
    }
    else if (root->data == data)
    {
        return true;
    }
    else if (root->data > data)
    {
        if (root->left == NULL)
        {
            return false;
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
            return false;
        }
        else
        {
            return searchNode(root->right, data);
        }
    }
}

TreeNode* findMin(TreeNode* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->left == NULL)
    {
        return root;
    }
    else
    {
        return findMin(root->left);
    }
}

void inorderTraversal(TreeNode* root)
{
    if (root->left != NULL)
    {
        inorderTraversal(root->left);
    }
    else
    {
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(TreeNode* root)
{
    printf("%d ", root->data);
    if (root->left != NULL)
    {
        preorderTraversal(root->left);
    }
    else
    {
        preorderTraversal(root->right);
    }
}

void postorderTraversal(TreeNode* root)
{
    if (root->left != NULL)
    {
        postorderTraversal(root);
    }
    else
    {
        postorderTraversal(root->right);
        printf("%d ", root->data);
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
