#include <iostream>
#include <fstream>


const int MAX_INT = 2147483647;
struct Node 
{
	int key;
	int pos;
};
class priorityqueue 
{
private:

	Node* arr;
	int* pos;
	int size;
	int capacity;
	void min_heapify(int i)
	{
		int lowest = i;
		int l = 2 * i + 1;
		int r = 2 * i + 2;

		if (l < size && arr[l].key < arr[lowest].key)
		{
			lowest = l;
		}
		if (r < size && arr[r].key < arr[lowest].key)
		{
			lowest = r;
		}

		if (lowest != i)
		{
			Node temp = arr[i];
			arr[i] = arr[lowest];
			arr[lowest] = temp;
			pos[arr[i].pos] = i;
			pos[arr[lowest].pos] = lowest;
			min_heapify(lowest);
		}
	}
	void decrease_key(int i, int key)
	{
		arr[i].key = key;
		while (i > 0 && arr[i].key < arr[(i - 1) / 2].key)
		{
			Node temp1 = arr[i];
			arr[i] = arr[(i - 1) / 2];
			arr[(i - 1) / 2] = temp1;
			pos[arr[i].pos] = i;
			i = (i - 1) / 2;
			pos[arr[i].pos] = i;
		}

	}

public:

	priorityqueue() 
	{
		size = 0;
		capacity = 0;
		pos = new int[10];
		arr = new Node[1];
	}

	~priorityqueue()
	{
		delete[] arr;
		delete[] pos;
	}

	void insert(int key, int pos1, int k) 
	{
		if (capacity == 0) 
		{
			delete[] arr;
			delete[] pos;
			arr = new Node[1];
			arr[0].key = key;
			pos = new int[k + 1];
			arr[0].pos = pos1;
			pos[pos1] = 0;
			capacity = 1;
			size = 1;
		}
		else 
		{
			if (capacity == size) 
			{
				capacity = capacity * 2;
				Node* temp = new Node[capacity];
				for (int i = 0; i < size; ++i)
				{
					temp[i] = arr[i];
				}
				delete[] arr;
				arr = temp;
			}
			size++;
			arr[size - 1].key = MAX_INT;
			arr[size - 1].pos = pos1;
			pos[pos1] = size - 1;
			decrease_key(size - 1, key);
		}
	}

	void extractMin(std::ofstream& outFile) 
	{

		if (size < 1) 
		{
			outFile << "*\n";
			return;
		}

		int min = arr[0].key;
		arr[0] = arr[size - 1];
		pos[arr[0].pos] = 0;
		size -= 1;
		min_heapify(0);

		outFile << min << "\n";
	}

	void decreaseKey(int pos1, int key) 
	{
		decrease_key(pos[pos1], key);
	}
};



int main(int argc, char* argv[]) 
{
	priorityqueue queue;
	int counter = 0;
	int x;
	int y;
	char symb;

	std::ifstream countFile(argv[1]);
	std::ifstream inputFile(argv[1]);
	std::ofstream outputFile(argv[2]);

	if (!inputFile.is_open())
	{
		return -1;
	}

	char* str = new char[1024];

	while (!countFile.eof())
	{
		countFile.getline(str, 1024, '\n');
		counter++;
	}

	countFile.close();

	for (int i = 1; i <= counter; i++)
	{
		inputFile >> symb;

		if (symb == 'p')
		{
			for (int j = 1; j <= 3; j++)
			{
				inputFile >> symb;
			}
			inputFile >> x;
			queue.insert(x, i, counter);
		}
		else if (symb == 'e')
		{
			for (int j = 1; j <= 10; j++)
			{
				inputFile >> symb;
			}
			queue.extractMin(outputFile);
		}
		else if (symb == 'd')
		{
			for (int j = 1; j <= 11; j++)
			{
				inputFile >> symb;
			}
			inputFile >> x >> y;
			queue.decreaseKey(x, y);
		}
	}

	delete[] str;
	inputFile.close();
	outputFile.close();

	return 0;
}