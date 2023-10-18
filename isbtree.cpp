#include <cmath>
#include <fstream>
#include <iostream>

int parse_num(char*& ptr, char sep) 
{
    int number = 0;
    int sign = 1;
    while (*ptr != sep) 
    {
        if (*ptr == '-') 
        {
            sign = -1;
            ptr++;
            continue;
        }
        number = number * 10 + (*ptr - '0');
        ptr++;
    }
    return number * sign;
}


class ParseNode 
{
public:
    int num;
    bool leaf;
    int keysCount;
    int* keys;
    int childrenCount;
    bool isUsed;
    int* childrenNums;

    ~ParseNode() 
    {
        if(!leaf) 
        {
            delete[] childrenNums;
        }
        delete[] keys;
    }

    ParseNode(char* str) 
    {
        childrenCount = 0;
        isUsed = false;
        char* ptr = str;
        if (ptr[0] == 'l') 
        {
            leaf = true;
            ptr += 8;
        }
        else {
            leaf = false;
            ptr += 10;
        }

        num = parse_num(ptr, ' ');
        ptr += 2;

        keysCount = parse_num(ptr, ':');
        ptr += 2;

        int* keys = new int[this->keysCount];
        for (int i = 0; i < this->keysCount; i++) 
        {
            if (i != this->keysCount - 1) 
            {
                keys[i] = parse_num(ptr, ' ');
            }
            else 
            {
                keys[i] = parse_num(ptr, ')');
            }
            ptr += 1;
        }
        this->keys = keys;

        ptr += 2;

        if (!this->leaf) 
        {
            childrenCount = parse_num(ptr, ':');
            ptr += 2;
            int* children = new int[this->childrenCount];
            for (int i = 0; i < this->childrenCount; ++i) 
            {
                if (i != this->childrenCount - 1) 
                {
                    children[i] = parse_num(ptr, ' ');
                }
                else 
                {
                    children[i] = parse_num(ptr, ')');
                }
                ptr += 1;
            }
            this->childrenNums = children;
        }
    }
};

class Node 
{
public:
    int num;
    bool leaf;
    int keysCount;
    int* keys;
    int childrenCount;
    Node** children;

    Node()
        : num(0),
        leaf(false),
        keysCount(0),
        keys(nullptr),
        childrenCount(0),
        children(nullptr) {
        if (childrenCount == 0) 
        {
            children = nullptr;
        }
        else 
        {
            children = new Node * [childrenCount] { nullptr };
        }
    }

    ~Node() 
    {
    }

    Node(ParseNode* node)
        : num(node->num),
        leaf(node->leaf),
        keysCount(node->keysCount),
        childrenCount(node->childrenCount)
        {
        keys = new int[keysCount];
        for(int i = 0; i < keysCount; i++) 
        {
            keys[i] = node->keys[i];
        }
        if (childrenCount == 0) 
        {
            children = nullptr;
        }
        else 
        {
            children = new Node * [childrenCount] { nullptr };
        }

    }


    bool operator>(const Node& node) const 
    { 
        return this->num > node.num; 
    }
    bool operator<(const Node& node) const 
    { 
        return this->num < node.num;
    }
    bool operator==(const Node& node) const 
    { 
        return this->num == node.num; 
    }

    bool KeysSeqIsValid() const
    {
        for (int i = 1; i < keysCount; i++) 
        {
            if (keys[i - 1] > keys[i])
            {
                return false;
            }
        }
        return true;
    }

    bool keysCountIsValid(int t, bool isRoot = false) const
    {
        if (isRoot) 
        {
            return 2 * t - 1 >= keysCount;
        }

        return t - 1 <= keysCount && keysCount <= 2 * t - 1;
    }

    bool childrenCountIsValid(int t) const 
    {
        if (!leaf) 
        {
            return childrenCount == keysCount + 1;
        }
        return true;
    }
};

int search(int n, ParseNode** arr,  int value)
{
    for (int i = 0; i < n; i++) 
    {
        if (arr[i] != nullptr && arr[i]->num == value) 
        {
            return i;
        }
    }
    return -1;
}

class BTree 
{
private:
    bool broken;


