#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <climits>
// #include "utilis.cpp"
using namespace std;
using namespace std::chrono;

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
