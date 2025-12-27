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

    TreeNode* current = root;
    while (true)
    {
        if (current->data >= data)
        {
            if (current->left == NULL)
            {
                current->left = createNode(data);
                break;
            }
            else
            {
                current = current->left;
                continue;
            }
        }
        else
        {
            if (current->right == NULL)
            {
                current->right = createNode(data);
                break;
            }
            else
            {
                current = current->right;
                continue;
            }
        }
    }
    return root;
}

TreeNode* deleteNode(TreeNode* root, int data)
{
    if (root->data == data && (root->left == NULL || root->right == NULL))
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

    TreeNode* current = root;
    while (true)
    {

        if (current->data == data)
        {
            return true;
        }
        else if (current->data > data)
        {
            if (current->left == NULL)
            {
                return false;
            }
            else
            {
                current = current->left;
                continue;
            }
        }
        else
        {
            if (current->right == NULL)
            {
                return false;
            }
            else
            {
                current = current->right;
                continue;
            }
        }
    }
}

TreeNode* findMin(TreeNode* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    TreeNode* current = root;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

void inorderTraversal(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
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
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    if (root->left != NULL)
    {
        preorderTraversal(root->left);
    }
    if (root->right != NULL)
    {
        preorderTraversal(root->right);
    }
}

void postorderTraversal(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL)
    {
        postorderTraversal(root);
    }
     
    if (root->right != NULL)
    {
        postorderTraversal(root->right);
    }

    printf("%d ", root->data);
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
