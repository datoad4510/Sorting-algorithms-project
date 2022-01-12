#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <climits>
// #include "utilis.cpp"
using namespace std;
using namespace std::chrono;

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