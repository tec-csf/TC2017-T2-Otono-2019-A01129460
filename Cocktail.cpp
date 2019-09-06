#include <iostream>
#include <chrono>
using namespace std;

// Sorts arrar a[0..n-1] using Cocktail sort
void CocktailSort(int a[], int n)
{
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = false;

        // loop from left to right same as
        // the bubble sort
        for (int i = start; i < end; ++i) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        // if nothing moved, then array is sorted.
        if (!swapped)
            break;

        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = false;

        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;

        // from right to left, doing the
        // same comparison as in the previous stage
        for (int i = end - 1; i >= start; --i) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
}

// Driver code
int main()
{
    const int size = 200000;
	int arr[size];

	for (int i = 0; i < size; ++i) {
		arr[i] = 1 + rand() % 50;
	}
	auto start = chrono::steady_clock::now();
	int n = sizeof(arr) / sizeof(arr[0]);
    CocktailSort(arr, n);
    auto end = chrono::steady_clock::now();
	cout << "\nTime of execution: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milisegundos." << endl;
	return 0;
}
