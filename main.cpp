#include <fstream>
#include "HalfSelectionSort.hpp"
#include "StandardSort.hpp"
#include "MergeSort.hpp"
#include "InPlaceMergeSort.hpp"
#include "HalfHeapSort.hpp"
#include "QuickSelect.hpp"
#include "MedianOfMedians.hpp"
#include "WorstCaseQuickSelect.hpp"

#include <iostream>
#include <vector>
#include <stdlib.h>

// Median: 50492874, 50173306

bool vectorsMatch(const std::vector<int>& vector1, const std::vector<int>& vector2) {
    char median[] = "50173306";
    
    // Check if the lengths of the vectors are the same
    if (vector1.size() != vector2.size()) {
        std::cout << vector1.size() <<"\n";
        std::cout << vector2.size() <<"\n";
        return false;
    }
    else{
        std::cout << "vector size matches\n size: " << vector1.size() << "\n";
    }

    bool test = true;

    // Compare each element of the vectors
    for (size_t i = 0; i < vector1.size(); ++i) {
        if (vector1[i] != vector2[i] && test == true) {
            std::cout << "index " << i << " in vector1 has value: " << vector1[i] << std::endl;
            std::cout << "index " << i << " in vector2 has value: " << vector2[i] << std::endl;
            test = false;
        }
        if (vector1[i] == std::atoi(median)){
            std::cout << "index of median: " << i << std::endl;
        }
    }

    // If all elements match, return true
    return test;
}

void writeVectorToFile(const std::vector<int>& numbers, const std::string& filename) {
    // Open the file for writing
    std::ofstream outputFile(filename);

    // Check if the file is successfully opened
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Write each integer to the file
    for (int num : numbers) {
        outputFile << num << " ";
    }

    // Close the file
    outputFile.close();
}

void readIntegersFromFile(const std::string& filename, std::vector<int> &vec) {
    
    // Open the file
    std::ifstream file(filename);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    int value;
    // Read integers from the file and append them to the vector
    while (file >> value) {
        vec.push_back(value);
    }

    // Close the file
    file.close();

    return;
}



int main(){
    int duration = 0;
    // std::vector<int> nums {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    std::vector<int> nums;
    readIntegersFromFile("input1.txt", nums);

    // nums = worstCaseQuickSelect();



    // std::cout << "Standard Sort: \n";
    // std::cout << "Median: " << standardSort(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int Standard_Duration = duration;

    // write output to file
    // std::string sorted_output = "Sorted_Output.txt";
    // writeVectorToFile(nums, sorted_output);


    // std::cout << "Half Selection Sort: \n";
    // std::cout << "Median: " << halfSelectionSort(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int halfSelection_Duration = duration;

    // std::cout << "Merge Sort: \n";
    // std::cout << "Median: " << mergeSort(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int MergeSort_Duration = duration;

    // std::cout << "In-Place Merge Sort: \n";
    // std::cout << "Median: " << inPlaceMergeSort(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int InPlaceMergeSort_Duration = duration;


    // DOESN'T MATCH OUTPUT
    // std::cout << "Half Heap Sort: \n";
    // std::cout << "Median: " << halfHeapSort(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int HalfHeapSort_Duration = duration;


    // std::cout << "Full Heap Sort: \n";
    // std::cout << "Median: " << HeapSort(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int heapSort_Duration = duration;

    // DOESN'T MATCH OUTPUT
    std::cout << "QuickSelect: \n";
    std::cout << "Median: " << quickSelect(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl << std::endl;
    int QuickSelect_Duration = duration;

    // std::cout << "Quicksort: \n";
    // std::cout << "Median: " << quickSort(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int QuickSelect_Duration = duration;

    // std::cout << "Median of Medians: \n";
    // std::cout << "Median: " << medianOfMedians(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int MedianOfMedians = duration;

    // writeVectorToFile(nums,"outputworstcase.txt");

    std::vector<int> output;
    readIntegersFromFile("quickselect1.txt",output);

    if (vectorsMatch(nums, output)) {
        std::cout << "Vectors match!" << std::endl;
    } else {
        std::cout << "Vectors do not match." << std::endl;
    }

    for (int i = 0; i < nums.size(); ++i){
        if (i < 3 || i > nums.size()-4)
        std::cout << nums[i] << " ";
    }
    std::cout <<std::endl;

    // outputs for HEAPSORT
        // OUTPUT:  50492874 50624991 50579758 ... 57423279 86361348 92940355

        // CORRECT: 50492874 50624991 50579758 ... 57423279 98679032 92940355

    // outputs for quickSelect
        // 21820191 25991116 30706795 ... 80388697 82907042 71434180

        // 25991116 5409968 30706795 ... 80388697 91636921 89010357

    return 0;
}