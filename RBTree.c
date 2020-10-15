#include "RBTree.h"
#include <stdlib.h>

// -------------------------- const definitions -------------------------

/**
 * @var int SUCCESS_VALUE
 * @brief The value to return id there was a success in the function.
 */
const int SUCCESS_VALUE = 1;

/**
 * @var int FAILER_VALUE
 * @brief The value if there is a failer in the function.
 */
const int FAILER_VALUE = 0;

/**
 * @var int VALUE_WAS_FOUND_VALUE
 * @brief The value if the data is already exists in the tree.
 */
const int VALUE_WAS_FOUND_VALUE = 1;

// -------------------------- functions declaration -------------------------

/**
 * @brief The function returns a pointer to the node's parent.
 * @param node the node to find it's parent.
 * @return A pointer to the node's parent.
 */
static Node* getParent(Node* node);

/**
 * @brief The function returns a pointer to the node's grandparent.
 * @param node the node to find it's grandparent.
 * @return A pointer to the node's grandparent.
 */
static Node* getGrandParent(Node* node);

/**
 * @brief The function returns a pointer to the node's brother.
 * @param node the node to find it's brother.
 * @return A pointer to the node's brother.
 */
static Node* getBrother(Node* node);

/**
 * @brief The function returns a pointer to the node's uncle.
 * @param node the node to find it's uncle.
 * @return A pointer to the node's uncle.
 */
static Node* getUncle(Node* node);

/**
 * @brief The function to rotate the grandparent's node.
 * @param node the node to rotate.
 */
static void rotateLeft(Node* node);

/**
 * @brief The function to rotate the grandparent's node.
 * @param node the node to rotate.
 */
static void rotateRight(Node* node);

/**
 * @brief The function to repair the tree after insertion.
 * @param node the node that was inserted.
 */
static void repairNode(Node* n);

/**
 * @brief The function to operate the func function on the nodes in the tree.
 * @param argc the number of arguments the user entered.
 * @param argv the array of the arguments.
 * @return 0 if there were not problems, and 1 if there were problems with the CLI.
 */
static int forEachInOrder(Node *n, forEachFunc func, void *args);

/**
 * @brief The function free the tree' node by node, in the right order.
 * @param n the node to free.
 * @param freeFunc the function to free th data.
 */
static void freeInOrder(Node *n, FreeFunc freeFunc);

/**
 * @brief The recursive function to add a new node to the tree.
 * @param root The tree's root.
 * @param newNode The new node to add to the tree.
 * @param compFunc The function to compare the data in the noeds.
 */
static void addHelper(Node* root, Node* newNode, CompareFunc compFunc);

// ------------------------------ functions -----------------------------

RBTree *newRBTree(CompareFunc compFunc, FreeFunc freeFunc)
{
    if (compFunc == NULL || freeFunc == NULL)
    {
        return NULL;
    }
    RBTree *myTree = (RBTree*) malloc(sizeof(RBTree));
    myTree->compFunc = compFunc;
    myTree->freeFunc = freeFunc;
    myTree->size = 0;
    myTree->root = NULL;
    return myTree;
}

static Node* getParent(Node* node)
{
    if (node == NULL)
    {
        return NULL;
    }
    return node->parent;
}

static Node* getGrandParent(Node* node)
{
    Node* p = getParent(node);
    return getParent(p);
}

static Node* getBrother(Node* node)
{
    Node *node2 = getParent(node);
    if (node2 == NULL)
    {
        return NULL;
    }
    if (node == node2->right)
    {
        return node2->left;
    }
    else
    {
        return node2->right;
    }
}

static Node* getUncle(Node* node)
{
    Node* p = getParent(node);
    return getBrother(p);
}

static void rotateLeft(Node* node)
{
    Node* temp = node->right;
    Node* parent = getParent(node);

    node->right = temp->left;
    temp->left = node;
    node->parent = temp;
    if (node->right != NULL)
    {
        node->right->parent = node;
    }
    if (parent != NULL)
    {
        if (node == parent->left)
        {
            parent->left = temp;
        }
        else if (node == parent->right)
        {
            parent->right = temp;
        }
    }
    temp->parent = parent;
}

static void rotateRight(Node* node)
{
    Node* temp = node->left;
    Node* parent = getParent(node);

    node->left = temp->right;
    temp->right = node;
    node->parent = temp;
    if (node->left != NULL)
    {
        node->left->parent = node;
    }
    if (parent != NULL)
    {
        if (node == parent->left)
        {
            parent->left = temp;
        }
        else if (node == parent->right)
        {
            parent->right = temp;
        }
    }
    temp->parent = parent;
}

