//Counting sort which takes negative numbers as well
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>


using namespace std;

void countSort(vector <int>& arr)
{
    int max = *max_element(arr.begin(), arr.end());
    int min = *min_element(arr.begin(), arr.end());
    int range = max - min + 1;

    vector<int> count(range), output(arr.size());
    for(int i = 0; i < arr.size(); i++)
        count[arr[i]-min]++;

    for(int i = 1; i < count.size(); i++)
        count[i] += count[i-1];

    for(int i = arr.size()-1; i >= 0; i--)
    {
        output[ count[arr[i]-min] -1 ] = arr[i];
        count[arr[i]-min]--;
    }

    for(int i=0; i < arr.size(); i++)
        arr[i] = output[i];
}

int main()
{
    const int size = 200000;
    vector<int> arr;
    for (int i = 0; i < size; ++i) {
        int val = 1 + rand() % 50;
        arr.push_back(val);
    }
    auto start = chrono::steady_clock::now();
    countSort (arr);
    auto end = chrono::steady_clock::now();
	cout << "\nTime of execution: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milisegundos." << endl;
	return 0;
}
