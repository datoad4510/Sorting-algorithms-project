#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <climits>
#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
using namespace std;
using namespace std::chrono;

// Return the time the given sorting algorithm takes to sort the given vector
auto timeSort(void (*sortAlgorithm)(vector<int>&),vector<int>& v){
	auto start = high_resolution_clock::now();
	sortAlgorithm(v);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Execution time: "
		 << duration.count() << " microseconds" << endl;
	return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

template<typename T>
void print(const vector<T>& v)
{
	cout << endl;
	for (auto m : v)
		cout << m << " ";
	cout << endl;
}

// Generate a random vector containing unique elements,
// we use it to estimate the average running time of sorting algorithm
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

// Generate a already sorted vector containing unique elements
vector<int> sortedVector(int n)
{
	vector<int> v(n);
	for (int i = 1; i <= n; ++i)
	{
		v[i - 1] = i;
	}

	return v;
}

// Generate a vector where elements are in reverse order
vector<int> reverseVector(int n)
{
	vector<int> v(n);
	for (int i = 1; i <= n; ++i)
	{
		v[n - (i - 1)] = i;
	}

	return v;
}

// Generate a vector where elements are in reverse order
// n is always even and a power of two, a recursive implementation is very tempting but we would
// stackoverflow very quickly
vector<int> balancedPartitionVector(int n)
{
	vector<int> v(n);

	int N = log2(n);
	int count = 0;

	for(int i = 1; i <= N; ++i){
		for(int j = 1; j <= pow(2,i-1); ++j){

			v[((1 + 2*(j-1))/pow(2,i))*n] = count;
			count++;
			// cout << ((1 + 2*(j-1))/pow(2,i))*n << " : " << count << '\n';
		}
	}
	v[0] = n;

	return v;
}

// Check if two vectors are equal
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

// Test if the given sorting algorithm can sort random arrays
void testSort(void (*sortAlgorithm)(vector<int>&))
{
	for (int i = 5; i < 20; ++i)
	{
		vector<int> test = randomVector(i);
		print(test);

		vector<int> sorted(test);
		sort(sorted.begin(), sorted.end());

		sortAlgorithm(test);
		print(test);

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