static void repairNode(Node* n)
{
    Node* grand = getGrandParent(n);
    if (getParent(n) == NULL)
    {
        n->color = BLACK;
    }
    else if (getParent(n)->color == BLACK)
    {
        return;
    }
    else if (getUncle(n) != NULL && getUncle(n)->color == RED)
    {
            getUncle(n)->color = BLACK;
            getParent(n)->color = BLACK;
            getGrandParent(n)->color = RED;
            repairNode(getGrandParent(n));
    }
    else
    {
        if (n == getParent(n)->right && getParent(n) == getGrandParent(n)->left)
        {
            rotateLeft(getParent(n));
            n = n->left;
        }
        else if (n == getParent(n)->left && getParent(n) == getGrandParent(n)->right)
        {
            rotateRight(getParent(n));
            n = n->right;
        }
        if (n == getParent(n)->left)
        {
            rotateRight(getGrandParent(n));
        }
        else
        {
            rotateLeft(getGrandParent(n));
        }
        getParent(n)->color = BLACK;
        grand->color = RED;
    }
}

static void addHelper(Node* root, Node* newNode, CompareFunc compFunc)
{
    if (root != NULL && compFunc(newNode->data, root->data) < 0)
    {
        if (root->left != NULL)
        {
            addHelper(root->left, newNode, compFunc);
            return;
        }
        else
        {
            root->left = newNode;
        }
    }
    else if (root != NULL)
    {
        if (root->right != NULL)
        {
            addHelper(root->right, newNode, compFunc);
            return;
        }
        else
        {
            root->right = newNode;
        }
    }
    newNode->parent = root;
    newNode->left = NULL;
    newNode->right = NULL;
}

int addToRBTree(RBTree *tree, void *data)
{
    if (tree == NULL || data == NULL)
    {
        return FAILER_VALUE;
    }
    if (containsRBTree(tree, data) == VALUE_WAS_FOUND_VALUE)
    {
        return FAILER_VALUE;
    }
    tree->size = tree->size + 1;
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;
    if (tree->root == NULL)
    {
        newNode->color = BLACK;
        newNode->parent = NULL;
        newNode->left = NULL;
        newNode->right = NULL;
        tree->root = newNode;
        return SUCCESS_VALUE;
    }
    addHelper(tree->root, newNode, tree->compFunc);
    repairNode(newNode);

    while (getParent(tree->root) != NULL)
    {
        tree->root = getParent(tree->root);
    }
    return SUCCESS_VALUE;
}

int containsRBTree(RBTree *tree, void *data)
{
    if (tree == NULL || data == NULL)
    {
        return 0;
    }
    Node * p = tree->root;
    void* nodeData;
    while (p != NULL)
    {
        nodeData = p->data;
        if (tree->compFunc(nodeData, data) == 0)
        {
            return VALUE_WAS_FOUND_VALUE;
        }
        else if (tree->compFunc(p->data, data) < 0)
        {
            p = p->right;
        }
        else
        {
            p = p->left;
        }
    }
    return 0;
}

static int forEachInOrder(Node *n, forEachFunc func, void *args)
{
    if (n == NULL)
    {
        return SUCCESS_VALUE;
    }
    if (forEachInOrder(n->left, func, args) == FAILER_VALUE)
    {
        return FAILER_VALUE;
    }
    if (func(n->data, args) == FAILER_VALUE)
    {
        return FAILER_VALUE;
    }
    if (forEachInOrder(n->right, func, args) == FAILER_VALUE)
    {
        return FAILER_VALUE;
    }
    return SUCCESS_VALUE;
}

int forEachRBTree(RBTree *tree, forEachFunc func, void *args)
{
    if (tree == NULL)
    {
        return SUCCESS_VALUE;
    }
    if (tree->root == NULL)
    {
        return SUCCESS_VALUE;
    }
    if (forEachInOrder(tree->root, func, args) == FAILER_VALUE)
    {
        return FAILER_VALUE;
    }
    return SUCCESS_VALUE;
}

static void freeInOrder(Node *n, FreeFunc freeFunc)
{
    if (n == NULL)
    {
        return;
    }
    freeInOrder(n->left, freeFunc);
    freeInOrder(n->right, freeFunc);
    freeFunc(n->data);
    if (getParent(n) != NULL)
    {
        if (getParent(n)->right == n)
        {
            getParent(n)->right = NULL;
        }
        else
        {
            getParent(n)->left = NULL;
        }
    }
    free(n);
    n = NULL;
}

void freeRBTree(RBTree *tree)
{
    Node* p;
    if (tree == NULL)
    {
        return;
    }
    p = tree->root;
    if (p == NULL)
    {
        return;
    }
    freeInOrder(p, tree->freeFunc);
    free(tree);
    tree = NULL;
}
