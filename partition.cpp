#include <iostream>

long long partition(int n, int k);

int main() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    std::cout << partition(n, k);
    return 0;
}

long long partition(int n, int k)
{
    if (k > n)
    {
        std::cout << "Error";
        return -1;
    }

    if (n > 500 || k > 500)
    {
        std::cout << "Error";
        return -2;
    }

    long long* current = new long long[n + 1];
    long long* previous = new long long[n + 1];

    for (int i = 0; i < n; i++)
    {
        current[i] = 0;
        previous[i] = 0;
    }

    for (int j = 1; j <= k; ++j)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (j > i)
            {
                current[i] = 0;
            }
            else if (i == 0 || i == j)
            {
                current[i] = 1;
            }
            else if (i > j)
            {
                current[i] = previous[i - 1] + current[i - j];
            }
        }

        std::swap(previous, current);

        for (int i = 0; i < n; i++)
        {
            current[i] = 0;
        }
    }

    long long result = previous[n];
    delete[] previous;
    delete[] current;

    return result;
}