#include <iostream>
#include <fstream>


class AATree 
{

private:

    struct Node 
    {
        int key;
        int level;
        Node* left;
        Node* right;
        Node(int key, int level, Node* left = nullptr, Node* right = nullptr) : key(key), level(level), left(left), right(right) {}
    };

    Node* root;

    static Node* skew(Node* t) 
    {
        if (t == nullptr)
        {
            return nullptr;
        }
        if (t->left != nullptr && t->level == t->left->level) 
        {
            Node* leftChild = t->left;
            t->left = leftChild->right;
            leftChild->right = t;
            return leftChild;
        }
        return t;
    }

    static Node* split(Node* t) 
    {
        if (t == nullptr)
        {
            return nullptr;
        }
        if (t->right != nullptr && t->right->right != nullptr && t->level == t->right->right->level) 
        {
            Node* rightChild = t->right;
            t->right = rightChild->left;
            rightChild->left = t;
            rightChild->level++;
            return rightChild;
        }
        return t;
    }

    static Node* decreaseLevel(Node* t)
    {
        int res;
        if (t->left == nullptr || t->right == nullptr) 
        {
            res = 1;
        }
        else 
        {
            res = std::min(t->left->level, t->right->level) + 1;
        }

        if (res < t->level)
        {
            t->level = res;
            if (t->right != nullptr && t->right->level > t->level)
            {
                t->right->level = res;
            }
        }
        return t;
    }

    Node* insert(Node* t, int key) 
    {
        if (t == nullptr) 
        {
            return new Node(key, 1);
        }
        if (key < t->key) 
        {
            t->left = insert(t->left, key);
        }
        else if (key > t->key) 
        {
            t->right = insert(t->right, key);
        }

        t = skew(t);
        t = split(t);

        return t;
    }

    static Node* find(Node* t) 
    {
        while (t->left != nullptr) 
        {
            t = t->left;
        }
        return t;
    }

    Node* remove(Node*& t, int key) 
    {
        if (t == nullptr)
        {
            return nullptr;
        }
        if (key < t->key) 
        {
            t->left = remove(t->left, key);
        }
        else if (key > t->key) 
        {
            t->right = remove(t->right, key);
        }
        else 
        {
            if (t->left == nullptr && t->right == nullptr) 
            {
                delete t;
                return nullptr;
            }
            if (t->left == nullptr)
            {
                Node* temp = t->right;
                delete t;
                return temp;
            }
            if (t->right == nullptr) 
            {
                Node* temp = t->left;;
                delete t;
                return temp;
            }
        }
        t = decreaseLevel(t);
        t = skew(t);
        if (t->right != nullptr)
        {
            t->right = skew(t->right);
            t->right->right = skew(t->right->right);
        }
        t = split(t);
        t->right = split(t->right);

        return t;
    }

    bool search(Node* t, int key) 
    {
        if (t == nullptr)
        {
            return false;
        }
        if (key < t->key)
        {
            return search(t->left, key);
        }
        if (key > t->key) 
        {
            return search(t->right, key);
        }
        return true;
    }
  
    int getLevel(Node* node = nullptr) const
    {
        if (node == nullptr)
        {
            node = root;
        }

        if (node == nullptr)
        {
            return 0;
        }

        return node->level;
    }

    void deleteTree(Node* t)
    {
        if (t == nullptr)
        {
            return;
        }
        deleteTree(t->left);
        deleteTree(t->right);
        delete t;
    }


public:

    AATree() : root(nullptr) 
    {
    }

    ~AATree() 
    {
        deleteTree(root);
    }

    bool search(int key) 
    {
        return search(root, key);
    }

    void insert(int key, std::ofstream& outFile)
    {
        root = insert(root, key);
        outFile << getLevel() << '\n';
    }

    void remove(int key, std::ofstream& outFile)
    {
        root = remove(root, key);
        outFile << getLevel() << '\n';
    }

};

int main(int argc, char* argv[])
{
    int n;
    char symbol;
    int value;
    AATree tree;

    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    if (!inputFile.is_open()) 
    {
        std::cout << "Error";
        return -1;
    }

    inputFile >> n;

    for (int i = 0; i < n; i++)
    {
        inputFile >> symbol;
        switch (symbol)
        {
            case '+':
                inputFile >> value;
                tree.insert(value, outputFile);
                break;
            case '-':
                inputFile >> value;
                tree.remove(value, outputFile);
                break;
            case '?':
                inputFile >> value;
                if (tree.search(value)) 
                {
                    outputFile << "true" << '\n';
                }
                else 
                {
                    outputFile << "false" << '\n';
                }
                break;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
