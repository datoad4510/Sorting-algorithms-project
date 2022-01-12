#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <climits>
// #include "utilis.cpp"
using namespace std;
using namespace std::chrono;

void selectionSort(vector<int>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		int min = i;
		for (int j = i + 1; j < v.size(); ++j)
		{
			if (v[j] < v[min])
				min = j;
		}

		swap(v[i], v[min]);
	}
}
