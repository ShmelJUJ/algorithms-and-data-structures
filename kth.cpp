#include <fstream>
#include <iostream>


int partition(int* arr, int left, int right)
{
    if (left > right) 
    {
        std::cout << "Error1";
        return -2;
    }

    int pivot = arr[(left+right) / 2];
    int i = left;
    int j = right;

    while (i <= j)
    {
        while (arr[i] < pivot)
        { 
            i++; 
        }
        while (arr[j] > pivot)
        { 
            j--; 
        }
        if (i < j)
        {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
        else if (i == j)
        {
            i++;
            j--;
        }
    }

    return i;
}

void quickSort(int* arr, int left, int right, int k1, int k2)
{
    if (left == right || left > k2 || right < k1)
    {
        return;
    }
        int pivotIndex = partition(arr, left, right);
        quickSort(arr, left, pivotIndex - 1, k1, k2);
        quickSort(arr, pivotIndex, right, k1, k2);

}


int main(int argc, char* argv[]) 
{
    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    if (!inputFile) 
    {
        std::cout << "Error";
        return -1;
    }

    int n, k1, k2, A, B, C;
    inputFile >> n;
    int* array = new int[n + 1];
    inputFile >> k1 >> k2 >> A >> B >> C >> array[1] >> array[2];

    for (int i = 3; i <= n; ++i) 
    {
        array[i] = A * array[i - 2] + B * array[i - 1] + C;
    }
        
    quickSort(array, 1, n, k1, k2);

    for (int i = k1; i < k2; i++) 
    { 
        outputFile << array[i] << ' ';
    }
    outputFile << array[k2];
    
    delete[] array;
    inputFile.close();
    outputFile.close();

    return 0;
}