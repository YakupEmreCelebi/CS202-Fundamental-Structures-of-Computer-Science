/**
 * Title: Binary Search Trees
 * Author : Yakup Emre Celebi
 * ID: 22302267
 * Section : 2
 * Homework : 1
 * Description : Binary Search Tree with insert, retrieve, delete and height find logic
 */

#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode
{
    int key;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val)
    {
        key = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree
{
private:
    TreeNode *root;

    int heightHelper(TreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else
        {
            return max(heightHelper(node->right), heightHelper(node->left)) + 1;
        }
    }

public:
    BinarySearchTree()
    {
        root = nullptr;
    }

    void insert(int x)
    {
        TreeNode *newNode = new TreeNode(x);
        TreeNode *currentNode = root;
        TreeNode *prevOfCurrentNode = nullptr;

        if (root == nullptr)
        {
            root = newNode;
        }
        else
        {
            while (currentNode != nullptr)
            {

                prevOfCurrentNode = currentNode;

                if (x > currentNode->key)
                {
                    currentNode = currentNode->right;
                }
                else
                {
                    currentNode = currentNode->left;
                }
            }

            if (prevOfCurrentNode->key > x)
            {
                prevOfCurrentNode->left = newNode;
            }
            else
            {
                prevOfCurrentNode->right = newNode;
            }
        }
    }

    bool retrieve(int x)
    {

        if (root == nullptr)
        {
            return false;
        }
        else if (root->key == x)
        {
            return true;
        }

        TreeNode *currentNode = root;

        while (currentNode != nullptr)
        {

            if (x > currentNode->key)
            {
                currentNode = currentNode->right;
            }
            else if (x < currentNode->key)
            {
                currentNode = currentNode->left;
            }
            else
            {
                return true;
            }
        }

        return false;
    }

    void deleteKey(int x)
    {

        TreeNode *nodeToDelete = nullptr;
        TreeNode *currentNode = root;
        TreeNode *prevOfCurrentNode = nullptr;

        while (currentNode != nullptr)
        {

            if (x > currentNode->key)
            {
                prevOfCurrentNode = currentNode;
                currentNode = currentNode->right;
            }
            else if (x < currentNode->key)
            {
                prevOfCurrentNode = currentNode;
                currentNode = currentNode->left;
            }
            else
            {
                nodeToDelete = currentNode;
                break;
            }
        }

        if (nodeToDelete == nullptr)
        {
            return;
        }

        // Case 0
        if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr)
        {

            if (nodeToDelete == root)
            {
                delete root;
                root = nullptr;
                return;
            }

            if (prevOfCurrentNode->right == nodeToDelete)
            {
                prevOfCurrentNode->right = nullptr;
            }
            else if (prevOfCurrentNode->left == nodeToDelete)
            {
                prevOfCurrentNode->left = nullptr;
            }
            delete nodeToDelete;
            nodeToDelete = nullptr;

            return;
        }

        // Case 1
        if (nodeToDelete->left != nullptr && nodeToDelete->right == nullptr)
        {
            if (nodeToDelete == root)
            {
                root = nodeToDelete->left;
                delete nodeToDelete;
                return;
            }

            if (prevOfCurrentNode->key > nodeToDelete->key)
            {
                prevOfCurrentNode->left = nodeToDelete->left;
            }
            else
            {
                prevOfCurrentNode->right = nodeToDelete->left;
            }

            delete nodeToDelete;
            nodeToDelete = nullptr;
        }
        else if (nodeToDelete->right != nullptr && nodeToDelete->left == nullptr)
        {

            if (nodeToDelete == root)
            {
                root = nodeToDelete->right;
                delete nodeToDelete;
                return;
            }

            if (prevOfCurrentNode->key > nodeToDelete->key)
            {
                prevOfCurrentNode->left = nodeToDelete->right;
            }
            else
            {
                prevOfCurrentNode->right = nodeToDelete->right;
            }

            delete nodeToDelete;
            nodeToDelete = nullptr;
        }

        // Case 2
        // I used the inorder successor for Case 2.
        else if (nodeToDelete->right != nullptr && nodeToDelete->left != nullptr)
        {
            TreeNode *nodeToCopy = nodeToDelete->right;
            TreeNode *prevOfNodeToCopy = nodeToDelete;
            while (nodeToCopy->left != nullptr)
            {
                prevOfNodeToCopy = nodeToCopy;
                nodeToCopy = nodeToCopy->left;
            }

            nodeToDelete->key = nodeToCopy->key;

            if (prevOfNodeToCopy->left == nodeToCopy)
            {
                prevOfNodeToCopy->left = nodeToCopy->right;
            }
            else
            {
                prevOfNodeToCopy->right = nodeToCopy->right;
            }
            delete nodeToCopy;
        }
    }

    int height()
    {
        return heightHelper(root);
    }
};

int main()
{
    BinarySearchTree myTree;

    myTree.insert(40);
    myTree.insert(20);
    myTree.insert(60);
    myTree.insert(10);
    myTree.insert(30);
    myTree.insert(50);
    myTree.insert(70);
    myTree.insert(5);
    myTree.insert(35);
    myTree.insert(32);

    cout << "Tree height: " << myTree.height() << endl;

    return 0;
}