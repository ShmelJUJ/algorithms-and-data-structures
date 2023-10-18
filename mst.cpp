#include <iostream>
#include<fstream>

struct Edge
{
    int u, v, weight;
};

class Mst
{
public:
    int* p;

    Mst(int size)
    {
        p = new int[size];
        for (int i = 0; i < size; i++)
        {
            p[i] = i;
        }
    }
    ~Mst()
    {
        delete[] p;
    }

    int get(int v)
    {
        return (v == p[v]) ? v : (p[v] = get(p[v]));
    }

    void unite(int a, int b)
    {
        a = get(a);
        b = get(b);
        if (a != b)
        {
            p[a] = b;
        }
    }

    int kruskal(Edge* edges, int m_)
    {
        int cost = 0;
        mergeSort(edges, 0, m_ - 1);
        for (int i = 0; i < m_; ++i)
        {
            int a = edges[i].u;
            int b = edges[i].v;
            int l = edges[i].weight;

            if (get(a) != get(b)) {
                cost += l;
                unite(a, b);
            }
        }
        return cost;
    }

    static void merge(Edge* edges, int left, int mid, int right) 
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Edge* leftArr = new Edge[n1];
        Edge* rightArr = new Edge[n2];

        for (int i = 0; i < n1; i++)
        {
            leftArr[i] = edges[left + i];
        }
        for (int j = 0; j < n2; j++)
        {
            rightArr[j] = edges[mid + 1 + j];
        }

        int i = 0;
        int j = 0;
        int k = left;
        while (i < n1 && j < n2)
        {
            if (leftArr[i].weight <= rightArr[j].weight)
            {
                edges[k] = leftArr[i];
                i++;
            }
            else
            {
                edges[k] = rightArr[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            edges[k] = leftArr[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            edges[k] = rightArr[j];
            j++;
            k++;
        }

        delete[] leftArr;
        delete[] rightArr;
    }

    void mergeSort(Edge* edges, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            mergeSort(edges, left, mid);
            mergeSort(edges, mid + 1, right);
            merge(edges, left, mid, right);
        }
    }
};

int main(int argc, char* argv[])
{

    int n;
    int m;
    std::ifstream inputFile(argv[1]);

    inputFile >> n >> m;

    Edge* edges = new Edge[m];    

    for (int i = 0; i < m; i++)
    {
        inputFile >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    std::cout << Mst(n).kruskal(edges, m);
    inputFile.close();
    delete[] edges;

    return 0;
}