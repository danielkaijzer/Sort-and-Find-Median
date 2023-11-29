#include <fstream>
#include "HalfSelectionSort.hpp"
#include "StandardSort.hpp"
#include "MergeSort.hpp"
#include "InPlaceMergeSort.hpp"
#include "HalfHeapSort.hpp"
#include "QuickSelect.hpp"
#include "MedianOfMedians.hpp"

int main(){
    // std::vector<int> nums{3,2,1,4,5}; // Median: 2
    int duration = 0;

    std::string filename = "input9.txt";
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


    std::cout << "Half Selection Sort: \n";
    std::cout << "Median: " << halfSelectionSort(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl << std::endl;
    int halfSelection_Duration = duration;


    std::cout << "Standard Sort: \n";
    std::cout << "Median: " << standardSort(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl << std::endl;
    int Standard_Duration = duration;

    std::cout << "Merge Sort: \n";
    std::cout << "Median: " << mergeSort(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl << std::endl;
    int MergeSort_Duration = duration;


    std::cout << "In-Place Merge Sort: \n";
    std::cout << "Median: " << inPlaceMergeSort(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl << std::endl;
    int InPlaceMergeSort_Duration = duration;

    std::cout << "Half Heap Sort: \n";
    std::cout << "Median: " << halfHeapSort(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl << std::endl;
    int HalfHeapSort_Duration = duration;

    std::cout << "QuickSelect: \n";
    std::cout << "Median: " << quickSelect(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl << std::endl;
    int QuickSelect_Duration = duration;

    std::cout << "Median of Medians: \n";
    std::cout << "Median: " << medianOfMedians(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl << std::endl;
    int MedianOfMedians = duration;

    // for (auto num : nums){
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;

    return 0;
}