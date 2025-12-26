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
