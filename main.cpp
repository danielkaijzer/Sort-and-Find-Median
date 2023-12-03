#include <fstream>
#include "HalfSelectionSort.hpp"
#include "StandardSort.hpp"
#include "MergeSort.hpp"
#include "InPlaceMergeSort.hpp"
#include "HalfHeapSort.hpp"
#include "QuickSelect.hpp"
#include "MedianOfMedians.hpp"

#include <iostream>
#include <vector>

bool vectorsMatch(const std::vector<int>& vector1, const std::vector<int>& vector2) {
    // Check if the lengths of the vectors are the same
    if (vector1.size() != vector2.size()) {
        return false;
    }

    // Compare each element of the vectors
    for (size_t i = 0; i < vector1.size(); ++i) {
        if (vector1[i] != vector2[i]) {
            return false;
        }
    }

    // If all elements match, return true
    return true;
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

std::vector<int> readIntegersFromFile(const std::string& filename) {
    std::vector<int> result;
    
    // Open the file
    std::ifstream file(filename);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        // You may choose to handle the error differently, e.g., throw an exception
        return result;
    }

    int number;
    // Read integers from the file and append them to the vector
    while (file >> number) {
        result.push_back(number);
    }

    // Close the file
    file.close();

    return result;
}

int main(){
    // std::vector<int> nums{3,2,1,4,5}; // Median: 2
    int duration = 0;

    std::string filename = "input1.txt";
    std::vector<int> nums;
 
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()){
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    int value;
    while (inputFile >> value){
        nums.push_back(value);
    }

    inputFile.close();

    // DOESN'T MATCH OUTPUT
    // std::cout << "Half Selection Sort: \n";
    // std::cout << "Median: " << halfSelectionSort(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int halfSelection_Duration = duration;

    // write output to file
    // std::string halfSelect_Output = "halfSelect_Output.txt";
    // writeVectorToFile(nums, halfSelect_Output);



    // std::cout << "Standard Sort: \n";
    // std::cout << "Median: " << standardSort(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int Standard_Duration = duration;

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

    // DOESN'T MATCH OUTPUT
    std::cout << "QuickSelect: \n";
    std::cout << "Median: " << quickSelect(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl << std::endl;
    int QuickSelect_Duration = duration;

    // std::cout << "Median of Medians: \n";
    // std::cout << "Median: " << medianOfMedians(nums,duration) <<
    // std::endl << "Duration: " << duration << std::endl << std::endl;
    // int MedianOfMedians = duration;

    std::vector<int> output = readIntegersFromFile("quickselect1.txt");

    if (vectorsMatch(nums, output)) {
        std::cout << "Vectors match!" << std::endl;
    } else {
        std::cout << "Vectors do not match." << std::endl;
    }

    for (auto num : nums){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // outputs for HEAPSORT
        // 50214089 50200007 49946203 ... 99617657 99881669 99922526

        // 50492874 50624991 50579758 ... 57423279 98679032 92940355

    // outputs for quickSelect
        // 21820191 25991116 30706795 ... 80388697 82907042 71434180

        // 25991116 5409968 30706795 ... 80388697 91636921 89010357

    return 0;
}