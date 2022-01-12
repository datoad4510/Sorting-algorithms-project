#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <climits>
#include "utilis.cpp"
#include "insertionSort.cpp"
#include "selectionSort.cpp"
#include "mergeSort.cpp"
#include "quickSort.cpp"
#include "hybridMergeSort.cpp"
#include "randomizedQuicksort.cpp"
#include "tailRecursiveQuicksort.cpp"
using namespace std;
using namespace std::chrono;

int main()
{
	// Bounds of power of two we will use
	int startPow = 8;
	int endPow = 16;

	// Initialize necessary vectors
	std::vector<int> arraySize;
	std::vector< vector<int> > avgVecList;
	std::vector< vector<int> > bestVecList;
	std::vector< vector<int> > worstVecList;
	std::vector< vector<int> > balancedPartitionVecList;

	// Initialize and open the stream for acessing csv files
	std::ofstream averageCaseFile;
	std::ofstream bestCaseFile;
	std::ofstream worstCaseFile;
    averageCaseFile.open("./../data/averageCaseData.csv");
	bestCaseFile.open("./../data/bestCaseData.csv");
	worstCaseFile.open("./../data/worstCaseData.csv");
    
	// Create the array containing values of N and vectors to sort
    averageCaseFile << "N,";
	bestCaseFile << "N,";
	worstCaseFile << "N,";
	for (size_t i = startPow; i < endPow; i++){
		arraySize.push_back(pow(2,i));
		
		// Write the first line for each csv files
        averageCaseFile << to_string(int(pow(2,i))) << ",";
		bestCaseFile << to_string(int(pow(2,i))) << ",";
		worstCaseFile << to_string(int(pow(2,i))) << ",";

		//Fullfill vectors
		avgVecList.push_back(randomVector(pow(2,i)));
		bestVecList.push_back(sortedVector(pow(2,i)));
		balancedPartitionVecList.push_back(balancedPartitionVector(pow(2,i)));
		worstVecList.push_back(reverseVector(pow(2,i)));
	}
    averageCaseFile << "\n";
	bestCaseFile << "\n";
	worstCaseFile << "\n";

	///// Average Case Running time ///// 
	cout << "//////// Average Case: //////// \n";

	averageCaseFile << "Insertion Sort,";
	cout << "Insertion sort:\n";
	// Here it is important to copy the vector to avoid modifying it and changing the running time of the nest sorting algorithm
	std::vector< vector<int> > avgVecList1 = avgVecList; 
	for (size_t i = 0; i < endPow - startPow; i++){
		averageCaseFile << to_string(timeSort(insertionSort, avgVecList1[i])) + ",";
	}
	averageCaseFile << "\n";

    averageCaseFile << "Selection Sort,";
	cout << "Selection sort:\n";
	std::vector< vector<int> > avgVecList2 = avgVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		averageCaseFile << to_string(timeSort(selectionSort, avgVecList2[i])) + ",";
	}
	averageCaseFile << "\n";

    averageCaseFile << "Merge Sort,";
	cout << "Merge sort:\n";
	std::vector< vector<int> > avgVecList3 = avgVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		averageCaseFile << to_string(timeSort(mergesortHelper, avgVecList3[i])) + ",";
	}
	averageCaseFile << "\n";

    averageCaseFile << "Quick Sort,";
	cout << "Quick sort:\n";
	std::vector< vector<int> > avgVecList4 = avgVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		averageCaseFile << to_string(timeSort(quicksortHelper, avgVecList4[i])) + ",";
	}
	averageCaseFile << "\n";

	averageCaseFile << "Hybrid Merge Sort,";
	cout << "Hybrid Merge Sort:\n";
	std::vector< vector<int> > avgVecList5 = avgVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		averageCaseFile << to_string(timeSort(hybridMergesortHelper, avgVecList5[i])) + ",";
	}
	averageCaseFile << "\n";

	averageCaseFile << "Randomized Quick Sort,";
	cout << "Randomized Quick Sort:\n";
	std::vector< vector<int> > avgVecList6 = avgVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		averageCaseFile << to_string(timeSort(randomizedQuicksortHelper, avgVecList6[i])) + ",";
	}
	averageCaseFile << "\n";

	averageCaseFile << "Tail Recursive Quick Sort,";
	cout << "Tail Recursive Quick Sort:\n";
	std::vector< vector<int> > avgVecList7 = avgVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		averageCaseFile << to_string(timeSort(hybridMergesortHelper, avgVecList7[i])) + ",";
	}
	averageCaseFile << "\n";

	averageCaseFile.close();

	///// Best Case Running time ///// 
	cout << "//////// Best Case: //////// \n";

	bestCaseFile << "Insertion Sort,";
	cout << "Insertion sort:\n";
	// Here it is important to copy the vector to avoid modifying it and changing the running time of the nest sorting algorithm
	std::vector< vector<int> > bestVecList1 = bestVecList; 
	for (size_t i = 0; i < endPow - startPow; i++){
		bestCaseFile << to_string(timeSort(insertionSort, bestVecList1[i])) + ",";
	}
	bestCaseFile << "\n";

    bestCaseFile << "Selection Sort,";
	cout << "Selection sort:\n";
	std::vector< vector<int> > bestVecList2 = bestVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		bestCaseFile << to_string(timeSort(selectionSort, bestVecList2[i])) + ",";
	}
	bestCaseFile << "\n";

    bestCaseFile << "Merge Sort,";
	cout << "Merge sort:\n";
	std::vector< vector<int> > bestVecList3 = bestVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		bestCaseFile << to_string(timeSort(mergesortHelper, bestVecList3[i])) + ",";
	}
	bestCaseFile << "\n";

    bestCaseFile << "Quick Sort,";
	cout << "Quick sort:\n";
	std::vector< vector<int> > balancedPartitionVecList4 = balancedPartitionVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		bestCaseFile << to_string(timeSort(quicksortHelper, balancedPartitionVecList4[i])) + ",";
	}
	bestCaseFile << "\n";

	bestCaseFile << "Hybrid Merge Sort,";
	cout << "Hybrid Merge Sort:\n";
	std::vector< vector<int> > bestVecList5 = bestVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		bestCaseFile << to_string(timeSort(hybridMergesortHelper, bestVecList5[i])) + ",";
	}
	bestCaseFile << "\n";

	bestCaseFile << "Randomized Quick Sort,";
	cout << "Randomized Quick Sort:\n";
	std::vector< vector<int> > balancedPartitionVecList6 = balancedPartitionVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		bestCaseFile << to_string(timeSort(randomizedQuicksortHelper, balancedPartitionVecList6[i])) + ",";
	}
	bestCaseFile << "\n";

	bestCaseFile << "Tail Recursive Quick Sort,";
	cout << "Tail Recursive Quick Sort:\n";
	std::vector< vector<int> > balancedPartitionVecList7 = balancedPartitionVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		bestCaseFile << to_string(timeSort(hybridMergesortHelper, balancedPartitionVecList7[i])) + ",";
	}
	bestCaseFile << "\n";

	bestCaseFile.close();

	///// Worst Case Running time ///// 
	cout << "//////// Worst Case: ////////\n";

	worstCaseFile << "Insertion Sort,";
	cout << "Insertion sort:\n";
	// Here it is important to copy the vector to avoid modifying it and changing the running time of the nest sorting algorithm
	std::vector< vector<int> > worstVecList1 = worstVecList; 
	for (size_t i = 0; i < endPow - startPow; i++){
		worstCaseFile << to_string(timeSort(insertionSort, worstVecList1[i])) + ",";
	}
	worstCaseFile << "\n";

    worstCaseFile << "Selection Sort,";
	cout << "Selection sort:\n";
	std::vector< vector<int> > worstVecList2 = worstVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		worstCaseFile << to_string(timeSort(selectionSort, worstVecList2[i])) + ",";
	}
	worstCaseFile << "\n";

    worstCaseFile << "Merge Sort,";
	cout << "Merge sort:\n";
	std::vector< vector<int> > worstVecList3 = worstVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		worstCaseFile << to_string(timeSort(mergesortHelper, worstVecList3[i])) + ",";
	}
	worstCaseFile << "\n";

    worstCaseFile << "Quick Sort,";
	cout << "Quick sort:\n";
	std::vector< vector<int> > worstVecList4 = worstVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		worstCaseFile << to_string(timeSort(quicksortHelper, worstVecList4[i])) + ",";
	}
	worstCaseFile << "\n";

	worstCaseFile << "Hybrid Merge Sort,";
	cout << "Hybrid Merge Sort:\n";
	std::vector< vector<int> > worstVecList5 = worstVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		worstCaseFile << to_string(timeSort(hybridMergesortHelper, worstVecList5[i])) + ",";
	}
	worstCaseFile << "\n";

	worstCaseFile << "Randomized Quick Sort,";
	cout << "Randomized Quick Sort:\n";
	std::vector< vector<int> > worstVecList6 = worstVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		worstCaseFile << to_string(timeSort(randomizedQuicksortHelper, worstVecList6[i])) + ",";
	}
	worstCaseFile << "\n";

	worstCaseFile << "Tail Recursive Quick Sort,";
	cout << "Tail Recursive Quick Sort:\n";
	std::vector< vector<int> > worstVecList7 = worstVecList;
	for (size_t i = 0; i < endPow - startPow; i++){
		worstCaseFile << to_string(timeSort(hybridMergesortHelper, worstVecList7[i])) + ",";
	}
	worstCaseFile << "\n";

	worstCaseFile.close();
}