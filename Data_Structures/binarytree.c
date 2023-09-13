/****
*NAME : Pratik Basyal
*CS 241
***/

#include<stdio.h>
#include<stdlib.h>
#include"binarytree.h"


/* Alloc a new node with given data. */
struct TreeNode* createNode(char data)
{
    struct TreeNode* new_node = malloc(sizeof(struct TreeNode));
    new_node -> data = data;
    new_node -> left = NULL;
    new_node -> right = NULL;

    return new_node;
}

/* Insert data at appropriate place in BST, return new tree root. */
struct TreeNode* insertBST(struct TreeNode* root, char data)
{
    struct TreeNode* new_node = malloc(sizeof(struct TreeNode));

    /*if root is null*/
    if(root == NULL)
    {
        new_node -> data = data;
        new_node -> right = new_node -> left = NULL;

        return new_node;
    }
    
    free(new_node);

    /*following BST rules, inserting data*/
    if(data < root-> data)
    {
        root -> left = insertBST(root -> left, data);
    }

    else if(data > root -> data)
    {
        root -> right = insertBST(root -> right, data);
    }

    return root;
}

/* Remove data from BST pointed to by rootRef, changing root if necessary.
 * For simplicity's sake, always choose node's in-order
 *   successor in the two-child case.
 * Memory for removed node should be freed.
 * Return 1 if data was present, 0 if not found. */
int removeBST(struct TreeNode** rootRef, char data) 
{
    struct TreeNode* temp = *rootRef;
    struct TreeNode* successor = NULL;

    if (*rootRef == NULL) 
    {
        return 0; /*data not found*/
    } 
    
    else if (data < (*rootRef)->data) 
    {
        return removeBST(&((*rootRef)->left), data);
    } 
    
    else if (data > (*rootRef)->data) 
    {
        return removeBST(&((*rootRef)->right), data);
    } 
    
    else 
    {
        /*Case 1: no children*/
        if ((*rootRef)->left == NULL && (*rootRef)->right == NULL) 
        {
            free(*rootRef);
            *rootRef = NULL;
            return 1;
        }
        /*Case 2: one child*/
        else if ((*rootRef)->left == NULL) 
        {
            *rootRef = (*rootRef)->right;
            free(temp);
            return 1;
        } 
        
        else if ((*rootRef)->right == NULL) 
        {
            *rootRef = (*rootRef)->left;
            free(temp);
            return 1;
        }
        
        /*Case 3: two children*/
        else 
        {
            successor = (*rootRef)->right;
            while (successor->left != NULL) 
            {
                successor = successor->left;
            }
            (*rootRef)->data = successor->data;
            return removeBST(&((*rootRef)->right), successor->data);
        }
    }
}

/* Return minimum value in non-empty binary search tree. */
char minValueBST(struct TreeNode* root) 
{
    while (root->left != NULL) 
    {
        root = root->left;
    }
    return root->data;
}

/* Return maximum depth of tree. Empty tree has depth 0. */
int maxDepth(struct TreeNode* root) 
{
    int leftDepth, rightDepth, max_Depth;

    if (root == NULL) 
    {
        return 0;
    } 
    else 
    {
        leftDepth = maxDepth(root->left);
        rightDepth = maxDepth(root->right);

        if(leftDepth > rightDepth)
        {
            max_Depth = leftDepth;
        }

        else
        {
            max_Depth = rightDepth;
        }
    }
    return 1 + max_Depth; /* max depth of whole tree*/
}

/* A tree is balanced if both subtrees are balanced and
 * the difference in height between the subtrees is no more than 1.
 * Return 1 if tree is balanced, 0 if not. */
int isBalanced(struct TreeNode* root)
{
    int left_height, right_height;
    if(root == NULL)
    {
        return 1;
    }

    left_height = maxDepth(root -> left);
    right_height = maxDepth(root -> right);

    if(abs(left_height - right_height) <= 1 && isBalanced(root -> left) && isBalanced(root -> right))
    {
        return 1;
    }

    return 0;
}

/* Return 1 if tree is a binary search tree, 0 if not. */
int isBST(struct TreeNode* root)
{
    struct TreeNode* stack[1000];  /*a stack to hold the nodes*/
    int top = -1;  /*initialize top of stack as -1*/

    struct TreeNode* curr = root;
    struct TreeNode* prev = NULL;

    if (root == NULL) 
    {
        return 1;
    }
    
    while (curr != NULL || top != -1) 
    {
        while (curr != NULL) 
        {
            stack[++top] = curr;
            curr = curr->left;
        }
        
        curr = stack[top--];
        
        if (prev != NULL && curr->data <= prev->data)
        {
            return 0;
        }
        
        prev = curr;
        curr = curr->right;
    }
    return 1;
}


/**
 * tried recursive method and didn't work to print new line.
 * Instead I went with this method
 * This Function :
 * Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */

void printTree(struct TreeNode* root) 
{
    struct TreeNode* stack[100];
    struct TreeNode* curr = root;
    int top = -1;

    if (root == NULL) 
    {
        printf("\n");
        return;
    }

    while (curr != NULL || top != -1) 
    {
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }
        curr = stack[top--];
        printf("%c ", curr->data);
        curr = curr->right;
    }
    printf("\n");
}

/* Print data for leaves on single line,
 * separated with spaces, ending with newline.*/
void printLeaves(struct TreeNode* root) 
{

    struct TreeNode* stack[100];
    int top = -1;
    struct TreeNode* curr = root;

    if (root == NULL) 
    {
        printf("\n");
        return;
    }

    while (curr != NULL || top != -1) 
    {
        while (curr != NULL) 
        {
            stack[++top] = curr;
            curr = curr->left;
        }

        curr = stack[top--];

        if (curr->left == NULL && curr->right == NULL) 
        {
            printf("%c ", curr->data);
        }

        curr = curr->right;
    }
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
void printTreeVerbose(struct TreeNode* root) 
{
    struct TreeNode* stack[100]; /*stack for iterative traversal*/
    int depthStack[100]; /*stack to keep track of depths*/
    int top = -1; /*stack top*/
    int depth = 1; /*starting depth*/
    stack[++top] = root; /*push the root onto the stack*/
    depthStack[top] = depth; /*push the depth onto the stack*/

    if (root == NULL) 
    {
        printf("\n");
        return;
    }

    while (top >= 0) /*while the stack is not empty*/
    {
        struct TreeNode* node = stack[top]; /*get the top node*/
        depth = depthStack[top--]; /*get the depth and pop the top*/

        printf("(%c,%d) ", node->data, depth); /*print the node's data and depth*/

        if (node->right != NULL) /*push the right child onto the stack*/
        { 
            stack[++top] = node->right;
            depthStack[top] = depth + 1;
        }

        if (node->left != NULL) /*push the left child onto the stack*/
        {
            stack[++top] = node->left;
            depthStack[top] = depth + 1;
        }
    }
    printf("\n");
}

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root) 
{
    if (root == NULL) return;
    
    freeTree(root->left);
    
    freeTree(root->right);
    
    free(root);
}

