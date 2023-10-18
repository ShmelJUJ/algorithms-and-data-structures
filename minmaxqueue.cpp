#include <iostream>
#include <fstream>

struct Values
{
    int val;
    int min;
    int max;

};
class Stack {
private:
    struct Values* elements;
    int size;
    int top;

public:
    Stack() 
    {
        top = -1;
    }
    ~Stack() 
    {
        delete[] elements;
    }
    void push(int value) 
    {
        if (isFull()) 
        {
            std::cout << "Error1" << std::endl;
            return;
        }
        top++;
        if (top == 0)
        {
            elements[top].min = value;
            elements[top].max = value;
        }
        if (top > 0)
        {
            elements[top].min = std::min(elements[top - 1].min, value);
            elements[top].max = std::max(elements[top - 1].max, value);
        }
        elements[top].val = value;
       
    }
    int pop() 
    {
        if (isEmpty()) 
        {
            std::cout << "Error2" << std::endl;
            return -1;
        }
        int it = elements[top].val;
        --top;
        return it;
    }
    int getMin() const 
    {
        if (isEmpty()) 
        {
            std::cout << "Error3" << std::endl;
            return -1;
        }
       
        return elements[top].min;
    }
    int getMax() const 
    {
        if (isEmpty()) 
        {
            std::cout << "Error4" << std::endl;
            return -1;
        }
       
        return elements[top].max;
    }
    bool isEmpty() const 
    {
        return top == -1;
    }
    bool isFull() const 
    {
        return top == size - 1;
    }
    void setSize(int size_) 
    {
        size = size_;
        elements = new Values[size];
    }
};

class Queue {
private:
    Stack leftStack, rightStack;
    int minimum, maximum;

public:
    Queue(int maxSize) 
    {
        leftStack.setSize(maxSize);
        rightStack.setSize(maxSize);
        minimum = maximum = 0;
    }
    void enqueue(int value) 
    {
        if (leftStack.isFull()) 
        {
            std::cout << "Error5" << std::endl;
            return;
        }
        leftStack.push(value);
    }
    int dequeue() 
    {
        if (isEmpty()) 
        {
            std::cout << "Error6" << std::endl;
            return -1;
        }
        if (rightStack.isEmpty()) 
        {
            while (!leftStack.isEmpty()) 
            {
                rightStack.push(leftStack.pop());
            }
        }
        return rightStack.pop();
    }
    int diffMinMax()
    {
        if (leftStack.isEmpty() && rightStack.isEmpty())
        {
            return 0;
        }

        if (leftStack.isEmpty() || rightStack.isEmpty())
        {
            minimum = leftStack.isEmpty() ? rightStack.getMin() : leftStack.getMin();
        }
        else
        {
            minimum = std::min(leftStack.getMin(), rightStack.getMin());
        }

        if (leftStack.isEmpty() || rightStack.isEmpty())
        {
            maximum = leftStack.isEmpty() ? rightStack.getMax() : leftStack.getMax();
        }
        else
        {
            maximum = std::max(leftStack.getMax(), rightStack.getMax());
        }
        return maximum-minimum;

    }
    bool isEmpty() const 
    {
        return leftStack.isEmpty() && rightStack.isEmpty();
    }
};

int main(int argc, char* argv[])
{

    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);


    if (!inputFile.is_open())
    {
        std::cerr << "Error" << std::endl;
        return -1;
    }

    int count;
    int value;
    char symbol;


    inputFile >> count;
    Queue q(count);

    while (count != 0) 
    {
        inputFile >> symbol;
        switch (symbol) 
        {
        case '+':
            inputFile >> value;
            q.enqueue(value);
            break;
        case '-':
            q.dequeue();
            break;
        case '?':
            outputFile << q.diffMinMax() << std::endl;
            break;
        }
        count--;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}