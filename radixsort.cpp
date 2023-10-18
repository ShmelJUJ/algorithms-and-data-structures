#include <fstream>
#include <iostream>


void radixsort(char** arr, int n, int m, int k) 
{
    char** arr_ = new char* [n+1];

    for (int i = m - 1; i >= m - k; i--) 
    {
        int A[256];
        for (int i = 0; i < 256; i++)
        {
            A[i] = 0;
        }

        for (int j = 0; j < n; j++) 
        {
            A[(int)arr[j][i]]++;
        }

        int score = 0;
        for (int j = 0; j < 256; j++) 
        {
            int tmp = A[j];
            A[j] = score;
            score += tmp;
        }

        for (int j = 0; j < n; j++) 
        {
            char ch = arr[j][i];
            arr_[A[(int)ch]] = arr[j];
            A[(int)ch]++;
        }

        for (int j = 0; j < n; j++) 
        {
            arr[j] = arr_[j];
        }

    }

    delete[] arr_;
}

int main(int argc, char* argv[]) 
{

    int n, m, k;

    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);


    if (!inputFile.is_open()) 
    {
        std::cout << "Error";
        return -1;
    }

    inputFile >> n >> m >> k;
    char** array = new char* [n + 1];

    for (int i = 0; i < n; ++i)
    {
        array[i] = new char[m + 1];
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inputFile >> array[j][i];
        }
    }

    radixsort(array, n, m, k);

    for (int i = 0; i < n; ++i) 
    {
        outputFile << array[i][0];
    }
    for (int i = 0; i < n; i++) 
    {
        delete[] array[i];
    }

    delete[] array;
    inputFile.close();
    outputFile.close();

    return 0;
}
