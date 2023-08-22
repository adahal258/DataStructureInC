/*
Name:- Aashutosh Dahal
CS 241, Lab08
binarytree.c is the program that creates a binarysearch tree and perform
the operation like printing the leaves, printing tree, removing nodes and so on.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "binarytree.h"

int isBSTHelper(struct TreeNode* root, int minVal, int maxVal);
void printHelper(struct TreeNode* root);
void printHelperVerbose(struct TreeNode* root);
void printHelperLeaves(struct TreeNode* root);
/* Alloc a new node with given data. */
struct TreeNode* createNode(char data)
{
    struct TreeNode* newNode = malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
/* Insert data at appropriate place in BST, return new tree root. */
struct TreeNode* insertBST(struct TreeNode* root, char data)
{
    /* creates new node from null root. */
    if (root == NULL)
        return createNode(data);
    /*recursion:- either go to left or right.*/
    else if (data < root->data) 
        root->left = insertBST(root->left, data);
    else 
        root->right = insertBST(root->right, data);
    return root;
}

/* Remove data from BST pointed to by rootRef, changing root if necessary.
 * For simplicity's sake, always choose node's in-order
 *   successor in the two-child case.
 * Memory for removed node should be freed.
 * Return 1 if data was present, 0 if not found. */
int removeBST(struct TreeNode** rootRef, char data) 
{
    struct TreeNode* root = *rootRef;
    if (root != NULL) 
    {
        /*Call the above removeBST method with root->left and root->right 
        if root->data >data or root->data<data.present in the subtree.*/
        if (root->data > data )
            return removeBST(&root->left, data);
        else if (root->data < data)
            return removeBST(&root->right, data);
        else 
        {
            /*Both left and right reference is NULL*/
            if (root->left == NULL && root->right == NULL) 
            {
                free(root);
                *rootRef = NULL;
            } 
            /*only one child*/
            else if (root->left == NULL) 
            {
                *rootRef = NULL;
                free(root);
            } 
            else if (root->right == NULL) 
            {
                *rootRef = root->left;
                free(root); 
            } 
            /* Both child/subtree */
            else 
            {
                struct TreeNode* subTree = root->right;
                while (subTree->left != NULL) 
                {
                    subTree = subTree->left;
                }
                root->data = subTree->data;
                return removeBST(&root->right, subTree->data);
            }
        }
    }
    else
    {
        return 0;
    }
    return 1;
}

/* Return minimum value in non-empty binary search tree. */
char minValueBST(struct TreeNode* root)
{
    struct TreeNode* curr = root;
    if (root != NULL) 
    {
        /* since left subtree has lesser value than root.*/
        while (curr->left != NULL)
        { 
            curr = curr->left;
        }
        return curr->data;
    }
    else
        exit(1); 
}

/* Return maximum depth of tree. Empty tree has depth 0. */
int maxDepth(struct TreeNode* root)
{
    if (root != NULL)
    {
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        if(leftDepth > rightDepth)
        {
            return leftDepth+1;
        }
        else
        {
            return rightDepth+1;
        }
    }
    return 0;
}

/* A tree is balanced if both subtrees are balanced and
 * the difference in height between the subtrees is no more than 1.
 * Return 1 if tree is balanced, 0 if not. */
int isBalanced(struct TreeNode* root)
{
    if (root != NULL) 
    {
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        if (abs(leftDepth - rightDepth) <= 1 && isBalanced(root->left)&& isBalanced(root->right)) 
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

/* return 1 if is a binary search tree other false*/
/* compare with the maximum int value and minimum int value from limit.*/
int isBSTHelper(struct TreeNode* root, int minVal, int maxVal) 
{
    return root == NULL || (root->data >= minVal && root->data <= maxVal
                   && isBSTHelper(root->left, minVal, root->data - 1)
                   && isBSTHelper(root->right, root->data + 1, maxVal));
}


/* Return 1 if tree is a binary search tree, 0 if not. */
int isBST(struct TreeNode* root) 
{
    return isBSTHelper(root, INT_MIN, INT_MAX);
}
/* Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printHelper(struct TreeNode* root)
{
    if (root != NULL) 
    {
        /* using recursion to print left sub tree.*/
        printHelper(root->left); 
        printf("%c ", root->data);
        /* using recursion to print right sub tree.*/
        printHelper(root->right); 
    }
    else
    {
        return;   
    }
}
/*  to print new line */
void printTree(struct TreeNode* root)
{
    printHelper(root);
    printf("\n");
}

/* Print data for leaves on single line,
 * separated with spaces, ending with newline.*/
void printHelperLeaves(struct TreeNode* root)
{
if (root != NULL)
{
    if (root->left == NULL && root->right == NULL)
    {
        printf("%c ", root->data);
    }
    printHelperLeaves(root->left); /*using recursion to print left sub tree.*/ 
    printHelperLeaves(root->right);  /*using recursion to print right sub tree.*/ 
    if (root->left == NULL && root->right == NULL) 
    {
    }
}
else
{
    return;
}
}
/* new line character at the end of printLeaves*/
void printLeaves(struct TreeNode* root)
{
 printHelperLeaves(root);
 printf("\n");
}

/* Print data for a preorder tree traversal on a single line
 * as a sequence of (data, depth) pairs
 * separated with spaces, ending with newline.
 * (The root node has a depth of 1)
 *
 *  So, the tree
 *
 *      A
 *     / \
 *    B   C
 *   / \
 *  D   E
 *
 * will produce the output
 * (A,1) (B,2) (D,3) (E,3) (C,2) 
 */
void printHelperVerbose(struct TreeNode* root)
{
    static int subTree = 1;
    if (root != NULL) 
    {
        printf("(%c,%d) ", root->data, subTree);
        subTree++; 
    }
    else
    {   
        return;
    }
    printHelperVerbose(root->left);
    subTree--; /* negation after the left subtree is finished*/
    subTree++; 
    printHelperVerbose(root->right); 
    subTree--;
}

void printTreeVerbose(struct TreeNode* root)
{
   printHelperVerbose(root);
   printf("\n");
}

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root)
{
    if (root != NULL) 
    {
        freeTree(root->left); 
        freeTree(root->right);
        free(root); 
    }
    else
    {
        return;
    }
}

