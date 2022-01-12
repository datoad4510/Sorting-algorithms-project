#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <random>
#include <ctime>
#include <climits>
using namespace std;
using namespace std::chrono;

default_random_engine dre(time(NULL));

vector<int> merge(vector<int>& v1, vector<int>& v2)
{
	int size3 = v1.size() + v2.size();
	vector<int> v3(size3);

	//sentinel variables
	v1.push_back(INT_MAX);
	v2.push_back(INT_MAX);

	// indices for v1, v2 and v3
	int j = 0;
	int k = 0;

	for (int i = 0; i < size3; i++)
	{
		if (v1[j] <= v2[k])
		{
			v3[i] = v1[j];
			++j;
		}
		else
		{
			v3[i] = v2[k];
			++k;
		}
	}
	v1.pop_back();//removing sentinels
	v2.pop_back();
	return v3;
}

vector<int> mergesort(vector<int>& v)
{
	int q = v.size() / 2;
	if (q == 0)
		return v; //base case

	// divide array into two subarrays
	vector<int> v1(v.begin(), v.begin() + q);
	vector<int> v2(v.begin() + q, v.end());

	v1 = mergesort(v1);
	v2 = mergesort(v2);

	return merge(v1, v2);
}

void mergesortHelper(vector<int>& v)
{
	v = mergesort(v);
}


/*
put pivot in the first position. then in v[left+1...right),
put everything less than the pivot to the left, more to the right
while keeping track of the boundary. finally, move the pivot to
right before the boundary value
*/
int partition(vector<int>& v, int pivot, int left, int right)
{
	// make sure pivot is between left and right
	assert(pivot >= left && pivot < right);

	// make sure left and right are valid
	assert(left >= 0 && right <= v.size());

	// if size of subarray is 1, it's already partitioned
	if (right - left == 1)
		return left;

	// for simplicity, swap pivot with the first element
	int pivot_value = v[pivot];
	swap(v[left], v[pivot]);

	// find first element that is greater than v[pivot]
	// during every step of the algorithm, all the elements before
	// boundary_idx are smaller than v[pivot]. v[boundary_index] is greater
	int boundary_idx = left + 1;
	while (boundary_idx < v.size() && v[boundary_idx] <= pivot_value)
	{
		++boundary_idx;
	}

	// this variable just runs through the array
	int running_idx = boundary_idx + 1;

	while (running_idx < right)
	{
		// keep updating the boundary
		if (v[running_idx] <= pivot_value)
		{
			swap(v[boundary_idx], v[running_idx]);
			++boundary_idx;
		}

		++running_idx;
	}

	// put the pivot in the correct position
	swap(v[left], v[boundary_idx - 1]);

	return boundary_idx - 1;
}

// sort v[left...right)
void quicksort(vector<int>& v, int left, int right)
{
	if (left < right)
	{
		// choose left as pivot every time (don't randomize pivot)
		int mid = partition(v, left, left, right);

		// sort v[left...mid)
		quicksort(v, left, mid);

		// sort v[mid+1...right)
		quicksort(v, mid + 1, right);
	}
}

void quicksortHelper(vector<int>& v)
{
	quicksort(v, 0, v.size());
}

template<typename T>
void print(const vector<T>& v)
{
	cout << endl;
	for (auto m : v)
		cout << m << " ";
	cout << endl;
}

vector<int> randomVector(int n)
{
	vector<int> v(n);
	for (int i = 1; i <= n; ++i)
	{
		v[i - 1] = i;
	}

	random_shuffle(v.begin(), v.end());

	return v;
}

bool areEqual(const vector<int>& v1, const vector<int>& v2)
{
	if (v1.size() != v2.size())
		return false;

	for (int i = 0; i < v1.size(); ++i)
	{
		if (v1[i] != v2[i])
			return false;
	}

	return true;
}

void testSort(void (*sortAlgorithm)(vector<int>&))
{
	for (int i = 1; i < 100; ++i)
	{
		vector<int> test = randomVector(i);

		vector<int> sorted(test);
		sort(sorted.begin(), sorted.end());

		sortAlgorithm(test);

		if (!areEqual(test, sorted))
		{
			cout << "Algorithm failed a test. Output: ";
			print(test);
			cout << "Expected output: ";
			print(sorted);

			return;
		}

	}

	cout << "The algorithm passed all tests!" << endl;
}

