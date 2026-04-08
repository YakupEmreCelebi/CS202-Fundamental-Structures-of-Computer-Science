/**
 * Title: AVL Trees and Heaps
 * Author: Yakup Emre Celebi
 * ID: 22302267
 * Section: 2
 * Homework: 2
 * Description: Sequencing quality monitor using AVL tree
 */

#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
    long long value;
    int height;

    long long value_count;
    long long subtree_size;
    long long subtree_sum;

    Node *left;
    Node *right;

    Node(long long val)
    {
        value = val;
        height = 1;
        value_count = 1;
        subtree_size = 1;
        subtree_sum = val;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree
{
private:
    Node *root;

    int height(Node *N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    long long getSize(Node *N)
    {
        if (N == nullptr)
            return 0;
        return N->subtree_size;
    }

    long long getSum(Node *N)
    {
        if (N == nullptr)
            return 0;
        return N->subtree_sum;
    }

    void updateNode(Node *N)
    {
        if (N != nullptr)
        {
            N->height = 1 + max(height(N->left), height(N->right));
            N->subtree_size = N->value_count + getSize(N->left) + getSize(N->right);
            N->subtree_sum = (N->value * N->value_count) + getSum(N->left) + getSum(N->right);
        }
    }

    int getBalance(Node *N)
    {
        if (N == nullptr)
        {
            return 0;
        }
        else
        {
            return height(N->left) - height(N->right);
        }
    }

    Node *rightRotate(Node *y)
    {
        Node *yL = y->left;
        Node *yLR = yL->right;
        yL->right = y;
        y->left = yLR;

        updateNode(y);
        updateNode(yL);

        return yL;
    }

    Node *leftRotate(Node *x)
    {
        Node *xR = x->right;
        Node *xRL = xR->left;
        xR->left = x;
        x->right = xRL;

        updateNode(x);
        updateNode(xR);

        return xR;
    }

    Node *insert(Node *node, long long key)
    {

        if (node == nullptr)
        {
            return new Node(key);
        }

        else if (key < node->value)
        {
            node->left = insert(node->left, key);
        }
        else if (key > node->value)
        {
            node->right = insert(node->right, key);
        }
        else
        {
            node->value_count++;
        }

        updateNode(node);
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->value)
        {
            return rightRotate(node);
        }

        else if (balance < -1 && key > node->right->value)
        {
            return leftRotate(node);
        }
        else if (balance > 1 && key > node->left->value)
        {

            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        else if (balance < -1 && key < node->right->value)
        {
            Node *rightRotateTop = rightRotate(node->right);
            node->right = rightRotateTop;

            return leftRotate(node);
        }

        return node;
    }

    Node *remove(Node *root, long long key)
    {
        if (root == nullptr)
        {
            return root;
        }

        if (key < root->value)
        {
            root->left = remove(root->left, key);
        }
        else if (key > root->value)
        {
            root->right = remove(root->right, key);
        }
        else
        {
            if (root->value_count > 1)
            {

                root->value_count--;
            }
            else
            {
                if ((root->left == nullptr) || (root->right == nullptr))
                {
                    Node *temp;

                    if (root->left != nullptr)
                    {
                        temp = root->left;
                    }
                    else
                    {
                        temp = root->right;
                    }

                    if (temp == nullptr)
                    {
                        temp = root;
                        root = nullptr;
                    }
                    else
                    {
                        *root = *temp;
                    }
                    delete temp;
                }
                else
                {
                    Node *temp = minValueNode(root->right);

                    root->value = temp->value;
                    root->value_count = temp->value_count;

                    temp->value_count = 1;
                    root->right = remove(root->right, temp->value);
                }
            }
        }
        if (root == nullptr)
        {
            return root;
        }

        updateNode(root);

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
        {
            return rightRotate(root);
        }

        else if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        else if (balance < -1 && getBalance(root->right) <= 0)
        {
            return leftRotate(root);
        }

        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    long long getSumOfSmallest(Node *node, long long P)
    {
        if (node == nullptr || P == 0)
        {
            return 0;
        }

        long long leftSize = getSize(node->left);

        if (P <= leftSize)
        {
            return getSumOfSmallest(node->left, P);
        }

        long long totSum = getSum(node->left);

        long long remP = P - leftSize;

        long long takeCount = 0;

        if (remP < node->value_count)
        {
            takeCount = remP;
        }
        else
        {
            takeCount = node->value_count;
        }

        totSum = totSum + (takeCount * node->value);

        remP = remP - takeCount;

        if (remP == 0)
        {
            return totSum;
        }
        else
        {
            long long rightSum = getSumOfSmallest(node->right, remP);

            totSum = totSum + rightSum;
            return totSum;
        }
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

public:
    AVLTree()
    {
        root = nullptr;
    }

    void insert(long long key)
    {
        root = insert(root, key);
    }

    void remove(long long key)
    {
        root = remove(root, key);
    }

    long long getSumOfSmallest(long long P)
    {
        return getSumOfSmallest(root, P);
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: ./monitor <input_file>" << "\n";
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile)
    {
        cout << "Error opening file!" << "\n";
        return 1;
    }

    long long N, W, P;
    inputFile >> N >> W >> P;

    long long *scores = new long long[N];
    for (long long i = 0; i < N; i++)
    {
        inputFile >> scores[i];
    }

    inputFile.close();

    AVLTree tree;
    long long global_sum = 0;

    for (long long i = 0; i < W; i++)
    {
        tree.insert(scores[i]);
    }

    long long local_sum = tree.getSumOfSmallest(P);
    cout << local_sum;
    global_sum += local_sum;

    for (long long i = W; i < N; i++)
    {
        tree.remove(scores[i - W]);

        tree.insert(scores[i]);
        local_sum = tree.getSumOfSmallest(P);

        cout << " " << local_sum;
        global_sum += local_sum;
    }

    cout << "\nGlobal Sum: " << global_sum << "\n";

    delete[] scores;

    return 0;
}