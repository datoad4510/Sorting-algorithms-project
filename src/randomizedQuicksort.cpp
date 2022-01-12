#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <climits>
#include <random>
// #include "utilis.cpp"
using namespace std;
using namespace std::chrono;

default_random_engine dre(time(NULL));

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