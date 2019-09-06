#include <iostream>
#include <chrono>
using namespace std;

/* function to sort arr using shellSort */
int shellSort(int arr[], int n)
{
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
    return 0;
}

int main()
{
    const int size = 200000;
	int arr[size];

	for (int i = 0; i < size; ++i) {
		arr[i] = 1 + rand() % 50;
	}
	auto start = chrono::steady_clock::now();
    int n = sizeof(arr)/sizeof(arr[0]);
    shellSort(arr, n);
    auto end = chrono::steady_clock::now();
    cout << "\nTime of execution: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milisegundos." << endl;
    return 0;
}
