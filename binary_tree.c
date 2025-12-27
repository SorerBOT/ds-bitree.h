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

TreeNode* insertNode(TreeNode* root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    if (root->data >= data)
    {
        if (root->left == NULL)
        {
            root->left = createNode(data);
        }
        else
        {
            insertNode(root->left, data);
        }
    }
    else
    {
        if (root->right == NULL)
        {
            root->right = createNode(data);
        }
        else
        {
            insertNode(root->right, data);
        }
    }
    return root;
}

TreeNode* deleteNode(TreeNode* root, int data)
{
    if (root->data == data && root->left == NULL || root->right == NULL)
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        TreeNode* descendant = (root->left != NULL)
            ? root->left
            : root->right;
        free(root);
        return descendant;
    }


    TreeNode* current = root;
    TreeNode* previous = root;

    while (current != NULL)
    {
        if (current->data == data)
        {
            break;
        }
        previous = current;
        current = (current->data > data)
            ? current->left
            : current->right; 
    }

    if (current == NULL)
    {
        return root;
    }
    if (current->left == NULL || current->right == NULL)
    {
        TreeNode* descendant = (current->left != NULL)
                ? current->left
                : current->right;
        if (previous->left == current)
        {
            previous->left = descendant;
        }
        else
        {
            previous->right = descendant;
        }
        free(current);
        return root;
    }

    TreeNode* predecessor_min_node_in_right_subtree = current;
    TreeNode* min_node_in_right_subtree = current->right;

    while (min_node_in_right_subtree->left != NULL)
    {
        predecessor_min_node_in_right_subtree = min_node_in_right_subtree;
        min_node_in_right_subtree = min_node_in_right_subtree->left;
    }

    int min_node_data = min_node_in_right_subtree->data;
    if (predecessor_min_node_in_right_subtree == current)
    {
        predecessor_min_node_in_right_subtree->right = min_node_in_right_subtree->right;
    }
    else
    {
        predecessor_min_node_in_right_subtree->left = min_node_in_right_subtree->right;
    }
    free(min_node_in_right_subtree);
    current->data = min_node_data;

    return root;
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
