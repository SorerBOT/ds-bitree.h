#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

static void freeNode(TreeNode* node)
{
    omp_destroy_lock(&node->lock);
    free(node);
}

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

    omp_init_lock(&node->lock);

    return node;
}

TreeNode* insertNode(TreeNode* root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    TreeNode* current = root;
    omp_lock_t* lock_to_unset = NULL;
    omp_set_lock(&current->lock);
    while (true)
    {
        if (lock_to_unset != NULL)
        {
            omp_unset_lock(lock_to_unset);
        }
        lock_to_unset = &current->lock;

        if (current->data >= data)
        {
            if (current->left == NULL)
            {
                current->left = createNode(data);
                break;
            }
            else
            {
                omp_set_lock(&current->left->lock);
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
                omp_set_lock(&current->right->lock);
                current = current->right;
                continue;
            }
        }
    }
    if (lock_to_unset != NULL)
    {
        omp_unset_lock(lock_to_unset);
    }
    return root;
}

TreeNode* deleteNode(TreeNode* root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }

    omp_set_lock(&root->lock);

    TreeNode* current = root;
    TreeNode* previous = NULL;

    while (true)
    {
        if (current->data == data)
        {
            break;
        }
        TreeNode* descendant = (data <= current->data)
            ? current->left
            : current->right;

        if (descendant == NULL)
        {
            if (previous != NULL)
            {
                omp_unset_lock(&previous->lock);
            }
            omp_unset_lock(&current->lock);
            return root;
        }

        omp_set_lock(&descendant->lock);
        if (previous != NULL)
        {
            omp_unset_lock(&previous->lock);
        }
        previous = current;
        current = descendant;
    }

    /* Deletion of a node without descendants */
    if (current->left == NULL && current->right == NULL)
    {
        if (current == root)
        {
            omp_unset_lock(&root->lock);
            freeNode(current);
            return NULL;
        }

        if (previous->left == current)
        {
            previous->left = NULL;
            omp_unset_lock(&current->lock);
            freeNode(current);
            omp_unset_lock(&previous->lock);
            return root;
        }

        previous->right = NULL;
        omp_unset_lock(&current->lock);
        freeNode(current);
        omp_unset_lock(&previous->lock);
        return root;
    }

    /* Deletion of a node with a single descendant */
    if (current->left == NULL || current->right == NULL)
    {
        TreeNode* descendant = (current->left != NULL)
            ? current->left
            : current->right;

        omp_set_lock(&descendant->lock);

        current->data = descendant->data;
        current->left = descendant->left;
        current->right = descendant->right;

        omp_unset_lock(&descendant->lock);
        freeNode(descendant);
        omp_unset_lock(&current->lock);
        if (previous != NULL)
        {
            omp_unset_lock(&previous->lock);
        }

        return root;
    }

    /* Deletion of node with two descendants */
    if (previous != NULL)
    {
        omp_unset_lock(&previous->lock);
    }
    TreeNode* predecessor_min_node_in_right_subtree = current;
    TreeNode* min_node_in_right_subtree = current->right;
    previous = NULL;
    omp_set_lock(&min_node_in_right_subtree->lock);
    while (min_node_in_right_subtree->left != NULL)
    {
        if (previous != NULL)
        {
            omp_unset_lock(&previous->lock);
        }
        omp_set_lock(&min_node_in_right_subtree->left->lock);
        previous = min_node_in_right_subtree;
        predecessor_min_node_in_right_subtree = min_node_in_right_subtree;
        min_node_in_right_subtree = min_node_in_right_subtree->left;
    }

    if (previous != NULL)
    {
        omp_unset_lock(&previous->lock);
    }

    if (predecessor_min_node_in_right_subtree == current)
    {
        current->right = min_node_in_right_subtree->right;
    }
    else
    {
        predecessor_min_node_in_right_subtree->left = min_node_in_right_subtree->right;
    }
    current->data = min_node_in_right_subtree->data;
    omp_unset_lock(&min_node_in_right_subtree->lock);
    freeNode(min_node_in_right_subtree);
    omp_unset_lock(&current->lock);

    return root;
}

bool searchNode(TreeNode* root, int data)
{
    if (root == NULL)
    {
        return false;
    }

    TreeNode* current = root;
    omp_set_lock(&current->lock);
    while (true)
    {
        if (current->data == data)
        {
            omp_unset_lock(&current->lock);
            return true;
        }
        else if (current->data > data)
        {
            if (current->left == NULL)
            {
                omp_unset_lock(&current->lock);
                return false;
            }
            else
            {
                omp_set_lock(&current->left->lock);
                omp_unset_lock(&current->lock);
                current = current->left;
                continue;
            }
        }
        else
        {
            if (current->right == NULL)
            {
                omp_unset_lock(&current->lock);
                return false;
            }
            else
            {
                omp_set_lock(&current->right->lock);
                omp_unset_lock(&current->lock);
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
    omp_set_lock(&current->lock);
    while (current->left != NULL)
    {
        omp_set_lock(&current->left->lock);
        omp_unset_lock(&current->lock);
        current = current->left;
    }
    omp_unset_lock(&current->lock);
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
        omp_set_lock(&root->lock);

        TreeNode* left = root->left;
        TreeNode* right = root->right;

        freeTree(left);
        freeTree(right);

        omp_unset_lock(&root->lock);
        freeNode(root);
    }
}
