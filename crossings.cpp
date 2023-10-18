#include <iostream>
#include <fstream>

struct data
{
    int x1;
    int x2;
};

void merge(data* arr, int left, int mid, int right, long long& invCounter, int line)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    data* leftArr = new data[n1];
    data* rightArr = new data[n2];

    for (int i = 0; i < n1; i++)
    {
        leftArr[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++)
    {
        rightArr[j] = arr[mid + j + 1];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (line == 1)
        {
            if (leftArr[i].x1 <= rightArr[j].x1) 
            {
                arr[k] = leftArr[i];
                i++;
            }
            else 
            {
                arr[k] = rightArr[j];
                invCounter += n1 - i;
                j++;
            }
        }
        else 
        {
            if (leftArr[i].x2 <= rightArr[j].x2) 
            {
                arr[k] = leftArr[i];
                i++;
            }
            else 
            {
                arr[k] = rightArr[j];
                invCounter += n1 - i;
                j++;
            }
        }
        k++;

    }

    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void sort(data* arr, int left, int right, long long& invCounter, int line)
{
    if (right > left)
    {
        int mid = left + (right - left) / 2;
        sort(arr, left, mid, invCounter, line);
        sort(arr, mid + 1, right, invCounter, line);
        merge(arr, left, mid, right, invCounter, line);
    }
}


int main(int argc, char* argv[])
{
    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) 
    {
        std::cout << "Error" << '\n';
        return -1;
    }

    int n;
    inputFile >> n;
    long long counter = 0;
    long long same = 0;
    long long res = 0;
    data* arr = new data[n];

    for (int i = 0; i < n; i++)
    {
        inputFile >> arr[i].x1 >> arr[i].x2;
    }

    sort(arr, 0, n - 1, counter, 0);

    if (n > 100)
    {
        for (int i = 1; i < n; i++)
        {
            if (arr[i].x1 == arr[i - 1].x1)
            {
                same++;
            }
        }
    }

    counter = 0;

    sort(arr, 0, n - 1, counter, 1);

    if (n < 100)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (arr[i].x1 == arr[j].x1 || arr[i].x2 == arr[j].x2)
                {
                    same++;
                }
            }
        }
    }
    else
    {
        for (int i = 1; i < n; i++)
        {
            if (arr[i].x2 == arr[i - 1].x2)
            {
                same++;
            }
        }
    }

    res = counter + same;

    std::cout << res;

    delete[] arr;
    inputFile.close();


    return 0;
}