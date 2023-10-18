#include <iostream>
#include <fstream>

class HashSet 
{
private:
    static const int TABLE_SIZE = 10007;

    struct Node 
    {
        int key;
        Node* next;
        Node(int k) : key(k), next(nullptr) {}
    };

    Node** table;

    static int hash(int key) 
    {
        return std::abs(key) % TABLE_SIZE;
    }

public:
    HashSet() 
    {
        table = new Node * [TABLE_SIZE]();
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }

    }

    ~HashSet() 
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            Node* node = table[i];
            while (node != nullptr)
            {
                Node* prev = node;
                node = node->next;
                delete prev;
            }
        }
        delete[] table;
    }

    void add(int key) 
    {
        int index = hash(key);
        Node* newNode = new Node(key);
        newNode->next = table[index];
        table[index] = newNode;
    }

    void remove(int key) 
    {
        int index = hash(key);
        Node* prev = nullptr;
        Node* current = table[index];

        while (current != nullptr) 
        {
            if (current->key == key) 
            {
                if (prev == nullptr) 
                {
                    table[index] = current->next;
                }
                else 
                {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    bool find(int key) 
    {
        int index = hash(key);
        Node* current = table[index];

        while (current != nullptr) 
        {
            if (current->key == key) 
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

int main(int argc, char* argv[])
{
    HashSet mySet;
    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);


 /*   std::ifstream inputFile("input6.txt");
    std::ofstream outputFile("output.txt");*/

    if (!inputFile.is_open())
    {
        std::cout << "Error";
        return -1;
    }

    int n;
    char sign;
    inputFile >> n;
    for (int i = 0; i < n; i++) 
    {
        int val;
        inputFile >> sign;
        switch (sign) 
        {
        case '+':
            inputFile >> val;
            mySet.add(val);
            break;
        case '-':
            inputFile >> val;
            mySet.remove(val);
            break;
        case '?':
            inputFile >> val;
            if (mySet.find(val)) 
            {
                outputFile << "true" << "\n";
            }
            else 
            {
                outputFile << "false" << "\n";
            }
            break;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}