    void buildTree(ParseNode** arr, Node* curNode, ParseNode* curParseNode)
    {
        if (!curNode->leaf) 
        {
            for (int i = 0; i < curParseNode->childrenCount; i++) 
            {
                int searchIndex = search(N, arr, curParseNode->childrenNums[i]);
                if (searchIndex == -1 || arr[searchIndex]->isUsed) 
                {
                    broken = true;
                    curNode->childrenCount = i;
                    return;
                }
                arr[searchIndex]->isUsed = true;
                curNode->children[i] = new Node(arr[searchIndex]);
                buildTree(arr, curNode->children[i], arr[searchIndex]);
            }
        }
    }

    int DFS(int lvl, int max, Node* node, int min)
    {
        if (broken) 
        {
            return lvl;
        }
        if (!node->keysCountIsValid(t, root == node)) 
        {
            broken = true;
            return lvl;
        }
        if (!node->KeysSeqIsValid()) 
        {
            broken = true;
            return lvl;
        }
        if (!node->childrenCountIsValid(t)) 
        {
            broken = true;
            return lvl;
        }
        if (node->keys[0] < min) 
        {
            broken = true;
            return lvl;
        }
        if (node->keys[node->keysCount - 1] > max) 
        {
            broken = true;
            return lvl;
        }

        if (!node->leaf) 
        {
            int tempLvl = 0;
            for (int i = 0; i < node->childrenCount; i++) 
            {
                if (i == 0) 
                {
                    tempLvl = DFS( lvl + 1, node->keys[i], node->children[i], min);
                }
                else if (i == node->childrenCount - 1)
                {
                    if (DFS( lvl + 1, max, node->children[i], node->keys[i - 1]) != tempLvl)
                    {
                        broken = true;
                        return lvl;
                    }
                }
                else 
                {
                    if (DFS( lvl + 1, node->keys[i], node->children[i],  node->keys[i - 1]) != tempLvl)
                    {
                        broken = true;
                        return lvl;
                    }
                }
            }
            return tempLvl;
        }

        return lvl;
    }

    void deleteTree(Node* n) 
    {
        if (n != nullptr) 
        {
            if (!n->leaf) 
            {
                for (int i = 0; i < n->childrenCount; i++) 
                {
                    if(n->children[i] != nullptr) 
                    {
                        deleteTree(n->children[i]);
                    }
                }
                delete[] n->children;
            }
            delete[] n->keys;
            delete n;
        }
    }

public:
    Node* root;
    int N;
    int t;


    BTree() 
    {

    };

    ~BTree() 
    {
        deleteTree(root);
    }

    BTree(std::ifstream& input) 
    {
        int rootNum;
        input >> this->N >> this->t >> rootNum;
        broken = false;
        root = nullptr;
        ParseNode* tempRoot = nullptr;
        input.ignore();
        ParseNode** nodes = new ParseNode * [N] { nullptr };
        char* str = new char[2048] {0};

        for (int i = 0; i < abs(N); i++) 
        {

            input.getline(str, 2048);;
            nodes[i] = new ParseNode(str);
            if (nodes[i]->num == rootNum) 
            {
                tempRoot = nodes[i];
            }

        }
        delete[] str;

        if (tempRoot == nullptr) 
        {
            for (int i = 0; i < N; i++)
            {
                delete nodes[i];
            }
            delete[] nodes;
            nodes = nullptr;
            broken = true;
            return;
        }

        root = new Node(tempRoot);

        buildTree(nodes, root, tempRoot);

        for(int i = 0; i < N; i++) 
        {
            delete nodes[i];
        }
        delete[] nodes;
    }



    bool isValid() 
    {
        if (broken) 
        {
            return false;
        }

        if (root != nullptr) 
        {
            if (!(root->keysCount >= 1 && root->keysCount <= 2 * t - 1 && (root->leaf || root->childrenCount == root->keysCount + 1))) 
            {
                return false;
            }
            DFS( 0, 2147483647, root, -2147483648);
        }
        else {
            return false;
        }
        return !broken;
    }
};

int main(int argc, char* argv[]) 
{
    std::ifstream inputFile(argv[1]);
    BTree* tree = new BTree(inputFile);

    if (tree->isValid()) 
    {
        std::cout << "yes";
    }
    else 
    {
        std::cout << "no";
    }

    inputFile.close();
    delete tree;
    return 0;
}
