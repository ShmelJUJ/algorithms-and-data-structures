#include <iostream>
#include <fstream>

struct student 
{
    double average;
    int ID;
};

int partition(student* data, int left, int right)
{
    if (left > right) 
    {
        std::cout << "Error";
        return -1;
    }

    double pivot = data[left].average;
    int i = left + 1;
    int j = right;

    while (true)
    {
        while (i <= j && data[i].average <= pivot)
        {
            i++;
        }
        while (data[j].average >= pivot && j >= i)
        {
            j--;
        }
        if (j < i)
        {
            break;
        }
        std::swap(data[i], data[j]);
    }

    std::swap(data[left], data[j]);

    return j;
}

void quickSort(student* data, int left, int right)
{
    if (left < right)
    {
        int pivotIndex = partition(data, left, right);
        quickSort(data, left, pivotIndex - 1);
        quickSort(data, pivotIndex + 1, right);
    }
}


int main(int argc, char* argv[])
{
    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) 
    {
        std::cout << "Error!";
        return -1;
    }

    int size;
    inputFile >> size;
    student* info = new student[size];

    for (int i = 0; i < size; ++i) 
    {
        inputFile >> info[i].average;
        info[i].ID = i + 1;
    }

    quickSort(info,0, size - 1);

    std::cout << info[0].ID << " " << info[size / 2].ID << " " << info[size - 1].ID;
    delete [] info;
    inputFile.close();

    return 0;
}
