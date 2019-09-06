// Selection Sort.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <chrono>
using namespace std;
void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element
		swap(&arr[min_idx], &arr[i]);
	}
}

// Driver program to test above functions
int main()
{
	const int size = 200000;
	int arr[size];

	for (int i = 0; i < size; ++i) {
		arr[i] = 1 + rand() % 50;
	}
	auto start = chrono::steady_clock::now();
	int n = sizeof(arr) / sizeof(arr[0]);
	selectionSort(arr, n);
	auto end = chrono::steady_clock::now();
	cout << "\nTime of execution: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milisegundos." << endl;
	return 0;
}