void timeSort(void (*sortAlgorithm)(vector<int>&), vector<int>& v)
{
	auto start = high_resolution_clock::now();
	sortAlgorithm(v);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: "
		<< duration.count() << " microseconds" << endl;
}



// sorts v[left..right)
void insertionSort(vector<int>& v, int left, int right)
{
	for (int i = left; i < right; ++i)
	{
		for (int j = i; j > 0 && v[j - 1] > v[j]; --j)
		{
			swap(v[j], v[j - 1]);
		}
	}
}

void insertionSortHelper(vector<int>& v)
{
	insertionSort(v, 0, v.size());
}

// sorts v[left..right)
void selectionSort(vector<int>& v, int left, int right)
{
	for (int i = left; i < right; i++)
	{
		int min = i;
		for (int j = i + 1; j < right; ++j)
		{
			if (v[j] < v[min])
				min = j;
		}

		swap(v[i], v[min]);
	}
}

void selectionSortHelper(vector<int>& v)
{
	selectionSort(v, 0, v.size());
}

// https://stackoverflow.com/questions/13906169/when-is-insertion-sort-faster-than-merge-sort
vector<int> hybridMergesort(vector<int>& v)
{
	if (v.size() <= 43)
	{
		insertionSort(v, 0, v.size());
		return v;
	}

	int q = v.size() / 2;
	if (q == 0)
		return v; //base case

	// divide array into two subarrays
	vector<int> v1(v.begin(), v.begin() + q);
	vector<int> v2(v.begin() + q, v.end());

	v1 = hybridMergesort(v1);
	v2 = hybridMergesort(v2);

	return merge(v1, v2);
}

void hybridMergesortHelper(vector<int>& v)
{
	v = hybridMergesort(v);
}

// sort v[left...right)
void tailRecursiveQuicksort(vector<int>& v, int left, int right)
{
	while (left < right)
	{
		// choose left as pivot every time (don't randomize pivot)
		int mid = partition(v, left, left, right);

		// sort left half
		tailRecursiveQuicksort(v, left, mid);

		// move on to second half
		left = mid + 1;
	}
}


void tailRecursiveQuicksortHelper(vector<int>& v)
{
	tailRecursiveQuicksort(v, 0, v.size());
}

// sort v[left...right)
void randomizedQuicksort(vector<int>& v, int left, int right)
{
	
	while (left < right)
	{
		// choose random pivot
		uniform_int_distribution<int> uid(left, right - 1);
		int pivot = uid(dre);

		// choose left as pivot every time (don't randomize pivot)
		int mid = partition(v, pivot, left, right);

		// sort left half
		randomizedQuicksort(v, left, mid);

		// move on to second half
		left = mid + 1;
	}
}


void randomizedQuicksortHelper(vector<int>& v)
{
	randomizedQuicksort(v, 0, v.size());
}


int main()
{
	int arraySize = 1000;
	vector<int> test = randomVector(arraySize);

	cout << "Insertion sort:";
	vector<int> v = test;
	timeSort(insertionSortHelper, v);
	testSort(insertionSortHelper);

	cout << "\n\nSelection sort:";
	v = test;
	timeSort(selectionSortHelper, v);
	testSort(selectionSortHelper);

	cout << "\n\nQuicksort:";
	v = test;
	timeSort(quicksortHelper, v);
	testSort(quicksortHelper);

	cout << "\n\nMergesort:";
	v = test;
	timeSort(mergesortHelper, v);
	testSort(mergesortHelper);

	cout << "\n\nHybrid Mergesort (using insertion sort under size 43):";
	v = test;
	timeSort(hybridMergesortHelper, v);
	testSort(hybridMergesortHelper);

	cout << "\n\nTail recursive Quicksort:";
	v = test;
	timeSort(tailRecursiveQuicksortHelper, v);
	testSort(tailRecursiveQuicksortHelper);

	cout << "\n\nRandomized Quicksort:";
	v = test;
	timeSort(randomizedQuicksortHelper, v);
	testSort(randomizedQuicksortHelper);
}