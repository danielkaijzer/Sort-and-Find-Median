#include <fstream>
#include "HalfSelectionSort.hpp"
#include "StandardSort.hpp"
#include "MergeSort.hpp"
#include "InPlaceMergeSort.hpp"
#include "HalfHeapSort.hpp"
// #include "QuickSelect.hpp"
#include "MedianOfMediansMethod.hpp"
#include "WorstCaseQuickSelect.hpp"

#include <iostream>
#include <vector>
#include <stdlib.h>

// Median: 50492874, 50173306

bool vectorsMatch(const std::vector<int>& myoutput, const std::vector<int>& expected) {
    char median[] = "50492874";
    
    // Check if the lengths of the vectors are the same
    if (((myoutput.size())-1) != expected.size()) {
        std::cout << myoutput.size() <<"\n";
        std::cout << expected.size() <<"\n";
        return false;
    }
    else{
        std::cout << "vector size matches\n size: " << myoutput.size() << "\n";
    }

    bool test = true;

    // Compare each element of the vectors
    for (size_t i = 0; i < expected.size(); ++i) {
        if (myoutput[i+1] != expected[i] && test == true) {
            std::cout << "index " << i << " in my output has value: " << myoutput[i+1] << std::endl;
            std::cout << "index " << i << " in expected output has value: " << expected[i] << std::endl;
            test = false;
        }
        if (myoutput[i] == std::atoi(median)){
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
    // readIntegersFromFile("input9.txt", nums);

    nums = worstCaseQuickSelect();

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


    // std::cout << "Half Heap Sort: \n";
    // std::cout << "Median: " << halfHeapSort(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int HalfHeapSort_Duration = duration;

    // std::cout << "QuickSelect: \n";
    // std::cout << "Median: " << quickSelect(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int QuickSelect_Duration = duration;


    std::cout << "Median of Medians: \n";
    std::cout << "Median: " << quickSelectM(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl << std::endl;
    int MedianOfMedians = duration;

    // writeVectorToFile(nums,"outputworstcase.txt");

    // std::vector<int> output;
    // readIntegersFromFile("heapsort4.txt",output);

    // if (vectorsMatch(nums, output)) {
    //     std::cout << "Vectors match!" << std::endl;
    // } else {
    //     std::cout << "Vectors do not match." << std::endl;
    // }

    // for (int i = 0; i < nums.size(); ++i){
    //     if (i < 3 || i > nums.size()-4)
    //     std::cout << nums[i] << " ";
    // }
    // std::cout <<std::endl;

    // outputs for HEAPSORT
        // OUTPUT:  50492874 50624991 50579758 ... 57423279 86361348 92940355

        // CORRECT: 50492874 50624991 50579758 ... 57423279 98679032 92940355

    // outputs for quickSelect
        // 21820191 25991116 30706795 ... 80388697 82907042 71434180

        // 25991116 5409968 30706795 ... 80388697 91636921 89010357

    return 0;
}